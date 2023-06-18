#ifndef IMG_H
#define IMG_H

#include <ktypes.h>
#include <file.h>

typedef enum ImgType {
	IMG_TYPE_RGB = 0,
	IMG_TYPE_BGR,
	IMG_TYPE_ARGB,
	IMG_TYPE_ABGR,
	IMG_TYPE_RGBA,
	IMG_TYPE_BGRA
} img_type_e;

typedef struct Img {
	u8 * bitmap;
	u32 w;
	u32 h;
	img_type_e type;
} img_t;

img_t * img_new(u32 w, u32 h, img_type_e type);
void img_delete(img_t * img);
void img_load_raw(img_t * img, file_t * file, img_type_e type);

#endif
