#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <state.h>
#include <kwindow.h>

window_t * window;
int main(int argc, char ** argv) {
	puts("Hello, World!");

	state_init();

	window = window_new("test", 800, 500, 320, 200);
	while (window->status != WINDOW_CLOSED) {
		window_update(window);
		window_poll(window);
	}
	window_delete(window);

	state_quit();

	puts("Goodbye, World!");
	return 0;
}
