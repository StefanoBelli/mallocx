# A simple malloc implementation
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
