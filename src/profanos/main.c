#include "../../kalos.h"
#include <stdlib.h>


int kalos_width = 400;
int kalos_height = 400;

char *buffer = NULL;
uint32_t *fb = 0;
uint32_t pitch = 0;

#define _pixel_pos(x, y) (x + y * kalos_width)

int kalos_init() {
    fb = c_vesa_get_fb();
    pitch = c_vesa_get_pitch();
	buffer = malloc(kalos_height * kalos_width * sizeof(char) * 4);
	for(int x = 0; x < kalos_width; x++) {
		for(int y = 0; y < kalos_height; y++) {
			buffer[_pixel_pos(x, y)] = 0;
		}
	}
}

void kalos_update_window() {
    for(int x = 0; x < kalos_width; x++) {
		for(int y = 0; y < kalos_height; y++) {
			fb[x + y * pitch] = buffer[_pixel_pos(x, y)];
		}
	}
}

void kalos_fill_window(unsigned char r, unsigned char g, unsigned char b) {
	for(int x = 0; x < kalos_width; x++) {
		for(int y = 0; y < kalos_height; y++) {
			buffer[_pixel_pos(x, y)] = (_Pixel_t){.r = r, .g = g, .b = b};
		}
	}
}

void kalos_fill_rect(int x, int y, int h, int w, unsigned char r, unsigned char g, unsigned char b) {
	for(int x1 = x; x1 < x + w; x1++) {
		for(int y1 = y; y1 < y + h; y1++) {
			buffer[_pixel_pos(x1, y1)] = (_Pixel_t){.r = r, .g = g, .b = b};
		}
	}
}

void kalos_draw_line(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int D = 2*dy - dx;
    int y = y1;

    for(int x = x1; x < x2; x++) {
        buffer[_pixel_pos(x, y)] = (_Pixel_t){.r = r, .g = g, .b = b};
        if (D > 0) {
            y = y + 1;
            D = D - 2*dx;
        }
        D = D + 2*dy;
    }
}

void kalos_draw_disk(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b);

void kalos_draw_circle(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b);

int kalos_get_height() {
    return kalos_height;
}

int kalos_get_width() {
    return kalos_width;
}


void kalos_set_height(int h) {
    _Pixel_t *new_buffer = calloc(kalos_width * h, sizeof(_Pixel_t));
    for(int x = 0; x < kalos_width; x++) {
        for(int y = 0; y < h; y++) {
            new_buffer[x + y * kalos_width] = buffer[_pixel_pos(x, y)]; 
        }
    }
}

void kalos_set_width(int w) {

}

void kalos_update_events() {

}

void kalos_end() {
    free(buffer);
}

long long int kalos_get_time_ms();