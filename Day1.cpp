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

vector<int> v;

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{

		int current;
		int n;
		int count = 0;
		infile >> current;
		v.push_back(current);
		while (infile >> n) {
			if (current < n) {
				count++;
			}
			current = n;
			v.push_back(n);
		}
		cout << "There were " << count << " increases for part 1.\n";
		int sum = v[0] + v[1] + v[2];
		count = 0;
		for (int i = 3; i < v.size(); i++) {
			int newsum = sum - v[i - 3] + v[i];
			if (newsum > sum) {
				count++;
			}
			sum = newsum;
		}

		cout << "There were " << count << " increases for part 2.\n";
	}
	return 0;
}