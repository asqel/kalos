#ifndef KALOS_H
#define KALOS_H

#ifdef __cplusplus
extern "C" {
#endif

// Symbols prefixed with I should only be read/write by the lib (they are internal)

#include <stdint.h>
#ifndef NULL
#define NULL ((void *)0)
#endif

#define KEY_ESC 1
#define KEY_CTRL_L 2
#define KEY_CTRL_R 3
#define KEY_ALT 4
#define KEY_ARROW_UP 5
#define KEY_ARROW_DOWN 6
#define KEY_ARROW_LEFT 7
#define KEY_ARROW_RIGHT 8
#define KEY_ENTER 9
#define KEY_BACKSPACE 10
#define KEY_SHIFT 11
#define KEY_DELETE 12
#define KEY_INSERT 13
#define KEY_PAGE_UP 14
#define KEY_PAGE_DOWN 15
#define KEY_HOME 16
#define KEY_END 17
#define KEY_F1 18
#define KEY_F2 19
#define KEY_F3 20
#define KEY_F4 21
#define KEY_F5 22
#define KEY_F6 23
#define KEY_F7 24
#define KEY_F8 25
#define KEY_F9 26
#define KEY_F10 27
#define KEY_F11 28
#define KEY_F12 29
#define KEY_CAPS_LOCK 30

enum {
	KALOS_K_TILDE = 1,
	KALOS_K_1,
	KALOS_K_2,
	KALOS_K_3,
	KALOS_K_4,
	KALOS_K_5,
	KALOS_K_6,
	KALOS_K_7,
	KALOS_K_8,
	KALOS_K_9,
	KALOS_K_0,
	KALOS_K_MINUS,
	KALOS_K_EQUAL,
	KALOS_K_TAB,
	KALOS_K_Q,
	KALOS_K_W,
	KALOS_K_E,
	KALOS_K_R,
	KALOS_K_T,
	KALOS_K_Y,
	KALOS_K_U,
	KALOS_K_I,
	KALOS_K_O,
	KALOS_K_P,
	KALOS_K_L_BRACKET,
	KALOS_K_R_BRACKET,
	KALOS_K_BACKSLASH,
	KALOS_K_A,
	KALOS_K_S,
	KALOS_K_D,
	KALOS_K_F,
	KALOS_K_G,
	KALOS_K_H,
	KALOS_K_J,
	KALOS_K_K,
	KALOS_K_L,
	KALOS_K_SEMI_COLON,
	KALOS_K_QUOTE,
	KALOS_K_Z,
	KALOS_K_X,
	KALOS_K_C,
	KALOS_K_V,
	KALOS_K_B,
	KALOS_K_N,
	KALOS_K_M,
	KALOS_K_COMMA,
	KALOS_K_PERIOD,
	KALOS_K_SLASH,
	KALOS_K_SPACE,
};

#define KALOS_EV_KEY_RELEASED 0
#define KALOS_EV_KEY_PRESSED 1
#define KALOS_EV_SPECIAL_KEY_PRESSED 2
#define KALOS_EV_SPECIAL_KEY_RELEASED 3
#define KALOS_EV_DIMENSIONS 4// when window resized
#define KALOS_EV_QUIT 5

typedef struct kalos_event_s{
	char type;
	union {
		uint32_t key;
		uint32_t special;
	} val;
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

int I_kalos_init(int w, int h);
void I_kalos_exit();
void kalos_update_window();
void kalos_update_events();
int I_kalos_set_dimensions(int w, int h); // return 1 if window cannot be resized
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
kalos_surface_t *kalos_init(int w, int h);

void kalos_exit();

void kalos_get_events(kalos_event_t **events, int *events_len);

void kalos_fill(kalos_surface_t *dest, uint32_t colour);

void kalos_fill_rect(kalos_surface_t *dest, int x, int y, int h, int w, uint32_t colour);

void kalos_draw_line(kalos_surface_t *dest, int x1, int y1, int x2, int y2, uint32_t colour);

void kalos_draw_disk(kalos_surface_t *dest, int x, int y, int radius, uint32_t colour);

void kalos_draw_circle(kalos_surface_t *dest,  int x, int y, int radius, uint32_t colour);

kalos_surface_t *kalos_new_surface(int width, int height);

void kalos_blit(kalos_surface_t *dest, kalos_surface_t *src, int x, int y);


int I_kalos_append_event(kalos_event_t event); // 1 on error


void kalos_set_height(int h);
void kalos_set_width(int w);
int kalos_set_dimensions(int w, int h); // 1 on error

#ifdef __cplusplus
}
#endif

#endif

