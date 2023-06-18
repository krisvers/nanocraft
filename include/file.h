#ifndef FILE_H
#define FILE_H

#include <ktypes.h>

typedef struct File {
	u8 * buffer;
	usize len;
	char * name;
} file_t;

file_t * file_open(char * filename);
file_t * file_new(char * filename);
void file_delete(file_t * file);
void file_close(file_t * file);
void file_read(file_t * file);
void file_write(file_t * file);
void file_print(file_t * file);

#endif
