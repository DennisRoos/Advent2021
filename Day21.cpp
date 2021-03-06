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

int s1;
int s2;
int dice;
int dicerolls;

int roll() {
	int d = dice;
	dicerolls++;
	dice++;
	if (dice > 100) {
		dice = 1;
	}
	return d;
}

int part1(int p1, int p2) {
	dice = 1;
	dicerolls = 0;
	while (true) {
		int step = roll() + roll() + roll();
		p1 = (p1 + step) % 10;
		s1 += p1 + 1;
		if (s1 >= 1000) {//player 1 won
			return s2;
		}
		step = roll() + roll() + roll();
		p2 = (p2 + step) % 10;
		s2 += p2 + 1;
		if (s2 >= 1000) {//player 2 won
			return s1;
		}
	}
}

long long p1wins[10][10][21][21][2];
long long p2wins[10][10][21][21][2];

void dirac(int p1, int p2, int s1, int s2, bool t) {
	int p;
	int s;
	long long Q[10];
	long long R[10];
	if (t == true) {//player one's turn
		for (int i = 3; i < 10; i++) {
			p = (p1 + i) % 10;
			s = s1 + p + 1;
			if (s >= 21) {// win
				R[i] = 1;
				Q[i] = 0;
			}
			else {
				if (p1wins[p][p2][s][s2][0] == -1) {//we haven't logged this specific case before yet
					dirac(p, p2, s, s2, false);
				}
				R[i] = p1wins[p][p2][s][s2][0];
				Q[i] = p2wins[p][p2][s][s2][0];
			}
		}
	}
	else {//player two's turn
		for (int i = 3; i < 10; i++) {
			p = (p2 + i) % 10;
			s = s2 + p + 1;
			if (s >= 21) {// win
				R[i] = 0;
				Q[i] = 1;
			}
			else {
				if (p1wins[p1][p][s1][s][1] == -1) {
					dirac(p1, p, s1, s, true);
				}
				R[i] = p1wins[p1][p][s1][s][1];
				Q[i] = p2wins[p1][p][s1][s][1];
			}
		}

	}
	long long player1wins = R[3] + 3 * R[4] + 6 * R[5] + 7 * R[6] + 6 * R[7] + 3 * R[8] + R[9];
	long long player2wins = Q[3] + 3 * Q[4] + 6 * Q[5] + 7 * Q[6] + 6 * Q[7] + 3 * Q[8] + Q[9];
	if (t) {
		p1wins[p1][p2][s1][s2][1] = player1wins;
		p2wins[p1][p2][s1][s2][1] = player2wins;
	}
	else {
		p1wins[p1][p2][s1][s2][0] = player1wins;
		p2wins[p1][p2][s1][s2][0] = player2wins;

	}
	return;
}


int main(int argc, char * argv[]) {
	int p1 = 3;//hardcoded start positions (note, these are one lower than the actual start positions since I simulate a track from 0-9
	int p2 = 9;
	s1 = 0;
	s2 = 0;
	int score = part1(p1,p2);
	cout << "The result for part 1 is " << score * dicerolls << endl;

	for (int a = 0; a < 10; a++) {
		for (int b = 0; b < 10; b++) {
			for (int c = 0; c < 21; c++) {
				for (int d = 0; d < 21; d++) {
					p1wins[a][b][c][d][0] = -1;
					p1wins[a][b][c][d][1] = -1;
					p2wins[a][b][c][d][0] = -1;
					p2wins[a][b][c][d][1] = -1;
				}
			}
		}
	}
	dirac(p1,p2, 0, 0, true);

	cout << "Player 1 won " << p1wins[p1][p2][0][0][1] << " times" << endl;
	cout << "Player 2 won " << p2wins[p1][p2][0][0][1] << " times" << endl;
	if (p1wins[p1][p2][0][0][1] > p2wins[p1][p2][0][0][1]) {
		cout << "Player 1 won more often\n";
	}
	else {
		cout << "Player 2 won more often\n";
	}
	return 0;
}