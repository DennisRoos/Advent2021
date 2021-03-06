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

long long Crabs[2000];

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		for (int i = 0; i < 2000; i++) {
			Crabs[i] = 0;
		}
		int n;
		int left = 0;
		int right = 0;
		long long fuel = 0;
		while (infile >> n) {
			Crabs[n]++;
			right++;
			fuel += n;
		}
		long long prevFuel = fuel;
		int pos = 0;
		while (fuel <= prevFuel) {
			prevFuel = fuel;
			left += Crabs[pos];
			right -= Crabs[pos];
			fuel = fuel + left - right;
			pos++;
		}
		cout << "The optimal position for part 1 is " << pos - 1 << " with " << prevFuel << " fuel required.\n";
		
		//now for the mundane solution for part 2
		prevFuel = 99999999999999;
		fuel = prevFuel;
		pos = 0;
		while (fuel <= prevFuel) {
			prevFuel = fuel;
			fuel = 0;
			for (int i = 0; i < 2000; i++) {
				if (Crabs[i] > 0) {
					int dist = abs(i - pos);
					long long add = Crabs[i] * (dist * (dist + 1) / 2);
					fuel += add;
				}
			}
			pos++;
		}
		cout << "The optimal position for part 2 is " << pos - 1 << " with " << prevFuel << " fuel required.\n";


	}
	return 0;
}