#include "kalos.h"
#include <stdio.h>
#include <stdlib.h>

kalos_event_t kalos_events[kalos_events_max_len] = {
	(kalos_event_t){
		.is_pressed = 2,
		.key[0] = 0
	}
};

int kalos_events_len = 0;

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
