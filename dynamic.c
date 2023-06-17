#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define FILENAME "./exe.so"
#define METHOD RTLD_NOW
#define ENTRY_SYMBOL "entry"

typedef int (* entry_f)(void);

entry_f entry;

void * open(void) {
	void * h = dlopen(FILENAME, METHOD);
	if (h == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		abort();
	}

	return h;
}

entry_f load_entry(void * handle) {
	entry_f e;
	*((void **) &e) = dlsym(handle, ENTRY_SYMBOL);
	if (e == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		abort();
	}

	return e;
}

void * handle;

void run_loop(void) {
	handle = open();
	entry = load_entry(handle);

	int ret;
reload:
	ret = entry();
	switch (ret) {
		case 1:
			dlclose(handle);
			entry = NULL;
			handle = NULL;
			puts("Press any key to reload!");
			getchar();
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
	run_loop();
	puts("Exiting");

	return 0;
}
