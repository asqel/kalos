#include "kalos.h"
#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>

static Display *I_Xdisplay = NULL;
static Window I_Xwindow = {0};
static int I_Xscreen = 0;
static GC I_Xgc = {0};

int I_kalos_init(int w, int h) {
	I_Xdisplay = XOpenDisplay(NULL);
	if (I_Xdisplay == NULL) {
		return 1;
	}
	I_Xscreen = DefaultScreen(I_Xdisplay);
	I_Xwindow = XCreateSimpleWindow(I_Xdisplay, RootWindow(I_Xdisplay, I_Xscreen), 0, 0, w, h, 1,
		BlackPixel(I_Xdisplay, I_Xscreen), WhitePixel(I_Xdisplay, I_Xscreen));
	XSelectInput(I_Xdisplay, I_Xwindow, ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask);
	XMapWindow(I_Xdisplay, I_Xwindow);
	I_Xgc = XCreateGC(I_Xdisplay, I_Xwindow, 0, NULL);
	XSetForeground(I_Xdisplay, I_Xgc, BlackPixel(I_Xdisplay, I_Xscreen));
	XSetBackground(I_Xdisplay, I_Xgc, WhitePixel(I_Xdisplay, I_Xscreen));
	XFlush(I_Xdisplay);
	return 0;
}

void I_kalos_exit() {
	if (I_Xdisplay) {
		if (I_Xgc) XFreeGC(I_Xdisplay, I_Xgc);
		if (I_Xwindow) XDestroyWindow(I_Xdisplay, I_Xwindow);
		XCloseDisplay(I_Xdisplay);
		I_Xdisplay = NULL;
	}
}

void kalos_update_window() {
	if (I_kalos_win_buffer == NULL) return;
	XImage *image = XCreateImage(I_Xdisplay, DefaultVisual(I_Xdisplay, I_Xscreen), 24, ZPixmap, 0,
		(char *)I_kalos_win_buffer->pixels, I_kalos_win_buffer->I_width, I_kalos_win_buffer->I_height, 32, 0);
	XPutImage(I_Xdisplay, I_Xwindow, I_Xgc, image, 0, 0, 0, 0,
		I_kalos_win_buffer->I_width, I_kalos_win_buffer->I_height);
	XFlush(I_Xdisplay);
	image->data = NULL;
	XDestroyImage(image);
}

static uint32_t key_from_keysym_special(KeySym ks) {
	switch (ks) {
		case XK_Escape: return KEY_ESC;
		case XK_Control_L: return KEY_CTRL_L;
		case XK_Control_R: return KEY_CTRL_R;
		case XK_Alt_L: case XK_Alt_R: return KEY_ALT;
		case XK_Up: return KEY_ARROW_UP;
		case XK_Down: return KEY_ARROW_DOWN;
		case XK_Left: return KEY_ARROW_LEFT;
		case XK_Right: return KEY_ARROW_RIGHT;
		case XK_Return: return KEY_ENTER;
		case XK_BackSpace: return KEY_BACKSPACE;
		case XK_Shift_L: case XK_Shift_R: return KEY_SHIFT;
		case XK_Delete: return KEY_DELETE;
		case XK_Insert: return KEY_INSERT;
		case XK_Page_Up: return KEY_PAGE_UP;
		case XK_Page_Down: return KEY_PAGE_DOWN;
		case XK_Home: return KEY_HOME;
		case XK_End: return KEY_END;
		case XK_F1: return KEY_F1;
		case XK_F2: return KEY_F2;
		case XK_F3: return KEY_F3;
		case XK_F4: return KEY_F4;
		case XK_F5: return KEY_F5;
		case XK_F6: return KEY_F6;
		case XK_F7: return KEY_F7;
		case XK_F8: return KEY_F8;
		case XK_F9: return KEY_F9;
		case XK_F10: return KEY_F10;
		case XK_F11: return KEY_F11;
		case XK_F12: return KEY_F12;
		case XK_Caps_Lock: return KEY_CAPS_LOCK;
		default: return 0;
	}
}

