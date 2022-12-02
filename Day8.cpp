#include <iostream>
#include <fstream>
//#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include <cmath>

using namespace std;
string A[10];
int B[10];
int C[10];

bool contains(string s, char c) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == c) {
			return true;
		}
	}
	return false;
}

bool subset(string a, string b) {//checks if b contains all characters in a
	for (int i = 0; i < a.size(); i++) {
		if (!contains(b, a[i])) {
			return false;
		}
	}
	return true;
}

int digit(string s) {
	for (int i = 0; i < 10; i++) {
		if (s.compare(A[i]) == 0) {
			return C[i];
		}
	}
	return -1;
}

int main(int argc, char* argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int total;
		string s;
		total = 0;
		while (infile >> s) {
			int n = 0;
			for (int j = 0; j < 10; j++) {
				A[j] = -1;
				B[j] = -1;
				C[j] = -1;
			}
			for (int i = 0; i < 10; i++) {
				sort(s.begin(), s.end());
				A[i].assign(s);
				if (s.size() == 2) {// digit 1
					B[1] = i;
					C[i] = 1;
				}
				else if (s.size() == 3) {// digit 7
					B[7] = i;
					C[i] = 7;
				}
				else if (s.size() == 4) {// digit 4
					B[4] = i;
					C[i] = 4;
				}
				else if (s.size() == 7) {// digit 8
					B[8] = i;
					C[i] = 8;
				}
				infile >> s;
			}
			for (int i = 0; i < 10; i++) {
				if (subset(A[B[7]], A[i])) {
					if (A[i].size() == 5) {// digit 3
						B[3] = i;
						C[i] = 3;
					}
				}
			}
			for (int i = 0; i < 10; i++) {
				if (subset(A[B[4]], A[i])) {
					if (A[i].size() == 6) {// digit 9
						B[9] = i;
						C[i] = 9;
					}
				}
			}
			for (int i = 0; i < 10; i++) {
				if (A[i].size() == 6 && subset(A[B[7]], A[i])) {
					if (C[i] == -1) {// digit 0, not 9
						B[0] = i;
						C[i] = 0;
					}
				}
			}
			for (int i = 0; i < 10; i++) {
				if (A[i].size() == 6 && C[i] == -1) {//digit 6
					B[6] = i;
					C[i] = 6;
				}
			}
			for (int i = 0; i < 10; i++) {
				if (A[i].size() == 5 && subset(A[i], A[B[6]])) {// digit 5
					B[5] = i;
					C[i] = 5;
				}
			}
			for (int i = 0; i < 10; i++) {
				if (C[i] == -1) {// digit 2
					B[2] = i;
					C[i] = 2;
				}
			}
			//figured out all the digits

			for (int i = 0; i < 4; i++) {
				infile >> s;
				n *= 10;
				sort(s.begin(), s.end());
				int m = digit(s);
				n += m;
			}
			total += n;
		}
		cout << "The total is " << total << endl;
	}
	return 0;
}