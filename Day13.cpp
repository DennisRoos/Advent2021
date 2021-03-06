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

bool A[1311][895];

int main(int argc, char * argv[]) {
	int xmax = 1310;
	int ymax = 894;
	string s;
	int x;
	int y;
	for (int i = 0; i <= xmax; i++) {
		for (int j = 0; j <= ymax; j++) {
			A[i][j] = false;
		}
	}
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		while (infile >> s) {
			if (s.compare("fold") == 0) {
				char c;
				infile >> c;
				if (c == 'x') {
					infile >> x;
					for (int i = 0; i < x; i++) {
						for (int j = 0; j <= ymax; j++) {
							A[i][j] = A[i][j] || A[xmax - i][j];
						}
					}
					xmax = x - 1;
				}
				else {
					infile >> y;
					for (int i = 0; i <= xmax; i++) {
						for (int j = 0; j < y; j++) {
							A[i][j] = A[i][j] || A[i][ymax - j];
						}
					}
					ymax = y - 1;
				}
				int count = 0;
				for (int i = 0; i <= xmax; i++) {
					for (int j = 0; j <= ymax; j++) {
						if (A[i][j]) {
							count++;
						}
					}
				}
				cout << count << endl;
			}
			else {
				x = stoi(s);
				infile >> y;
				A[x][y] = true;
			}
		}
		for (int i = 0; i <= ymax; i++) {
			for (int j = 0; j <= xmax; j++) {
				if (A[j][i]) {
					cout << "#";
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
	}
	return 0;
}