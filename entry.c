#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <state.h>
#include <kwindow.h>

window_t * window;
int entry(void) {
	puts("eeee");

	state_init();

	window = window_new("test", 800, 500, 320, 200);
	while (window->status != WINDOW_CLOSED && window->status != WINDOW_RELOAD) {
		window_update(window);
		window_poll(window);
	}

	if (window->status == WINDOW_RELOAD) {
		window_delete(window);
		state_quit();

		return 1;
	}

	window_delete(window);
	state_quit();

	puts("Goodbye, World!");
	return 0;
}
