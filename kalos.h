#ifndef KALOS_H
#define KALOS_H

// Symbols prefixed with I should only be read/write by the lib

#include <stdint.h>

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

typedef struct kalos_surface_s {
	uint32_t *pixels; // this can be modified by the user (access: [x + y * .I_width])
	int I_height; // this should only be read by the user
	int I_width; // also this
} kalos_surface_t;

extern kalos_surface_t *I_kalos_win_buffer;

void I_kalos_init();
void I_kalos_exit();
void kalos_update_window();
void kalos_set_height(int h);
void kalos_set_width(int w);
void kalos_set_dimensions(int w, int h);
void kalos_update_events();
long long int kalos_get_time_ms();
void kalos_sleep_ms(long long int time);

#undef KALOS_OS

#ifdef __profanOS__
	#define KALO_OS "profanOS"
#elif __linux__
	#define KALOS_OS "linux"
#elif __WIN32
	#define KALOS_OS "windows"
	#error "kalos is supported for now (but it is planed)"
#else
	#define KALOS_OS "unknow"
	#error "kalos unsuported for this os"
#endif

//-------------------------------------------------//
//                                                 //
//                   COMMON FUNCTIONS              //
//                                                 //
//-------------------------------------------------//
// the functions should not be reimplemented by each OS

// return NULL on error
kalos_surface_t *kalos_init();

void kalos_end();

void kalos_get_events(kalos_event_t **events, int *events_len);

void kalos_fill(kalos_surface_t *dest, uint32_t colour);

void kalos_fill_rect(kalos_surface_t *dest, int x, int y, int h, int w, uint32_t colour);

void kalos_draw_line(kalos_surface_t *dest, int x1, int y1, int x2, int y2, uint32_t colour);

void kalos_draw_disk(kalos_surface_t *dest, int x, int y, int radius, uint32_t colour);

void kalos_draw_circle(kalos_surface_t *dest,  int x, int y, int radius, uint32_t colour);

kalos_surface_t *kalos_new_surface(int width, int height);

void kalos_blit(kalos_surface_t *dest, kalos_surface_t *src, int x, int y);


void I_kalos_set_event_len(int len);


#endif

