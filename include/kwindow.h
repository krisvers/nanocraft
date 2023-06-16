#ifndef KWINDOW_H
#define KWINDOW_H

#include <SDL2/SDL.h>
#include <ktypes.h>

typedef enum {
	WINDOW_CLOSED = -1,
	WINDOW_DEFAULT = 0,
} window_status_e;

typedef struct Window {
	char * name;
	u32 w;
	u32 h;
	u32 tw;
	u32 th;
	f32 scale;
	u8 * fb;
	window_status_e status;
	void (* key_callback)(struct Window * win, u8 type, u16 key, u16 mod);
	void (* quit_callback)(struct Window * win);
	SDL_Window * _sdl_window;
	SDL_Surface * _sdl_surface;
	SDL_Event _sdl_event;
} window_t;

typedef void (* window_key_f)(window_t * win, u8 type, u16 key, u16 mod);
typedef void (* window_quit_f)(window_t * win);

window_t * window_new(char * name, u32 win_w, u32 win_h, u32 fb_w, u32 fb_h);
void window_update(window_t * win);
void window_poll(window_t * win);
void window_delete(window_t * win);
void window_close(window_t * win);

#endif
