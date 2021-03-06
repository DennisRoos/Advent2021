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

long long Fish[9];

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		for (int i = 0; i < 9; i++) {
			Fish[i] = 0;
		}
		int n;
		while (infile >> n) {
			Fish[n]++;
		}
		for (int r = 0; r < 256; r++) {
			long long zero = Fish[0];
			for (int i = 0; i < 8; i++) {
				Fish[i] = Fish[i + 1];
			}
			Fish[8] = zero;
			Fish[6] += zero;
		}

		long long total = 0;
		for (int i = 0; i < 9; i++) {
			total += Fish[i];
		}
		cout << "There are " << total << " fish\n";
	}
	return 0;
}