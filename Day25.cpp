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

char A[160][160];
char B[160][160]; 
int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{


		string s;
		int j = 0;
		int i = 0;
		while (infile >> s) {
			for (i = 0; i < s.size(); i++) {
				A[j][i] = s[i];
				B[j][i] = s[i];
				//cout << A[j][i];
			}
			j++;
			//cout << endl;
		}
		int w = i;
		int h = j;
		bool b = true;
		int round = 0;
		while (b) {
			b = false;
			round++;
			//cout << "Starting round " << round << endl;
			for (int j = 0; j < h; j++) {
				for (int i = w - 1; i >= 1; i--) {
					if (A[j][i] == '.' && A[j][i - 1] == '>') {
						B[j][i] = '>';
						B[j][i - 1] = '.';
						b = true;
					}
				}
				if (A[j][0] == '.' && A[j][w - 1] == '>') {
					B[j][0] = '>';
					B[j][w - 1] = '.';
					b = true;
				}
			}
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					A[i][j] = B[i][j];
				}
			}

			for (int i = 0; i < w; i++) {
				for (int j = h - 1; j >= 1; j--) {
					if (A[j][i] == '.' && A[j-1][i] == 'v') {
						B[j][i] = 'v';
						B[j-1][i] = '.';
						b = true;
					}
				}
				if (A[0][i] == '.' && A[h-1][i] == 'v') {
					B[0][i] = 'v';
					B[h-1][i] = '.';
					b = true;
				}
			}
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					A[i][j] = B[i][j];
					//cout << A[i][j];
				}
				//cout << endl;
			}

		}
		cout << "Everything stopped on round " << round << endl;


	}
	return 0;
}