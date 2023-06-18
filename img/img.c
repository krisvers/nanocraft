#include <img.h>
#include <ktypes.h>
#include <file.h>
#include <mem_utils.h>
#include <string.h>
#include <assert.h>

img_t * img_new(u32 w, u32 h, img_type_e type) {
	img_t * img = heap_alloc(sizeof(img_t));
	img->w = w;
	img->h = h;
	img->type = type;
	switch (type) {
		case IMG_TYPE_RGB:
		case IMG_TYPE_BGR:
			img->bitmap = heap_alloc(w * h * 3);
			break;
		default:
			img->bitmap = heap_alloc(w * h * 4);
			break;
	}

	return img;
}

void img_delete(img_t * img) {
	assert(img != NULL);

	heap_free(img->bitmap);
	heap_free(img);
}

void img_load_raw(img_t * img, file_t * file, img_type_e type) {
	usize size;
	u32 color;

	switch (type) {
		case IMG_TYPE_RGB:
			size = img->w * img->h * 3;
			memcpy(img->bitmap, file->buffer, size);
			img->type = IMG_TYPE_RGB;
			break;
		case IMG_TYPE_ARGB:
			size = img->w * img->h * 4;
			memcpy(img->bitmap, file->buffer, size);
			img->type = IMG_TYPE_ARGB;
			break;
		case IMG_TYPE_BGR:
			size = img->w * img->h;
			rmemcpy(img->bitmap, file->buffer, size, 3);
			img->type = IMG_TYPE_RGB;
			break;
		case IMG_TYPE_ABGR:
			size = img->w * img->h;
			rmemcpy(img->bitmap, file->buffer, size, 4);
			img->type = IMG_TYPE_ARGB;
			break;
		case IMG_TYPE_RGBA:
			size = img->w * img->h;
			for (usize i = 0; i < size; ++i) {
				color = (file->buffer[(i * 4) + 3] << 24) | (file->buffer[(i * 4) + 0]) | (file->buffer[(i * 4) + 1] << 8) | (file->buffer[(i * 4) + 2] << 16);
				((u32 *) img->bitmap)[i] = color;
			}
			img->type = IMG_TYPE_ARGB;
			break;
		case IMG_TYPE_BGRA:
			size = img->w * img->h;
			for (usize i = 0; i < size; ++i) {
				color = (file->buffer[(i * 4) + 3] << 24) | (file->buffer[(i * 4) + 2]) | (file->buffer[(i * 4) + 1] << 8) | (file->buffer[(i * 4) + 0] << 16);
				((u32 *) img->bitmap)[i] = color;
			}
			img->type = IMG_TYPE_ARGB;
			break;
		default:
			break;
	}
}
