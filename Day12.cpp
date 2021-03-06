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

vector<string> names;
bool A[25][25];
bool large[25];
bool visited[25];
bool visitedtwice;

int find(string s) {
	for (int i = 0; i < names.size(); i++) {
		if (s.compare(names[i]) == 0) {
			return i;
		}
	}
	int n = names.size();
	names.push_back(s);
	if (s[0] >= 'A' && s[0] <= 'Z') {
		large[n] = true;
	}
	return n;
}

int pathfind(int n) {
	if (n == 1) {//we found n
		return 1;
	}
	if (!large[n] && visited[n]) {//already been in this small cave on this path
		if (visitedtwice || n == 0) {//there's another cave we've visited twice already or this is the start cave
			return 0;
		}
		else{
			visitedtwice = true;
			int paths = 0;
			for (int i = 0; i < names.size(); i++) {
				if (A[n][i]) {//there is a path to cave i from here
					paths += pathfind(i);
				}
			}
			visitedtwice = false;
			return paths;
		
		}
	}
	int paths = 0;
	visited[n] = true;
	for (int i = 0; i < names.size(); i++) {
		if (A[n][i]) {//there is a path to cave i from here
			paths += pathfind(i);
		}
	}
	visited[n] = false;
	return paths;
}

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		visitedtwice = false;
		names.push_back("start");
		names.push_back("end");
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++) {
				A[i][j] = false;
			}
			visited[i] = false;
			large[i] = false;
		}
		string s;
		string t;
		while (infile >> s) {
			infile >> t;
			int source = find(s);
			int target = find(t);
			A[source][target] = true;
			A[target][source] = true;
		}
		cout << "There are " << pathfind(0) << " paths" << endl;

	}
	return 0;
}