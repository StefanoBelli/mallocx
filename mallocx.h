#ifndef SSYNX_MALLOCX_H
#define SSYNX_MALLOCX_H

// TODO
//describe here how they work...
#include <sys/types.h>

#if defined(__cplusplus)
extern "C" {
#endif 

void* mallocx(size_t size);
void* callocx(size_t nmemb, size_t size);
void* reallocx(void* oldptr, size_t newsize);
void freex(void* ptr);

#if defined(__cplusplus)
}
#endif

#endif //SSYNX_MALLOCX_H
