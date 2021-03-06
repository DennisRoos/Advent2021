#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include <cmath>

using namespace std;

int xmax;
int xmin;
int ymax;
int ymin;
int hits;

int shoot(int xvel, int yvel) {
	int max = 0;
	int x = 0;
	int y = 0;
	while (x <= xmax && y >= ymin) {
		if (x >= xmin && y <= ymax) {//within target area
			hits++;
			return max;
		}
		else {
			x += xvel;
			y += yvel;
			if (xvel > 0) {
				xvel--;
			}
			yvel--;
			if (y > max) {
				max = y;
			}
		}
	}
	return -1;//probe didn't hit target area
}

int main(int argc, char * argv[]) {
	xmax = 311;
	xmin = 281;
	ymax = -54;
	ymin = -74;
	hits = 0;
	int best = -99;
	for (int x = 0; x < 330; x++) {
		for (int y = -74; y < 300; y++) {
			int result = shoot(x, y);
			if (result > best) {
				best = result;
			}
		}
	}
	cout << "The highest y was " << best << endl;
	cout << hits << " probes hit the target." << endl;

	return 0;
}