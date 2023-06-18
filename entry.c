#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <state.h>
#include <render.h>
#include <kwindow.h>
#include <file.h>
#include <img.h>

#define CLOSE() { window_delete(window); state_quit(); }

u8 texture[12] = {
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
};

window_t * window;
int entry(void) {
	puts("Program is running!");

	state_init();

	file_t * file = file_open("test.txt");
	img_t * test = img_new(2, 4, IMG_TYPE_BGR);
	img_load_raw(test, file, IMG_TYPE_BGR);
	file_close(file);

	window = window_new("test", 1200, 900, 300, 225);
	render_bind_window(window);
	while (window->status != WINDOW_CLOSED && window->status != WINDOW_RELOAD) {
		render_pixel(20, 20, 0xFF00FF);
		render_texture_rgb(0, 0, 2, 4, test->bitmap);
		window_update(window);
		window_poll(window);
	}

	img_delete(test);

	if (window->status == WINDOW_RELOAD) {
		CLOSE();
		puts("Program reloading!\n");
		return 1;
	}

	CLOSE();

	puts("Program exiting!\n");
	return 0;
}
