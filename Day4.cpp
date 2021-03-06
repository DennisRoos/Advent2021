#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <list>
#include <sstream>

using namespace std;

class bingo {
public:
	int A[5][5];
	bool marked[5][5];
	int x[100];
	int y[100];
	bool won;
	bingo();
	int score();
	void assign(int n, int xx, int yy);
};

bingo::bingo() {
	won = false;
	for (int i = 0; i < 100; i++) {
		x[i] = -1;
		y[i] = -1;
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			marked[i][j] = false;
		}
	}
}

void bingo::assign(int n, int xx, int yy) {
	A[xx][yy] = n;
	x[n] = xx;
	y[n] = yy;
	return;
}

vector<bingo*> v;
vector<int> numbers;

int bingo::score() {
	int score = 0;
	for (int k = 0; k < 5; k++) {
		for (int l = 0; l < 5; l++) {
			if (!marked[k][l]) {
				score += A[k][l];
			}
		}
	}
	return score;
}

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		getline(infile, s);
		stringstream ss;
		ss << s;
		int n;
		while (!ss.eof()) {
			ss >> n;
			numbers.push_back(n);
		}
		while (infile >> n) {
			bingo* b = new bingo();
			v.push_back(b);
			b->assign(n, 0, 0);
			for (int i = 1; i < 5; i++) {
				infile >> n;
				b->assign(n, 0, i);
			}
			for (int j = 1; j < 5; j++) {
				for (int i = 0; i < 5; i++) {
					infile >> n;
					b->assign(n, j, i);
				}
			}
		}
		int boardsleft = v.size();
		bool firstfound = false;
		int round = 0;
		while (true) {
			int current = numbers[round];
			round++;
			for (int i = 0; i < v.size(); i++) {
				if (v[i]->won == false) {
					if (v[i]->x[current] != -1) {
						v[i]->marked[v[i]->x[current]][v[i]->y[current]] = true;
						bool hor = true;
						bool ver = true;
						for (int j = 0; j < 5; j++) {
							hor = hor && v[i]->marked[j][v[i]->y[current]];
							ver = ver && v[i]->marked[v[i]->x[current]][j];
						}
						if (hor || ver) {//the bingo card won
							if (!firstfound) {
								cout << "The first winning score was " << v[i]->score()*current << endl;
								firstfound = true;
							}
							v[i]->won = true;
							boardsleft--;
							if (boardsleft == 0) {

								cout << "The last winning score was " << v[i]->score()*current << endl;
								return 0;
							}

						}
					}
				}
			}
		}


	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}