static uint32_t key_from_keysym(KeySym ks) {
	switch (ks) {
		case XK_grave: return KALOS_K_TILDE;
		case XK_1: return KALOS_K_1;
		case XK_2: return KALOS_K_2;
		case XK_3: return KALOS_K_3;
		case XK_4: return KALOS_K_4;
		case XK_5: return KALOS_K_5;
		case XK_6: return KALOS_K_6;
		case XK_7: return KALOS_K_7;
		case XK_8: return KALOS_K_8;
		case XK_9: return KALOS_K_9;
		case XK_0: return KALOS_K_0;
		case XK_minus: return KALOS_K_MINUS;
		case XK_equal: return KALOS_K_EQUAL;
		case XK_Tab: return KALOS_K_TAB;
		case XK_q: return KALOS_K_Q;
		case XK_w: return KALOS_K_W;
		case XK_e: return KALOS_K_E;
		case XK_r: return KALOS_K_R;
		case XK_t: return KALOS_K_T;
		case XK_y: return KALOS_K_Y;
		case XK_u: return KALOS_K_U;
		case XK_i: return KALOS_K_I;
		case XK_o: return KALOS_K_O;
		case XK_p: return KALOS_K_P;
		case XK_bracketleft: return KALOS_K_L_BRACKET;
		case XK_bracketright: return KALOS_K_R_BRACKET;
		case XK_backslash: return KALOS_K_BACKSLASH;
		case XK_a: return KALOS_K_A;
		case XK_s: return KALOS_K_S;
		case XK_d: return KALOS_K_D;
		case XK_f: return KALOS_K_F;
		case XK_g: return KALOS_K_G;
		case XK_h: return KALOS_K_H;
		case XK_j: return KALOS_K_J;
		case XK_k: return KALOS_K_K;
		case XK_l: return KALOS_K_L;
		case XK_semicolon: return KALOS_K_SEMI_COLON;
		case XK_apostrophe: return KALOS_K_QUOTE;
		case XK_z: return KALOS_K_Z;
		case XK_x: return KALOS_K_X;
		case XK_c: return KALOS_K_C;
		case XK_v: return KALOS_K_V;
		case XK_b: return KALOS_K_B;
		case XK_n: return KALOS_K_N;
		case XK_m: return KALOS_K_M;
		case XK_comma: return KALOS_K_COMMA;
		case XK_period: return KALOS_K_PERIOD;
		case XK_slash: return KALOS_K_SLASH;
		case XK_space: return KALOS_K_SPACE;
		default:
			return 0;
	}
}

void kalos_update_events() {
	if (I_kalos_win_buffer == NULL) return;
	XEvent event;
	kalos_events_len = 0;
	while (XPending(I_Xdisplay)) {
		XNextEvent(I_Xdisplay, &event);
		if (event.type == KeyPress || event.type == KeyRelease) {
			// check if was modified
			kalos_event_t kalos_event = {0};
			uint32_t special = key_from_keysym_special(XLookupKeysym(&event.xkey, 0));
			if (special != 0) {
				kalos_event.type = (event.type == KeyPress) ? KALOS_EV_SPECIAL_KEY_PRESSED : KALOS_EV_SPECIAL_KEY_RELEASED;
				kalos_event.val.special = special;
				I_kalos_append_event(kalos_event);
			}
			else {
				kalos_event.type = (event.type == KeyPress) ? KALOS_EV_KEY_PRESSED : KALOS_EV_KEY_RELEASED;
				kalos_event.val.key = key_from_keysym(XkbKeycodeToKeysym(I_Xdisplay, event.xkey.keycode, 0, 0));
				if (kalos_event.val.key != 0)
					I_kalos_append_event(kalos_event);
			}
		}
		else if (event.type == ConfigureNotify) {
			kalos_set_dimensions(event.xconfigure.width, event.xconfigure.height);
			kalos_event_t kalos_event = {0};
			kalos_event.type = KALOS_EV_DIMENSIONS;
			I_kalos_append_event(kalos_event);
		}
		// check if the cross was clicked
		else if (event.type == ClientMessage) {
			if (event.xclient.data.l[0] == XInternAtom(I_Xdisplay, "WM_DELETE_WINDOW", False)) {
				kalos_event_t kalos_event = {0};
				kalos_event.type = KALOS_EV_QUIT;
				I_kalos_append_event(kalos_event);
			}
		}
	}
}

int I_kalos_set_dimensions(int w, int h) {
	if (I_Xwindow == 0) return 1;
	XResizeWindow(I_Xdisplay, I_Xwindow, w, h);
	return 0;
}

#endif