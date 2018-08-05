#ifndef SSYNX_MALLOCX_H
#define SSYNX_MALLOCX_H

#include <sys/types.h>

#if defined(__cplusplus)
extern "C" {
#endif 

void* mallocx(size_t size);
void* callocx(size_t nmemb, size_t size);
void freex(void* ptr);

#if defined(__cplusplus)
}
#endif

#endif //SSYNX_MALLOCX_H
