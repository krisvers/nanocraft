#ifndef MEM_UTILS
#define MEM_UTILS

#include <ktypes.h>

void * heap_alloc(usize size);
void * heap_realloc(void * ptr, usize size);
void * heap_allocarray(usize nmemb, usize size);
void * heap_free(void * ptr);
void rmemcpy(void * dst, void * src, usize nmemb, usize mem_size);

#endif
