#include "mallocx.h"

int main() {
    void* a = mallocx(19);
    *(int*) a = 10;
    freex(a);
    void* b = mallocx(10);

    printf("%x\n", *(int*)b);

    freex(b);

    return 0;
}
