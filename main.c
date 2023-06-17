#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define FILENAME "./exe.so"
#define METHOD RTLD_NOW
#define ENTRY_SYMBOL "entry"

typedef int (* entry_f)(void);

void * open(void) {
	void * h = dlopen(FILENAME, METHOD);
	if (h == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		abort();
	}

	return h;
}

entry_f load_entry(void * handle) {
	entry_f entry;
	*((void **) &entry) = dlsym(handle, ENTRY_SYMBOL);
	if (entry == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		abort();
	}

	return entry;
}

void * handle;

void run_loop(entry_f entry) {
reload:
	switch (entry()) {
		case 1:
			dlclose(handle);
			handle = open();
			entry = load_entry(handle);
			goto reload;
		default:
			dlclose(handle);
			return;
	}
}

int main(void) {
	puts("Loading game");
	handle = open();

	puts("Loading entry");
	entry_f entry;
	entry = load_entry(handle);

	run_loop(entry);

	return 0;
}
