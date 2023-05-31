#pragma once

#include <stdlib.h>
#include <time.h>

class Random {
public:
	Random() {
		timespec ts;
		timespec_get(&ts, TIME_UTC);
		srand(ts.tv_nsec);
	}

	int getnum(int range) {
		return rand() % range;
	}
};