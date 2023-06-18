#include <mem_utils.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ktypes.h>

void * heap_alloc(usize size) {
	void * ptr = malloc(size);
	assert(ptr != NULL);

	return ptr;
}

void * heap_realloc(void * ptr, usize size) {
	ptr = realloc(ptr, size);
	assert(ptr != NULL);

	return ptr;
}

void * heap_allocarray(usize nmemb, usize size) {
	void * ptr = malloc(nmemb * size);
	assert(ptr != NULL);

	return ptr;
}

void * heap_free(void * ptr) {
	assert(ptr != NULL);
	free(ptr);

	return NULL;
}

void rmemcpy(void * dst, void * src, usize nmemb, usize mem_size) {
	u8 * d = dst;
	u8 * s = src;

	for (usize i = 0; i < nmemb; ++i) {
		for (ssize j = mem_size - 1; j > 0; --j) {
			d[(i * mem_size) + j] = s[(i * mem_size) + j];
		}
	}
}
