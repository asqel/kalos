#include "kalos.h"
#include <stdio.h>

int main(int argc, char const *argv[]){
	kalos_init();
	kalos_show_window();
	int x = 0;
	int y = 0;
	int end = 0;
	while (!end) {

		kalos_fill_window(0, 0, 0);
		kalos_draw_disk(x, y, 10, 255, 0, 255);
		kalos_update_window();
	}
	return 0;
}
