#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <list>
#include <sstream>

using namespace std;

int V[1000][1000];

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 1000; j++) {
				V[i][j] = 0;
			}
		}
		int x1;
		int x2;
		int y1;
		int y2;
		string t;
		while (infile >> x1) {
			infile >> y1;
			infile >> t;
			infile >> x2;
			infile >> y2;
			if (x1 == x2) {//vertical
				int low = min(y1, y2);
				int high = max(y1, y2);
				for (int i = low; i <= high; i++) {
					V[x1][i]++;
				}
			}
			else if (y1 == y2) {//horizontal
				int low = min(x1, x2);
				int high = max(x1, x2);
				for (int i = low; i <= high; i++) {
					V[i][y1]++;
				}
			}
			else {//diagonal
				if (x1 > x2) {
					if (y1 < y2) {
						for (int i = 0; i <= x1 - x2; i++) {
							V[x1 - i][y1 + i]++; 
						}
					}
					else {
						for (int i = 0; i <= x1 - x2; i++) {
							V[x1 - i][y1 - i]++;
						}
					}
				}
				else {
					if (y1 < y2) {
						for (int i = 0; i <= x2 - x1; i++) {
							V[x1 + i][y1 + i]++;
						}
					}
					else {
						for (int i = 0; i <= x2 - x1; i++) {
							V[x1 + i][y1 - i]++;
						}
					}

				}
			}
		}
		int count = 0;
		for (int j = 0; j < 1000; j++) {
			for (int i = 0; i < 1000; i++) {
				if (V[i][j] > 1) {
					count++;
				}
			}
		}
		cout << "Total number of overlapping vents is " << count << endl;

	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}