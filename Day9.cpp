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

int A[102][102];
vector<int> v;//vector of all the basin sizes

int navigate(int j, int i) {
	if (A[j][i] == 9) {
		return 0;
	}
	else {
		A[j][i] = 9;
		return navigate(j + 1, i) + navigate(j - 1, i) + navigate(j, i+ 1) + navigate(j, i - 1) + 1;
	}
}

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int total = 0;
		int j = 1;
		while (infile >> s) {
			for (int i = 1; i <= s.size(); i++) {
				A[j][i] = s[i - 1] - '0';
			}
			A[j][0] = 9;
			A[j][101] = 9;
			j++;
		}
		for (int i = 0; i < 102; i++) {
			A[0][i] = 9;
			A[101][i] = 9;
		}
		for (int j = 1; j <= 100; j++) {
			for (int i = 1; i <= 100; i++) {
				int c = A[j][i];
				if (c < A[j - 1][i] && c < A[j + 1][i] && c < A[j][i + 1] && c < A[j][i - 1]) {//found a low point
					total += c + 1;
					int size = navigate(j, i);
					cout << size << endl;
					v.push_back(size);
				}
			}
		}
		cout << "The total risk factor is " << total << endl;
		sort(v.begin(), v.end());
		int vsize = v.size();
		long long product = v[vsize - 1] * v[vsize - 2] * v[vsize - 3];
		cout << "The product of the three largest basins is " << product << endl;
	}
	return 0;
}