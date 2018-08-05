# A simple memory allocator
mallocx

Not sure if everything works correctly but it should u know... lol
I've done this just for fun and I would not use this of course.
To use this:

```
make
$EDITOR prog.c #do your mallocxs
gcc prog.c -L. -lmallocx
./a.out
```

it is possible to perform debug rule for make:

```
make debug
```

which basically enables debug printfs, doesn't include debug symbols

## Behaviour

### mallocx

 * Unless given size is equal to 0, it tries to find out a suitable block for the passed size
 
 * If could not find the block, then request more space and generate a new block
 
    * If the head of the linked list is a null pointer, then just let it be the head of the block (first alloc)

    * Otherwise, append the block to the list

 * Otherwise, set block_is_free to 0

 * Return the block "data portion"

### callocx

 * Calculate the final size given nmemb and size
 
 * Call mallocx 

 * Unless mallocx fails, set the block "data portion" to zeroes (zeroing)

 * Return the zeroed block

### reallocx
 
 * if oldblock is a null pointer, then behave as mallocx (see above)

 * Otherwise, get the "block header"

 * If this is a freed block, then return the same block, without further actions, you should set the pointer to NULL after use freex

 * If block size is greater or equal to the given new size, then just return the same block

 * Check if there is an adjacent block

 * If the adjacent block is free, proceed as follows:

   * Compute the sum of the old block size plus the size of block_header type (on x86_64 is 24 bytes) + the adjacent block size (data portion)

   * If the sum is major or equal than reallocx's supplied new size, then "merge", meaning that the oldblock's next pointer is set to the adjacent block's next pointer and the block size of the oldblock is set to the just computed sum.
   
   * Return the old block, which now has a lot more capacity. However previous content is not cleaned up, it is user responsibility to avoid having trash

 * If the adjacent block is equal to a null pointer (tail of the list),

   * Request the operating system for new space

   * Unless the system call fails, update the old block's size to previous_size = previous_size + new_size 

   * Return the oldblock with more capacity 

 
  * If the previous conditions were not met, 

  * Call mallocx for an entirely new block

  * Copy old data from old block to new block

  * free the oldblock and set the pointer to NULL

  * Return the new pointer with the same old data, in this case from a new address

### freex

  * If given block is a null pointer, then do nothing
  
  * Get the "block header"

  * Turn on block_is_free flag


## Structure

```
 header          data
+---------------+------------------...+
|*next|size|free| user_data           |
+---------------+------------------...+
USER_HIDDEN      USER_VISIBLE
```
