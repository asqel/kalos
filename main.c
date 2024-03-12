#include "kalos.h"
#include <stdio.h>
#include <math.h>
extern int kalos_does_redraw;
double A = 0;
void draw_graph() {
	int zero = kalos_get_height()/2;
	int w = kalos_get_width();
	double x = 0;
	for(int i = 0; i < w; i++) {
		x += 0.1;
		set_pixel_u32((int)i, (int)(sin(x+A)*10+zero), 0x0000FF);
	}
	A += 0.1;
}

int main(int argc, char const *argv[]){
	kalos_init();
	double x = 0;
	double y = 0;
	int end = 0;
	int Speed = 10;
	int x2 = -1;
	int y2 = -1;
	int dir_y = 0;
	int dir_x = 0;
	int moving_state = 5;
	while (!end) {
		kalos_update_events();
		for(int i = 0; i < kalos_events_len; i++) {
			if (kalos_events[i].is_pressed == 3) {
				if (kalos_events[i].key[0] == KEY_ARROW_UP)
					dir_y += -1;
				if (kalos_events[i].key[0] == KEY_ARROW_DOWN)
					dir_y += 1;
				if (kalos_events[i].key[0] == KEY_ARROW_RIGHT)
					dir_x += 1;
				if (kalos_events[i].key[0] == KEY_ARROW_LEFT)
					dir_x +=  -1;
				if (kalos_events[i].key[0] == KEY_SHIFT) {
					y2 = y;
					x2 = x;
				}
			}
			if (kalos_events[i].is_pressed == 4) {
				if (kalos_events[i].key[0] == KEY_ARROW_UP)
					dir_y -= -1;
				if (kalos_events[i].key[0] == KEY_ARROW_DOWN)
					dir_y -= 1;
				if (kalos_events[i].key[0] == KEY_ARROW_RIGHT)
					dir_x -= 1;
				if (kalos_events[i].key[0] == KEY_ARROW_LEFT)
					dir_x -=  -1;
			}
		}
		if (moving_state) {
			moving_state--;
		}
		if (!moving_state) {
			y += dir_y;
			x += dir_x;
			moving_state = 5;
		}
		kalos_fill_window(0, 0, 0);

		if (y2 >= 0)
			y2 -= 1;
		if (y2 >= 0) {
			kalos_draw_disk(x2, y2, 10, 0, 0, 255);
		}
		//if (dir_x == 0 && dir_y == 0)
			draw_graph();
		kalos_fill_rect(x, y, 10, 10, 255, 0, 255);
		kalos_update_window();
		
		kalos_sleep_ms(1.0/60*1000);
	}
	return 0;
}
