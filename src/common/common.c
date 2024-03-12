#ifndef KALOS_COMMON_NO_COMMON

#include "../../kalos.h"
#include "../../common.h"
#include <stdio.h>
#include <stdlib.h>

kalos_event_t kalos_events[kalos_events_max_len] = {
	(kalos_event_t){
		.is_pressed = 2,
		.key[0] = 0
	}
};



int kalos_events_len = 0;

#ifndef KALOS_COMMON_NO_SLEEP_MS
void kalos_sleep_ms(long long int time) {
    long long int start = kalos_get_time_ms();
	while (start + time < kalos_get_time_ms()) {
	//	asm volatile ("nop"::);
	}
}

#endif

#ifndef KALOS_COMMON_NO_READ_FILE
/// @brief open a file and return its content and its size
/// @param path a path to the file
/// @param file_size a pointer where the size of the file will be stored
/// @return the content of the file as an allocated buffer,
/// 	return NULL if there was an error, *file_size = -1 if error in 
/// 	reading file, *file_size = -2 if error on malloc
char *kalos_read_file(char *path, int *file_size) {
	FILE *f = fopen(path, "r");
	if (f == NULL) {
		*file_size = -1;
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	*file_size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *buffer = malloc(sizeof(char) * (*file_size));
	fread(buffer, sizeof(char), *file_size, f);
	return buffer;
}

#endif

kalos_pixel_t *_kalos_decode_png(unsigned char *bytes, int file_size, int *width, int *height);

#ifndef KALOS_COMMON_READ_PNG_IMAGE
kalos_surface_t kalos_read_png_image(char *path) {
	int file_size = 0;
	char *bytes = kalos_read_file(path, &file_size);
	kalos_surface_t res;
	res.height = 0;
	res.width = 0;
	res.pixels = _kalos_decode_png(bytes, file_size, &res.width, &res.height);
	free(bytes);
	if (res.pixels == NULL) {
		res.width = -1;
		res.height = -1;
	}
	return res;
}

#endif


kalos_pixel_t *_kalos_decode_png(unsigned char *bytes, int file_size, int *width, int *height) {
	//check signature
	unsigned char signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
	if (file_size < 7)
		return NULL;
	for (int i = 0; i < 8; i++) {
		if (signature[i] != bytes[i])
			return NULL;
	}
}


#endif