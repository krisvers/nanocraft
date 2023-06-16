#include <kwindow.h>
#include <assert.h>
#include <ktypes.h>
#include <mem_utils.h>
#include <stdio.h>

static void window_key_callback_default(window_t * win, u8 type, u16 key, u16 mod);
static void window_quit_callback_default(window_t * win);

window_t * window_new(char * name, u32 win_w, u32 win_h, u32 fb_w, u32 fb_h) {
	window_t * win = heap_alloc(sizeof(window_t));
	win->name = name;
	win->w = win_w;
	win->h = win_h;
	win->tw = fb_w;
	win->th = fb_h;
	win->scale = win_h / (float) fb_h;
	win->key_callback = window_key_callback_default;
	win->quit_callback = window_quit_callback_default;

	win->_sdl_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, 0);
	if (win->_sdl_window == NULL) {
		fprintf(stderr, "SDL error: %s\n", SDL_GetError());
		abort();
	}

	win->_sdl_surface = SDL_GetWindowSurface(win->_sdl_window);
	if (win->_sdl_surface == NULL) {
		fprintf(stderr, "SDL error: %s\n", SDL_GetError());
		abort();
	}

	win->fb = win->_sdl_surface->pixels;
	if (win->_sdl_surface == NULL) {
		fprintf(stderr, "SDL error: %s\n", SDL_GetError());
		abort();
	}

	return win;
}

void window_delete(window_t * win) {
	assert(win != NULL);

	heap_free(win);
}

void window_close(window_t * win) {
	assert(win != NULL);
	assert(win->_sdl_window != NULL);
	
	SDL_DestroyWindow(win->_sdl_window);
	win->status = WINDOW_CLOSED;
}

void window_update(window_t * win) {
	assert(win != NULL);
	assert(win->_sdl_window != NULL);
	assert(win->_sdl_surface != NULL);

	SDL_UpdateWindowSurface(win->_sdl_window);
}

void window_poll(window_t * win) {
	assert(win != NULL);
	assert(win->_sdl_window != NULL);

	SDL_PollEvent(&win->_sdl_event);
	switch (win->_sdl_event.type) {
		case SDL_KEYDOWN:
			win->key_callback(win, 1, win->_sdl_event.key.keysym.sym, win->_sdl_event.key.keysym.mod);
			break;
		case SDL_KEYUP:
			win->key_callback(win, 0, win->_sdl_event.key.keysym.sym, win->_sdl_event.key.keysym.mod);
			break;
		case SDL_QUIT:
			win->quit_callback(win);
	}
}

static void window_key_callback_default(window_t * win, u8 type, u16 key, u16 mod) {
	assert(win != NULL);
	printf("window %s: %u, %u, %u\n", win->name, type, key, mod);
}

static void window_quit_callback_default(window_t * win) {
	window_close(win);
}
