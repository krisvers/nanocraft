#include <gfx/render.h>
#include <kwindow.h>
#include <ktypes.h>
#include <assert.h>

#define RENDER_WIN_RET(x) { if (window == NULL) { return x; } }
#define RENDER_WIN_RET_VOID() { if (window == NULL) { return; } }
#define RENDER_WIN_RET_VOID_C(condition) { if (window == NULL || condition) { return; } }
#define RENDER_TRANS_COLOR 0xFF11FF

#define RENDER_PIXEL(x, y, color) { if (color == RENDER_TRANS_COLOR) { return; } ((u32 *) window->fb)[(((u32) x) + (((u32) y) * window->w))] = color; }
#define RENDER_PIXEL_ARGB(x, y, color) { if ((color & 0xFF000000) == 0xFF000000) { return; } ((u32 *) window->fb)[(((u32) x) + (((u32) y) * window->w))] = color; }

static window_t * window;

void render_bind_window(window_t * win) {
	window = win;
}

void render_raw_pixel(u32 x, u32 y, u32 color) {
	RENDER_WIN_RET_VOID_C(x >= window->w || y >= window->h);

	assert(window->fb != NULL);
	RENDER_PIXEL(x, y, color);
}

void render_pixel(u32 x, u32 y, u32 color) {
	RENDER_WIN_RET_VOID_C(x >= window->tw || y >= window->th);

	assert(window->fb != NULL);
	for (u32 h = 0; h < window->scale; ++h) {
		for (u32 w = 0; w < window->scale; ++w) {
			RENDER_PIXEL((x * window->scale) + w, (y * window->scale) + h, color);
		}
	}
}

void render_rectangle(u32 x, u32 y, u32 w, u32 h, u32 color) {
	RENDER_WIN_RET_VOID_C(x >= window->tw || y >= window->th);

	assert(window->fb != NULL);
	for (u32 v = 0; v < h; ++v) {
		for (u32 u = 0; u < w; ++u) {
			render_pixel(x + u, y + v, color);
		}
	}
}

void render_texture_rgb(u32 x, u32 y, u32 w, u32 h, u8 * tex) {
	RENDER_WIN_RET_VOID_C(x >= window->tw || y >= window->th);

	assert(window->fb != NULL);
	assert(tex != NULL);
#ifdef RENDER_DEBUG
	render_rectangle(x, y, w, h, 0xFF00FF);
	window_update(window);
#endif

#ifdef RENDER_SLOW
	for (u64 t = 0; t < 0xFFFFF; ++t);
#endif

	u8 r;
	u8 g;
	u8 b;
	u32 rgb;
	for (u32 v = 0; v < h; ++v) {
		for (u32 u = 0; u < w; ++u) {
			r = tex[(u + (v * w)) * 3 + 0];
			g = tex[(u + (v * w)) * 3 + 1];
			b = tex[(u + (v * w)) * 3 + 2];
			rgb = (r << 16) | (g << 8) | (b);
			render_pixel(x + u, y + v, rgb);
		}
	}
}

void render_texture_bgr(u32 x, u32 y, u32 w, u32 h, u8 * tex) {
	RENDER_WIN_RET_VOID_C(x >= window->tw || y >= window->th);

	assert(window->fb != NULL);
	assert(tex != NULL);
#ifdef RENDER_DEBUG
	render_rectangle(x, y, w, h, 0xFF00FF);
	window_update(window);
#endif

#ifdef RENDER_SLOW
	for (u64 t = 0; t < 0xFFFFF; ++t);
#endif

	u8 r;
	u8 g;
	u8 b;
	u32 rgb;
	for (u32 v = 0; v < h; ++v) {
		for (u32 u = 0; u < w; ++u) {
			r = tex[(u + (v * w)) * 3 + 2];
			g = tex[(u + (v * w)) * 3 + 1];
			b = tex[(u + (v * w)) * 3 + 0];
			rgb = (r << 16) | (g << 8) | (b);
			render_pixel(x + u, y + v, rgb);
		}
	}
}

