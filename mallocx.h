#ifndef SSYNX_MALLOCX_H
#define SSYNX_MALLOCX_H

#include <sys/types.h>

void* mallocx(size_t size);
void freex(void* ptr);

#endif //SSYNX_MALLOCX_H