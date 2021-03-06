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


int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int n;
		int hor = 0;
		int depth = 0;
		int aim = 0;
		while (infile >> s) {
			infile >> n;
			if (s.compare("up") == 0) {
				aim -= n;
			}
			else if (s.compare("down") == 0) {
					aim += n;
			}
			else {//forward
				hor += n;
				depth += aim*n;
			}
		}
		cout << "The final position for part 1 is " << hor << "," << aim << " which together multiplies to " << hor * aim << endl << endl;
		cout << "The final position for part 2 is " << hor << "," << depth << " which together multiplies to " << hor * depth << endl << endl;
	}
	return 0;
}