void render_texture_argb(u32 x, u32 y, u32 w, u32 h, u8 * tex) {
	RENDER_WIN_RET_VOID_C(x >= window->tw || y >= window->th);

	assert(window->fb != NULL);
	assert(tex != NULL);
#ifdef RENDER_DEBUG
	render_rectangle(x, y, w, h, 0xFF00FF);
	window_update(window);
#endif

#ifdef RENDER_SLOW
	for (u64 t = 0; t < 0xFFFFF; ++t);
#endif

	u8 a;
	u8 r;
	u8 g;
	u8 b;
	u32 rgb;
	for (u32 v = 0; v < h; ++v) {
		for (u32 u = 0; u < w; ++u) {
			a = tex[(u + (v * w)) * 4 + 0];
			if (a == 0) {
				continue;
			}
			r = tex[(u + (v * w)) * 4 + 1];
			g = tex[(u + (v * w)) * 4 + 2];
			b = tex[(u + (v * w)) * 4 + 3];
			rgb = (r << 16) | (g << 8) | (b);
			render_pixel(x + u, y + v, rgb);
		}
	}
}

void render_texture_abgr(u32 x, u32 y, u32 w, u32 h, u8 * tex) {
	RENDER_WIN_RET_VOID_C(x >= window->tw || y >= window->th);

	assert(window->fb != NULL);
	assert(tex != NULL);
#ifdef RENDER_DEBUG
	render_rectangle(x, y, w, h, 0xFF00FF);
	window_update(window);
#endif

#ifdef RENDER_SLOW
	for (u64 t = 0; t < 0xFFFFF; ++t);
#endif

	u8 a;
	u8 r;
	u8 g;
	u8 b;
	u32 rgb;
	for (u32 v = 0; v < h; ++v) {
		for (u32 u = 0; u < w; ++u) {
			a = tex[(u + (v * w)) * 4 + 0];
			if (a == 0) {
				continue;
			}
			r = tex[(u + (v * w)) * 4 + 3];
			g = tex[(u + (v * w)) * 4 + 2];
			b = tex[(u + (v * w)) * 4 + 1];
			rgb = (r << 16) | (g << 8) | (b);
			render_pixel(x + u, y + v, rgb);
		}
	}
}

void render_texture_rgba(u32 x, u32 y, u32 w, u32 h, u8 * tex) {
	RENDER_WIN_RET_VOID_C(x >= window->tw || y >= window->th);

	assert(window->fb != NULL);
	assert(tex != NULL);
#ifdef RENDER_DEBUG
	render_rectangle(x, y, w, h, 0xFF00FF);
	window_update(window);
#endif

#ifdef RENDER_SLOW
	for (u64 t = 0; t < 0xFFFFF; ++t);
#endif

	u8 a;
	u8 r;
	u8 g;
	u8 b;
	u32 rgb;
	for (u32 v = 0; v < h; ++v) {
		for (u32 u = 0; u < w; ++u) {
			a = tex[(u + (v * w)) * 4 + 3];
			if (a == 0) {
				continue;
			}
			r = tex[(u + (v * w)) * 4 + 0];
			g = tex[(u + (v * w)) * 4 + 1];
			b = tex[(u + (v * w)) * 4 + 2];
			rgb = (r << 16) | (g << 8) | (b);
			render_pixel(x + u, y + v, rgb);
		}
	}
}

void render_texture_bgra(u32 x, u32 y, u32 w, u32 h, u8 * tex) {
	RENDER_WIN_RET_VOID_C(x >= window->tw || y >= window->th);

	assert(window->fb != NULL);
	assert(tex != NULL);
#ifdef RENDER_DEBUG
	render_rectangle(x, y, w, h, 0xFF00FF);
	window_update(window);
#endif

#ifdef RENDER_SLOW
	for (u64 t = 0; t < 0xFFFFF; ++t);
#endif

	u8 a;
	u8 r;
	u8 g;
	u8 b;
	u32 rgb;
	for (u32 v = 0; v < h; ++v) {
		for (u32 u = 0; u < w; ++u) {
			a = tex[(u + (v * w)) * 4 + 3];
			if (a == 0) {
				continue;
			}
			r = tex[(u + (v * w)) * 4 + 2];
			g = tex[(u + (v * w)) * 4 + 1];
			b = tex[(u + (v * w)) * 4 + 0];
			rgb = (r << 16) | (g << 8) | (b);
			render_pixel(x + u, y + v, rgb);
		}
	}
}
