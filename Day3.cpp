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

vector<string> ox;
vector<string> co2;

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int C[12];
		for (int i = 0; i < 12; i++) {
			C[i] = 0;
		}
		int num = 0;
		while (infile >> s) {
			ox.push_back(s);
			co2.push_back(s);
			num++;
			for (int i = 0; i < 12; i++) {
				if (s[i] == '1') {
					C[i]++;
				}
			}
		}
		int gamma = 0;
		int epsilon = 0;
		for (int i = 0; i < 12; i++) {
			gamma *= 2;
			epsilon *= 2;
			if (C[i] > num / 2) {
				gamma++;
			}
			else {
				epsilon++;
			}
		}
		cout << "Gamma is " << gamma << ", epsilon is " << epsilon << ". They multiply to " << gamma * epsilon << endl;

		int bit = 0;
		while(ox.size() > 1){
			int count = 0;
			for (int i = 0; i < ox.size(); i++) {
				if (ox[i][bit] == '1') {
					count++;
				}
			}
			char c = '1';
			if (count *2 >= ox.size()) {
				c = '0';
			}
			for (int i = ox.size() - 1; i >= 0; i--) {
				if (ox[i][bit] == c) {
					ox.erase(ox.begin() + i);
				}
			}
			bit++;
		}
		bit = 0;
		while (co2.size() > 1) {
			int count = 0;
			for (int i = 0; i < co2.size(); i++) {
				if (co2[i][bit] == '1') {
					count++;
				}
			}
			char c = '1';
			if (count * 2 < co2.size()) {
				c = '0';
			}
			for (int i = co2.size() - 1; i >= 0; i--) {
				if (co2[i][bit] == c) {
					co2.erase(co2.begin() + i);
				}
			}
			bit++;
		}


		int oxy = 0;
		int scrub = 0;
		for (int i = 0; i < 12; i++) {
			oxy *= 2;
			scrub *= 2;
			if (ox[0][i] == '1') {
				oxy++;
			}
			if (co2[0][i] == '1') {
				scrub++;
			}
		}

		cout << "Oxygen: " << ox[0] << ", CO2: " << co2[0] << endl << "Product is " << oxy * scrub << endl;

	}
	return 0;
}