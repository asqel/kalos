#include "../../kalos.h"

void kalos_sleep_ms(long long int time) {
    long long int start = kalos_get_time_ms();
	while (start + time < kalos_get_time_ms());
}