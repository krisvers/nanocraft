#include <mem_utils.h>
#include <stdlib.h>
#include <assert.h>
#include <ktypes.h>

void * heap_alloc(usize size) {
	void * ptr = malloc(size);
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
