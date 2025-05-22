#include "kalos.h"
#include <stdlib.h>
#include <stdio.h>


int main() {
	kalos_surface_t *surface = kalos_init(800, 600);
	if (surface == NULL) {
		printf("Error: %s\n", "kalos_init");
		return 1;
	}
	int x = 0;
	int y = 0;
	while (1) {
		kalos_update_events();
		kalos_event_t *events;
		int events_len;
		kalos_get_events(&events, &events_len);
		for (int i = 0; i < events_len; i++) {
			if (events[i].type == KALOS_EV_QUIT) {
				kalos_exit();
				return 0;
			}
			if (events[i].type == KALOS_EV_SPECIAL_KEY_PRESSED) {
				if (events[i].val.special == KEY_ARROW_UP) {
					y--;
				}
				if (events[i].val.special == KEY_ARROW_DOWN) {
					y++;
				}
				if (events[i].val.special == KEY_ARROW_LEFT) {
					x--;
				}
				if (events[i].val.special == KEY_ARROW_RIGHT) {
					x++;
				}
				if (events[i].val.key == KEY_ESC) {
					kalos_exit();
					return 0;
				}
			}
		}
		surface->pixels[x + y * surface->I_width] = 0xFF0000;
		usleep(200000);
		kalos_update_window();
	}
	return 0;
}