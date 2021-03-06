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

struct beacon {
	int x;
	int y;
	int z;
};


class scanner {
public:
	bool compare();
	bool found;
	int start;
	int beaconcount;
	int X[50][48];
	int Y[50][48];
	int Z[50][48];
	int xx;
	int yy;
	int zz;
};

int foundcount;
vector<beacon*> bbb[39];
vector<scanner*> v;
vector<beacon*> beacons;

void addBeacon(scanner* sc, int o, int x, int y, int z) {
	sc->X[sc->beaconcount][o] = x;
	sc->Y[sc->beaconcount][o] = y;
	sc->Z[sc->beaconcount][o] = z;
}

void addOrientation(scanner* sc, int o, int x, int y, int z) {
	addBeacon(sc, o + 0, x, y, z);
	addBeacon(sc, o + 1, x, y, -z);
	addBeacon(sc, o + 2, x, -y, z);
	addBeacon(sc, o + 3, x, -y, -z);
	addBeacon(sc, o + 4, -x, y, z);
	addBeacon(sc, o + 5, -x, y, -z);
	addBeacon(sc, o + 6, -x, -y, z);
	addBeacon(sc, o + 7, -x, -y, -z);
}

void newBeacon(int x, int y, int z) {
	for (int i = 0; i < beacons.size(); i++) {
		if (beacons[i]->x == x && beacons[i]->y == y && beacons[i]->z == z) {
			return;
		}
	}
	beacon* b = new beacon();
	b->x = x;
	b->y = y;
	b->z = z;
	beacons.push_back(b);
}

bool scanner::compare() {
	for (int i = start; i <= foundcount; i++) {
		for (int m = 0; m < bbb[i].size(); m++) {
			for (int k = 0; k < 48; k++) {
				for (int j = 0; j < beaconcount; j++) {//for each known beacon i, we picture beacon j of this scanner to be i and see if we have overlap
					int scannerX = bbb[i][m]->x - X[j][k];
					int scannerY = bbb[i][m]->y - Y[j][k];
					int scannerZ = bbb[i][m]->z - Z[j][k];
					int count = 0;
					for (int a = m+1; a < bbb[i].size(); a++) {
						for (int b = 0; b < beaconcount; b++) {
							if (bbb[i][a]->x == scannerX + X[b][k] && bbb[i][a]->y == scannerY + Y[b][k] && bbb[i][a]->z == scannerZ + Z[b][k]) {
								count++;
							}
						}
					}
					if (count >= 11) {//we found a match!
						found = true;
						foundcount++;
						xx = scannerX;
						yy = scannerY;
						zz = scannerZ;
						for (int c = 0; c < beaconcount; c++) {
							int x = scannerX + X[c][k];
							int y = scannerY + Y[c][k];
							int z = scannerZ + Z[c][k];
							beacon* b = new beacon();
							b->x = x;
							b->y = y;
							b->z = z;
							bbb[foundcount].push_back(b);
							newBeacon(x, y, z);
						}
						return true;
					}
				}
			}
		}
		start++;
	}
	return false;
}

int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int x;
		int y;
		int z;
		infile >> s;
		infile >> s;
		infile >> s;
		infile >> s;
		infile >> s;
		while (s.compare("---") != 0) {//load scanner 0
			x = stoi(s);
			infile >> y;
			infile >> z;
			infile >> s;
			beacon* b = new beacon();
			b->x = x;
			b->y = y;
			b->z = z; 
			bbb[0].push_back(b);
			beacons.push_back(b);
		}
		infile >> s;
		infile >> s;
		infile >> s;
		scanner* sc = new scanner();
		sc->found = false;
		sc->beaconcount = 0;
		sc->start = 0;
		v.push_back(sc);
		while (infile >> s) {
			if (s.compare("---") == 0) {
				sc = new scanner();
				v.push_back(sc);
				sc->found = false;
				sc->start = 0;
				sc->beaconcount = 0;
				infile >> s;
				infile >> s;
				infile >> s;
			}
			else{	
				x = stoi(s);
				infile >> y;
				infile >> z;
				addOrientation(sc, 0, x, y, z);//half of these orientations aren't actually possible, but it's giving me too much of a headache to figure out which so we'll just check them all
				addOrientation(sc, 8, x, z, y);
				addOrientation(sc, 16, y, x, z);
				addOrientation(sc, 24, y, z, x);
				addOrientation(sc, 32, z, x, y);
				addOrientation(sc, 40, z, y, x);


				sc->beaconcount++;
			}
		}
		foundcount = 0;
		while (foundcount < v.size()) {
			cout << "Looped\n" << endl;
			for (int i = 0; i < v.size(); i++) {
				if (!v[i]->found) {
					bool b = v[i]->compare();
					if (b) {

						cout << "Overlap found! " << foundcount << endl;
					}
				}
			}
		}
		int dist = 0;
		cout << "There were " << beacons.size() << " total beacons\n";
		for (int i = 0; i < v.size(); i++) {
			for (int j = 0; j < v.size(); j++) {
				int d = abs(v[i]->xx - v[j]->xx) + abs(v[i]->yy - v[j]->yy) + abs(v[i]->zz - v[j]->zz);
				if (d > dist) {
					dist = d;
				}
			}
		}
		cout << "The largest distance was " << dist << endl;
	}
	return 0;
}