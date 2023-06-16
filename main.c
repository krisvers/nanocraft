#include <stdio.h>
#include <kwindow.h>

window_t * window;
int main(void) {
	puts("Hello, World!");

	window = window_new("test", 800, 500, 320, 200);

	while (window->status != WINDOW_CLOSED) {
		window_update(window);
		window_poll(window);
	}

	window_delete(window);

	puts("Goodbye, World!");
	return 0;
}
