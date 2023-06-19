#ifndef IMG_TGA_H
#define IMG_TGA_H

#include <ktypes.h>
#include <img.h>

#define TGA_HEADER_SIZE (18)

typedef struct TGAHeader {
	u8 id_len;
	u8 color_map_type;
	u8 img_type;
	u16 color_map_origin;
	u16 color_map_len;
	u8 color_map_depth;
	u16 img_x_origin;
	u16 img_y_origin;
	u16 img_w;
	u16 img_h;
	u8 bpp;
	u8 img_desc;
} __attribute__((packed)) tga_header_t;

typedef struct TGAMapData {
	u8 id_len;
	u16 color_map_origin;
	u16 color_map_len;
	u8 color_map_depth;
	u16 img_x_origin;
	u16 img_y_origin;
	u16 img_w;
	u16 img_h;
	u8 bpp;
	u8 img_desc;
} tga_map_data_t;

typedef struct TGAExtension {
	u16 extension_size;
	char author_name[41];
	char author_comment[324];
	u8 time_stamp[12];
	u8 job_id[41];
	u8 job_time[6];
	u8 software_id[41];
	u8 software_version[3];
	u32 key_color;
	u32 aspect_ratio;
	u32 gamma_value;
	u32 color_correction_offset;
	u32 postage_stamp_offset;
	u32 scan_line_offset;
	u8 attributes_type;
} tga_extension_t;

typedef struct TGAFooter {
	u32 extension_offset;
	u32 dev_offset;
	char sig[16];
	char period;
	char nul;
} tga_footer_t;

typedef struct TGAImg {
	tga_header_t header;
	img_t * img;
} tga_t;

tga_t * tga_new(img_t * img);
void tga_delete(tga_t * tga);
tga_t * tga_load(file_t * file);
void tga_save(tga_t * tga, file_t * file);

#endif
