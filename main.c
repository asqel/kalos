#include "kalos.h"
#include <stdio.h>

extern int kalos_does_redraw;

int main(int argc, char const *argv[]){
	kalos_init();
	kalos_show_window();
	int x = 0;
	int y = 0;
	int end = 0;
	while (!end) {
		kalos_event_t *events = kalos_get_events();
		for(int i = 0; events[i].is_pressed != 2; i++) {
						if (events[i].is_pressed == 3) {
				if (events[i].key[0] == KEY_ARROW_UP)
					y--;
				if (events[i].key[0] == KEY_ARROW_DOWN)
					y++;
				if (events[i].key[0] == KEY_ARROW_RIGHT)
					x++;
				if (events[i].key[0] == KEY_ARROW_LEFT)
					x--;
			}
		}

		kalos_fill_window(0, 0, 0);
		kalos_draw_disk(x, y, 10, 255, 0, 255);
		
		kalos_sleep_ms(16);
	}
	return 0;
}
