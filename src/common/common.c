#include "kalos.h"
#include <stdio.h>
#include <stdlib.h>

kalos_event_t kalos_events[kalos_events_max_len] = {0};
kalos_surface_t *I_kalos_win_buffer = NULL;
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

kalos_surface_t *kalos_init(int w, int h) {
	kalos_surface_t *surface = malloc(sizeof(kalos_surface_t));
	if (surface == NULL) {
		return NULL;
	}
	surface->I_width = w;
	surface->I_height = h;
	surface->pixels = malloc(sizeof(uint32_t) * w * h);
	if (surface->pixels == NULL) {
		free(surface);
		return NULL;
	}
	I_kalos_win_buffer = surface;
	if (I_kalos_init(w, h) != 0) {
		free(surface);
		I_kalos_win_buffer = NULL;
		return NULL;
	}
	kalos_events_len = 0;
	return surface;
}

void kalos_exit() {
	I_kalos_exit();
	if (I_kalos_win_buffer != NULL) {
		free(I_kalos_win_buffer->pixels);
		free(I_kalos_win_buffer);
		I_kalos_win_buffer = NULL;
	}
}

int I_kalos_append_event(kalos_event_t event) {
	if (kalos_events_len >= kalos_events_max_len) {
		return 1;
	}
	kalos_events[kalos_events_len] = event;
	kalos_events_len++;
	return 0;
}

void kalos_get_events(kalos_event_t **ev, int *len) {
	*ev = (kalos_event_t *)kalos_events;
	*len = kalos_events_len;
}

int kalos_set_dimensions(int w, int h) {
	if (I_kalos_set_dimensions(w, h) != 0) {
		return 1;
	}
	uint32_t *new_pixels = malloc(sizeof(uint32_t) * w * h);
	if (new_pixels == NULL) {
		return 1;
	}
	for (int i = 0; i < w * h; i++) {
		new_pixels[i] = 0;
	}
	for (int x = 0; x < I_kalos_win_buffer->I_width; x++) {
		for (int y = 0; y < I_kalos_win_buffer->I_height; y++) {
			if (x < w && y < h) {
				new_pixels[x + y * w] = I_kalos_win_buffer->pixels[x + y * I_kalos_win_buffer->I_width];
			}
		}
	}
	free(I_kalos_win_buffer->pixels);
	I_kalos_win_buffer->pixels = new_pixels;
	I_kalos_win_buffer->I_width = w;
	I_kalos_win_buffer->I_height = h;
	return 0;
}