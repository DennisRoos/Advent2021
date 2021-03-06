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

string s;
int i;
long long completionscore;
vector<long long> v;

char closer(char c) {
	char d;
	if (c == '(') {
		d = ')';
	}
	else if (c == '{') {
		d = '}';
	}
	else if (c == '<') {
		d = '>';
	}
	else if (c == '[') {
		d = ']';
	}
	return d;
}

int parse(char c) {
	while (i < s.size()) {
		if (s[i] == '(' || s[i] == '<' || s[i] == '[' || s[i] == '{') {
			char d = closer(s[i]);
			i++;
			int score = parse(d);
			if (score > 0) {
				return score;
			}
		}
		else if (s[i] == c) {//closing bracket matches opening, end of chunk
			i++;
			return 0;
		}
		else {//non-matching closer
			if (s[i] == ')') {
				return 3;
			}
			if (s[i] == ']') {
				return 57;
			}
			if (s[i] == '}') {
				return 1197;
			}
			if (s[i] == '>') {
				return 25137;
			}
		}
	}
	completionscore *= 5;
	if (c == ')') {
		completionscore += 1;
	}
	else if (c == ']') {
		completionscore += 2;
	}
	else if (c == '}') {
		completionscore += 3;
	}
	else if (c == '>') {
		completionscore += 4;
	}
	return 0;
}


int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	int syntaxscore = 0;
	if (infile.is_open())
	{
		while (infile >> s) {
			i = 0;
			int corruption = 0;
			completionscore = 0;
			while (i < s.size() && corruption == 0) {
				char c = s[i];
				i++;
				corruption = parse(closer(c));
			}
			if (corruption > 0) {
				syntaxscore += corruption;
			}
			else{
				v.push_back(completionscore);
			}
		}
		cout << "The total syntax score is " << syntaxscore << endl;
		sort(v.begin(), v.end());
		cout << "The middle completion score is " << v[((v.size() - 1) / 2)] << endl;
	}
	return 0;
}