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

int A[502][502];
int D[502][502];


struct node {
	int x;
	int y;
	node* next;
	node* prev;
};

node* start;


int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int j = 1;
		while (infile >> s) {
			for (int i = 1; i <= 100; i++) {
				A[i][j] = s[i - 1] - '0';
				for (int k = 0; k < 5; k++) {
					for (int l = 0; l < 5; l++) {
						int t = A[i][j] + k + l;
						if (t > 9) {
							t = t - 9;
						}
						A[(100 * k) + i][100 * l + j] = t;
						D[(100 * k) + i][100 * l + j] = 9999;

					}
				}
			}
			j++;
		}
		for (int i = 0; i < 502; i++) {
			D[0][i] = 0;
			D[i][0] = 0;
			D[501][i] = 0;
			D[i][501] = 0;
		}
		D[1][1] = 0;
		start = new node();
		start->next = NULL;
		start->prev = NULL;
		start->x = 1;
		start->y = 1;
		while (true) {
			int x;
			int y;
			int smallest = 9999999999;
			node* best = start;
			node* n = start;
			while (n != NULL) {
				int d = D[n->x][n->y];
				if (d < smallest) {
					smallest = d;
					best = n;
				}
				n = n->next;
			}
			if (best == start) {//remove smallest element from list
				start = start->next;
			}
			else {
				best->prev->next = best->next;
				if (best->next != NULL) {
					best->next->prev = best->prev;
				}
			}
			x = best->x;
			y = best->y;
			int l;
			if (x == 500 && y == 500) {
				cout << "The shortest path is length " << D[500][500] << endl;
				return 0;
			}
			l = D[x][y] + A[x - 1][y];
			if (D[x - 1][y] > l) {
				if (D[x - 1][y] == 9999) {
					node *n2 = new node();
					n2->x = x - 1;
					n2->y = y;
					if (start != NULL) {
						start->prev = n2;
					}
					n2->next = start;
					start = n2;
				}
				D[x - 1][y] = l;
			}
			l = D[x][y] + A[x + 1][y];
			if (D[x + 1][y] > l) {
				if (D[x + 1][y] == 9999) {
					node *n2 = new node();
					n2->x = x + 1;
					n2->y = y;
					if (start != NULL) {
						start->prev = n2;
					}
					n2->next = start;
					start = n2;
				}
				D[x + 1][y] = l;
			}
			l = D[x][y] + A[x][y - 1];
			if (D[x][y - 1] > l) {
				if (D[x][y - 1] == 9999) {
					node *n2 = new node();
					n2->x = x;
					n2->y = y - 1;
					if (start != NULL) {
						start->prev = n2;
					}
					n2->next = start;
					start = n2;
				}
				D[x][y - 1] = l;
			}
			l = D[x][y] + A[x][y + 1];
			if (D[x][y + 1] > l) {
				if (D[x][y + 1] == 9999) {
					node *n2 = new node();
					n2->x = x;
					n2->y = y + 1;
					if (start != NULL) {
						start->prev = n2;
					}
					n2->next = start;
					start = n2;
				}
				D[x][y + 1] = l;
			}
		}
	}
	return 0;
}