#ifndef IMG_TGA_H
#define IMG_TGA_H

#include <ktypes.h>
#include <img.h>

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
} tga_header_t;

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

typedef struct TGADeveloper {
	
} tga_developer_t;

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
	u32 scan_line offset;
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
	tga_extension_t extension;
	tga_footer_t footer;
	img_t * img;
} tga_img_t;

#endif
