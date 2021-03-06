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
long long i;
long long total;

long long binary(string str, long long k, long long l) {
	long long n = 0;
	for (long long  j = 0; j < l; j++) {
		n *= 2;
		if (str[k] == '1') {
			n++;
		}
		k++;
		
	}
	return n;
}

long long evaluate(int typeID, long long value, long long result, bool first) {

	if (first) {
		return result;
	}


	if (typeID == 0) {
		return value + result;
	}
	if (typeID == 1) {
		return value * result;
	}	
	if (typeID == 2) {
		return min(value, result);
	}
	if (typeID == 3) {
		return max(value, result);
	}
	
	if (typeID == 5) {
		if (value > result) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if (typeID == 6) {
		if (value < result) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if (typeID == 7) {
		if (value == result) {
			return 1;
		}
		else {
			return 0;
		}
	}

}

long long parsePacket() {
	int version = binary(s, i, 3);
	i += 3;
	total += version;
	int typeID = binary(s, i, 3);
	i += 3;
	if (typeID == 4) {//literal
		string l;
		while (s[i] == '1') {
			i++;
			for (int j = 0; j < 4; j++) {
				l.push_back(s[i]);
				i++;
			}
		}
		i++;//we reached the leading zero
		for (int j = 0; j < 4; j++) {
			l.push_back(s[i]);
			i++;
		}
		long long lit = binary(l, 0, l.size());
		//cout << "Literal value " << lit << endl;
		return lit;
	}
	else {//operator
		long long value = 0;
		bool first = true;
		if (s[i] == '0') {//check length type ID
			i++;
			long long l = binary(s, i, 15);
			i += 15;
			long long end = i + l;
			while (i < end) {
				long long result = parsePacket();
				value = evaluate(typeID, value, result, first);
				first = false;
			}
			//cout << "Packet version: " << version << " . TypeID : " << typeID << endl;
			//cout << "Value " << value << endl;
			return value;
		}
		else {//length type is 1
			i++;
			long long  l = binary(s, i, 11);
			i += 11;
			for (long long  j = 0; j < l; j++) {
				long long result = parsePacket();
				value = evaluate(typeID, value, result, first);
				first = false;
			}
			//cout << "Packet version: " << version << " . TypeID : " << typeID << endl;
			//cout << "Value " << value << endl;
			return value;
		}
	}
}

int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string in;
		infile >> in;
		for (int i = 0; i < in.size(); i++) {
			switch(in[i]){
				case '0':
					s.append("0000");
					break;
				case '1':
					s.append("0001");
					break;
				case '2':
					s.append("0010");
					break;
				case '3':
					s.append("0011");
					break;
				case '4':
					s.append("0100");
					break;
				case '5':
					s.append("0101");
					break;
				case '6':
					s.append("0110");
					break;
				case '7':
					s.append("0111");
					break;
				case '8':
					s.append("1000");
					break;
				case '9':
					s.append("1001");
					break;
				case 'A':
					s.append("1010");
					break;
				case 'B':
					s.append("1011");
					break;
				case 'C':
					s.append("1100");
					break;
				case 'D':
					s.append("1101");
					break;
				case 'E':
					s.append("1110");
					break;
				case 'F':
					s.append("1111");
					break;
			}
		}
		total = 0;
		i = 0;
		long long result = parsePacket();
		cout << "The total packet versions was " << total << endl;
		cout << "The result of the calculation was " << result << endl;
	}
	return 0;
}