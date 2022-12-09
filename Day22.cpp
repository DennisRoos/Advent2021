
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

class cuboid {
public:
	int x1;
	int x2;
	int y1;
	int y2;
	int z1;
	int z2;
	cuboid(int a1, int a2, int b1, int b2, int c1, int c2);
};

cuboid::cuboid(int a1, int a2, int b1, int b2, int c1, int c2) {
	x1 = a1;
	x2 = a2;
	y1 = b1;
	y2 = b2;
	z1 = c1;
	z2 = c2;
}

vector<cuboid*> v;
vector<cuboid*> temp;

void intersect(cuboid *A, cuboid *B) {
	if (A->x1 < B->x1) {//A splits along x1
		cuboid* N = new cuboid(A->x1, B->x1 - 1, A->y1, A->y2, A->z1, A->z2);		

		v.push_back(N);
		A->x1 = B->x1;
	}
	if (A->x2 > B->x2) {//A splits along x2
		cuboid* N = new cuboid(B->x2 + 1, A->x2, A->y1, A->y2, A->z1, A->z2);
		v.push_back(N);
		A->x2 = B->x2;
	}
	if (A->y1 < B->y1) {//A splits along y1
		cuboid* N = new cuboid(A->x1, A->x2, A->y1, B->y1 - 1, A->z1, A->z2);
		v.push_back(N);
		A->y1 = B->y1;
	}
	if (A->y2 > B->y2) {//A splits along y2
		cuboid* N = new cuboid(A->x1, A->x2, B->y2 + 1, A->y2, A->z1, A->z2);
		v.push_back(N);
		A->y2 = B->y2;
	}
	if (A->z1 < B->z1) {//A splits along z1
		cuboid* N = new cuboid(A->x1, A->x2, A->y1, A->y2, A->z1, B->z1 - 1);
		v.push_back(N);
		A->z1 = B->z1;
	}

	if (A->z2 > B->z2) {//A splits along z2
		cuboid* N = new cuboid(A->x1, A->x2, A->y1, A->y2, B->z2 + 1, A->z2);
		v.push_back(N);
		A->z2 = B->z2;
	}
	v.erase(std::remove(v.begin(), v.end(), A), v.end());
	delete A;
	return;
}


int main(int argc, char* argv[]) {

	regex re("x=(-?[\\d]+)..(-?[\\d]+),y=(-?[\\d]+)..(-?[\\d]+),z=(-?[\\d]+)..(-?[\\d]+)");
	string s;
	smatch match;
	ifstream infile;
	infile.open("data.txt");
	long long total = 0;
	if (infile.is_open()) {
		string command;
		while (infile >> command) {
			infile >> s;
			if (regex_search(s, match, re) == true) {
				int x1 = stoi(match.str(1));
				int x2 = stoi(match.str(2));
				int y1 = stoi(match.str(3));
				int y2 = stoi(match.str(4));
				int z1 = stoi(match.str(5));
				int z2 = stoi(match.str(6));
				cuboid *C = new cuboid(x1, x2, y1, y2, z1, z2);
				for (int i = 0; i < v.size(); i++) {
					temp.push_back(v[i]);
				}
				for (int i = 0; i < temp.size(); i++) {
					if (temp[i]->x2 >= x1 && temp[i]->x1 <= x2 &&
						temp[i]->y2 >= y1 && temp[i]->y1 <= y2 &&
						temp[i]->z2 >= z1 && temp[i]->z1 <= z2) {//there is overlap!
						intersect(temp[i], C);
					}
				}
				if (command.compare("on") == 0) {
					v.push_back(C);
				}
				else {
					delete C;
				}
				temp.clear();
				total = 0;
			}
		}
		for (int i = 0; i < v.size(); i++) {
			long long x = (v[i]->x2 - v[i]->x1 + 1);
			long long y = (v[i]->y2 - v[i]->y1 + 1);
			long long z = (v[i]->z2 - v[i]->z1 + 1);
			long long volume = x * y * z;
			total += volume;
		}
		cout << "Total volume is " << total << endl << endl << endl;
	}


}