#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <state.h>
#include <gfx/render.h>
#include <kwindow.h>
#include <file.h>
#include <img.h>
#include <img/tga.h>

#define CLOSE() { window_delete(window); state_quit(); }

u8 texture[] = {
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
	0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

window_t * window;
int entry(void) {
	puts("Program is running!");

	state_init();

	file_t * file = file_open("a.tga");
	file_read(file);
	tga_t * tga = tga_load(file);
	file_close(file);

	window = window_new("test", 1200, 900, 300, 225);
	render_bind_window(window);
	while (window->status != WINDOW_CLOSED && window->status != WINDOW_RELOAD) {
		render_pixel(20, 20, 0xFF00FF);
		img_render(0, 0, tga->img);
		window_update(window);
		window_poll(window);
	}

	tga_delete(tga);

	if (window->status == WINDOW_RELOAD) {
		CLOSE();
		puts("Program reloading!\n");
		return 1;
	}

	CLOSE();

	puts("Program exiting!\n");
	return 0;
}
