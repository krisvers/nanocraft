#include <file.h>
#include <stdio.h>
#include <stdlib.h>
#include <mem_utils.h>

file_t * file_open(char * filename) {
	FILE * fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "file_open(filename): file \"%s\" can't be found\n", filename);
		abort();
	}

	file_t * file = heap_alloc(sizeof(file_t));

	fseek(fp, 0L, SEEK_END);
	file->len = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	file->buffer = heap_alloc(file->len);
	file->name = filename;

	fread(file->buffer, file->len, 1, fp);
	fclose(fp);

	return file;
}

file_t * file_new(char * filename) {
	FILE * fp = fopen(filename, "w");
	fclose(fp);

	file_t * file = heap_alloc(sizeof(file_t));
	file->len = 0;
	file->buffer = NULL;
	file->name = filename;

	return file;
}

void file_delete(file_t * file) {
	remove(file->name);
	file_close(file);
}

void file_close(file_t * file) {
	if (file->buffer != NULL) {
		heap_free(file->buffer);
	}
	heap_free(file);
}

void file_read(file_t * file) {
	FILE * fp = fopen(file->name, "r");
	if (fp == NULL) {
		fprintf(stderr, "file_read(file): file \"%s\" can't be found\n", file->name);
		abort();
	}

	fseek(fp, 0L, SEEK_END);
	file->len = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	if (file->len != 0) {
		if (file->buffer == NULL) {
			file->buffer = heap_alloc(file->len);
		} else {
			file->buffer = heap_realloc(file->buffer, file->len);
		}

		fread(file->buffer, file->len, 1, fp);
	}

	fclose(fp);
}

void file_write(file_t * file) {
	FILE * fp = fopen(file->name, "w");

	fwrite(file->buffer, file->len, 1, fp);
	fclose(fp);
}

void file_print(file_t * file) {
	for (usize i = 0; i < file->len; ++i) {
		putchar(file->buffer[i]);
	}
}
