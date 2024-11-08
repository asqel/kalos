#ifndef KALOS_H
#define KALOS_H

#if !defined(__WIN32) && !defined(__linux__)
	#define KALOS_UNSUPPORTED
#endif

#define KALOS_INIT_FAIL 1
#define KALOS_INIT_SUCCESS 0

#define KEY_ESC 1
#define KEY_CTRL_L 2
#define KEY_CTRL_R 3
#define KEY_ALT 4
#define KEY_ARROW_UP 5
#define KEY_ARROW_DOWN 6
#define KEY_ARROW_LEFT 7
#define KEY_ARROW_RIGHT 8
#define KEY_ENTER 9
#define KEY_ERASE 10
#define KEY_SHIFT 11

typedef struct kalos_event_s{
	char key[5];
	char is_pressed; // 0 :key_released, 1 :key_pressed, 2 :end_of_events
	// 3 :special_key_pressed (key[0] == key)(esc, shift...)
	// 4 :special_key_released (key[0] == key)(esc, shift...)
}kalos_event_t;

#define kalos_events_max_len 300

extern kalos_event_t kalos_events[kalos_events_max_len];
extern int kalos_events_len;

typedef struct kalos_pixel_s {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}kalos_pixel_t;

typedef struct kalos_surface_s {
	kalos_pixel_t *pixels;
	int height;
	int width;
} kalos_surface_t;

#define kalos_pixel_pos(x, y, surface) ((x) + (y) * (surface).width)


int kalos_init();

void kalos_update_window();

//void kalos_set_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
void kalos_fill_window(unsigned char r, unsigned char g, unsigned char b);

void kalos_fill_rect(int x, int y, int h, int w, unsigned char r, unsigned char g, unsigned char b);

void kalos_draw_line(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);

void kalos_draw_disk(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b);

void kalos_draw_circle(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b);

int kalos_get_height();

int kalos_get_width();

void kalos_set_height(int h);

void kalos_set_width(int w);

void kalos_set_dimensions(int w, int h);

void kalos_update_events();

void kalos_end();

long long int kalos_get_time_ms();

void kalos_sleep_ms(long long int time);

int kalos_init();

kalos_event_t kalos_oldes_event();


// here we define macros or variable (if their are not listed below, their are internals)
/*
macro functions:
	their are defined as macro function for speed

	set_pixel_u32(x, y, col)
		set a pixel at (x, y) to the colour col in rgb hex (0xRRGGBB)

*/
#ifdef __profanOS__
	#include <type.h>


	extern int kalos_width;
	extern int kalos_height;

	extern char *buffer;
	extern uint32_t *fb;
	extern uint32_t pitch;
	#define set_pixel_u32(x, y, col) ((x >= kalos_width|| y >= kalos_width) ? (0) : (((uint32_t *)buffer)[x + y * kalos_width] = col))
	buffer[_pixel_pos(x, y)] = (_Pixel_t){.r = r, .g = g, .b = b};

#elif __linux__
	#include <stdint.h>
	extern int kalos_width;
	extern int kalos_height;
	extern uint32_t *kalos_buffer_ptr;
	#define set_pixel_u32(x, y, col) ((x >= kalos_width|| y >= kalos_width) ? (0) : ((kalos_buffer_ptr)[x + y * kalos_width] = col))

#elif __WIN32

#else
#error "kalos unsuported for this os"

#endif



#endif

