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

string t;
vector<char> v;

int find(char c) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == c) {
			return i;
		}
	}
	v.push_back(c);
	return v.size() - 1;
}

long long R[10][10][10][41];
int S[10][10];
long long num[10];

int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		infile >> t;
		string input;
		string dummy;
		char result;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					for (int l = 0; l < 41; l++) {
						R[i][j][k][l] = 0;
					}
				}
			}
		}

		while (infile >> input) {
			infile >> dummy;
			infile >> result;
			int a = find(input[0]);
			int b = find(input[1]);
			int c =	find(result);
			R[a][b][c][1] = 1;
			S[a][b] = c;
		}
		for (int r = 2; r < 41; r++) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					int s = S[i][j];
					for (int k = 0; k < 10; k++) {
						R[i][j][k][r] = R[i][s][k][r - 1] + R[s][j][k][r - 1];
					}
					R[i][j][s][r]++;
				}
			}
		}
		string s;
		for (int i = 0; i < t.size(); i++) {
			s.push_back(find(t[i]));
		}

		for (int j = 0; j < 10; j++) {
			num[j] = 0;
		}
		for (int i = 1; i < s.size(); i++) {
			num[s[i]]++;
			for (int j = 0; j < 10; j++) {
				num[j] += R[s[i - 1]][s[i]][j][40];//change 40 to 10 for part 1
			}
		}
		num[s[0]]++;
		long long highest = -1;
		long long lowest = 99999999999999999;
		for (int j = 0; j < 10; j++) {
			if (num[j] > highest) {
				highest = num[j];
			}
			if (num[j] < lowest) {
				lowest = num[j];
			}
		}
		cout << "The highest count was " << highest << ". The lowest count was " << lowest << ". Their difference is " << highest - lowest << endl;
	}
	return 0;
}