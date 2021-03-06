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

int A[10][10];
bool flashed[10][10];
int totalflashes;
int flashes;

void gain(int i, int j) {
	if (i < 0 || i > 9 || j < 0 || j > 9) {
		return;
	}
	if (flashed[i][j]) {
		return;
	}
	if (A[i][j] < 9) {
		A[i][j]++;
	}
	else {//flash
		flashes++;
		flashed[i][j] = true;
		gain(i - 1, j - 1);
		gain(i, j - 1);
		gain(i + 1, j - 1);
		gain(i - 1, j);
		gain(i + 1, j);
		gain(i - 1, j + 1);
		gain(i, j + 1);
		gain(i + 1, j + 1);
	}
	return;
}

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		totalflashes = 0;
		int j = 0;
		while (infile >> s) {
			for (int i = 0; i < s.size(); i++) {
				A[j][i] = s[i] - '0';
			}
			j++;
		}
		int r = 1;
		while(true) {
			flashes = 0;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					flashed[i][j] = false;
				}
			}
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					gain(i, j);
				}
			}
			totalflashes += flashes;
			if (r == 100) {
				cout << "There were " << totalflashes << " flashes." << endl;
			}
			if (flashes == 100) {
				cout << "The octopi synchronized on step " << r << endl;
				return 0;//assumes this will be after part 1's result is in, i.e. it takes more than 100 rounds
			}
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (flashed[i][j]) {
						A[i][j] = 0;
					}
				}
			}
			r++;
		}
	}
	return 0;
}