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

bool A[500][500];
bool C[500][500];
bool B[512];

int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		for (int i = 0; i < 500; i++) {
			for (int j = 0; j < 500; j++) {
				A[i][j] = 0;
			}
		}
		string s;
		infile >> s;
		for (int i = 0; i < 512; i++) {
			if (s[i] == '#') {
				B[i] = true;
			}
			else {
				B[i] = false;
			}
		}
		int i = 150;
		while (infile >> s) {
			for (int j = 0; j < 100; j++) {
				if (s[j] == '#') {
					A[i][j + 150] = true;
				}
				else{
					A[i][j + 150] = false;
				}
			}
			i++;
		}

		for (int r = 0; r < 50; r++) {
			for (int i = 20; i < 480; i++) {
				for (int j = 20; j < 480; j++) {
					int n = 0;
					for (int k = -1; k < 2; k++) {
						for (int l = -1; l < 2; l++) {
							n *= 2;
							if (A[i + k][j + l] == true) {
								n++;
							}
						}
					}
					C[i][j] = B[n];
				}
			}

			for (int i = 20; i < 480; i++) {
				for (int j = 20; j < 480; j++) {
					A[i][j] = C[i][j];
				}
			}
		}

		int count = 0;
		for (int i = 90; i < 410; i++) {
			for (int j = 90; j < 410; j++) {
				if (A[i][j]) {
					count++;
				}
			}
		}
		cout << "There were " << count << " lights after 50 rounds" << endl;

	}
	return 0;
}