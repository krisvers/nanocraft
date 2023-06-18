#ifndef RENDER_H
#define RENDER_H

#include <kwindow.h>
#include <ktypes.h>

void render_bind_window(window_t * win);
void render_raw_pixel(u32 x, u32 y, u32 color);
void render_pixel(u32 x, u32 y, u32 color);
void render_rectangle(u32 x, u32 y, u32 w, u32 h, u32 color);
void render_texture_rgb(u32 x, u32 y, u32 w, u32 h, u8 * tex);

#endif
