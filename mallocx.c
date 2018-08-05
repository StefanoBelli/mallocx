/*
 * ssynx's malloc implementation (mallocx)
 * expect high fragmentation
 * 
 * do not use :)
 */

#define _DEFAULT_SOURCE //required by: sbrk

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "mallocx.h"
#include "dbg.h"

#if defined(__GNUC_MINOR__) || defined(__clang__)
#   define s_always_inline static inline __attribute__((__always_inline__))
#else
#   define s_always_inline static inline
#endif

typedef enum {
    FALSE,
    TRUE
} mallocx_bool;

typedef struct __s_block_header {

#if defined(__x86_64__)
  struct __s_block_header *next;
  size_t block_size;
  uint64_t block_is_free;
#endif

} block_header;

static block_header* blocks_head = NULL;

//request the operating system to extend reserved space
s_always_inline block_header* __iimpl_request_more_space(size_t space) {
    dfenter();

    dmessage("getting more space from the operating system...");
    block_header* new_space_addr = (block_header*) sbrk(space + sizeof(block_header));
    if(new_space_addr == NULL)
        return NULL;

    new_space_addr->block_is_free = 0;
    new_space_addr->block_size = space;
    new_space_addr->next = NULL;

    dfleave();
    return new_space_addr;
}

//look for suitable block (free block and sufficient space)
s_always_inline block_header* __iimpl_find_suitable_block(size_t required_size) {
    dfenter();

    dmessage("going through the linked list...");

    block_header* tmp_block = blocks_head;
    mallocx_bool looping = TRUE;
    while(looping && tmp_block) {
        if(tmp_block->block_is_free && tmp_block->block_size >= required_size)
            looping = FALSE;
        else 
            tmp_block = tmp_block->next;
    }

    dfleave();
    return tmp_block;
}

#define append_block_to_list(x_blockhdr) \
    { \
        block_header* tmp_block_head = blocks_head; \
        while(blocks_head->next) \
            blocks_head = blocks_head->next; \
        blocks_head->next = x_blockhdr; \
        blocks_head = tmp_block_head; \
    }

void* mallocx(size_t size) {
    dfenter();
    
    if(size == 0)
        return NULL;

    dmessage("looking for a suitable block for requested size");
    dvalue(size);
    block_header* your_block = __iimpl_find_suitable_block(size);
    if(your_block == NULL) {
        dmessage("could not find a suitable block... requesting space");
        errno = 0;
        if((your_block = __iimpl_request_more_space(size)) == NULL) {
            errno = ENOMEM;
            return NULL; //sbrk failed (exhausted memory)
        }

        if(blocks_head == NULL) {
            dmessage("head is NULL, this is new head");
            blocks_head = your_block;
        } else {
            dmessage("appending new block to the list...");
            append_block_to_list(your_block);
        }
    } else
        your_block->block_is_free = 0;

    dvalue(your_block->block_size);

    dfleave();
    return your_block + sizeof(block_header);
}

void* callocx(size_t nmemb, size_t size) {
    dfenter();

    const size_t final_size = nmemb * size;

    void* addr = mallocx(final_size);
    if(addr == NULL)
        return NULL;

    dmessage("zeroing...");
    memset(addr,0, final_size);

    dfleave();
    return addr;
}

void freex(void* block) {
    dfenter();

    if(block == NULL)
        return;

    block_header* current_block = (block_header*)block - sizeof(block_header);
    dvalue(current_block->block_size);
    
    current_block->block_is_free = 1;
 
    dfleave();
}
