#include <img/tga.h>
#include <img.h>
#include <file.h>
#include <ktypes.h>
#include <mem_utils.h>
#include <string.h>
#include <stdio.h>

tga_t * tga_new(img_t * img) {
	tga_t * tga = heap_alloc(sizeof(tga_t));
	tga->header.id_len = 0x00;
	tga->header.color_map_type = 0x00;
	tga->header.img_type = 0x02;
	tga->header.color_map_origin = 0x0000;
	tga->header.color_map_len = 0x0000;
	tga->header.color_map_depth = 0x00;
	tga->header.img_x_origin = 0x00;
	tga->header.img_y_origin = 0x00;
	tga->header.img_w = img->w;
	tga->header.img_h = img->h;
	switch (img->type) {
		case IMG_TYPE_RGB:
		case IMG_TYPE_BGR:
			tga->header.bpp = 24;
			break;
		case IMG_TYPE_ARGB:
		default:
			tga->header.bpp = 32;
			break;
	}
	tga->header.img_desc = 0x08;

	tga->img = heap_alloc(sizeof(img_t));
	tga->img->bitmap = heap_alloc(tga->header.img_w * tga->header.img_h * (tga->header.bpp / 8));
	tga->img->w = tga->header.img_w;
	tga->img->h = tga->header.img_h;
	memcpy(tga->img->bitmap, img->bitmap, tga->img->w * tga->img->h * (tga->header.bpp / 8));
	tga->img->type = img->type;

	return tga;
}

void tga_delete(tga_t * tga) {
	heap_free(tga->img->bitmap);
	heap_free(tga->img);
	heap_free(tga);
}

tga_t * tga_load(file_t * file) {
	tga_t * tga = heap_alloc(sizeof(tga_t));

	memcpy(&tga->header, file->buffer, TGA_HEADER_SIZE);

	tga->img = heap_alloc(sizeof(img_t));
	tga->img->w = tga->header.img_w;
	tga->img->h = tga->header.img_h;
	tga->img->type = IMG_TYPE_BGRA;

	usize size;
	// bytes per pixel
	u8 bpp;
	switch (tga->img->type) {
		case IMG_TYPE_RGB:
		case IMG_TYPE_BGR:
			bpp = 3;
			size = tga->img->w * tga->img->h * 3;
			break;
		case IMG_TYPE_ARGB:
		case IMG_TYPE_ABGR:
		case IMG_TYPE_RGBA:
		case IMG_TYPE_BGRA:
			bpp = 4;
			size = tga->img->w * tga->img->h * 4;
			break;
		case IMG_TYPE_GREY:
			bpp = 1;
			size = tga->img->w * tga->img->h;
			break;
		default:
			printf("tga_load(file): invalid IMG type\n");
	}

	tga->img->bitmap = heap_alloc(size);

	//memcpy(tga->img->bitmap, file->buffer + (file->len - size), size);
	for (u16 h = 0; h < tga->img->h; ++h) {
		for (u16 w = 0; w < tga->img->w; ++w) {
			for (u8 b = 0; b < bpp; ++b) {
				tga->img->bitmap[(w + (h * tga->img->w)) * bpp + b] = file->buffer[(file->len - size) + (w + ((-1 * h + (tga->img->h - 1)) * tga->img->w)) * bpp + b];
			}
		}
	}

	return tga;
}

void tga_save(tga_t * tga, file_t * file) {
	file->len = TGA_HEADER_SIZE + (tga->img->w * tga->img->h * (tga->header.bpp / 8));
	file->buffer = heap_realloc(file->buffer, file->len);

	memcpy(file->buffer, &tga->header, TGA_HEADER_SIZE);
	rmemcpy(file->buffer + TGA_HEADER_SIZE, tga->img->bitmap, tga->header.bpp / 8, file->len - TGA_HEADER_SIZE);

	file_write(file);
}
