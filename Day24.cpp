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

int X[14];
int Y[14];
int Z[14];
int W[14];

void computeHigh() {
	for (W[0] = 4; W[0] < 10; W[0]++) {
		for (W[1] = 8; W[1] < 10; W[1]++){
			for (W[2] = 1; W[2] < 10; W[2]++) {
				for (W[3] = 1; W[3] < 10; W[3]++) {
					cout << W[3] << endl;
					for (W[4] = 1; W[4] < 10; W[4]++) {
						for (W[5] = 1; W[5] < 10; W[5]++) {
							for (W[6] = 1; W[6] < 10; W[6]++) {
								for (W[7] = 1; W[7] < 10; W[7]++) {
									for (W[8] = 1; W[8] < 10; W[8]++) {
										for (W[9] = 1; W[9] < 10; W[9]++) {
											for (W[10] = 1; W[10] < 10; W[10]++) {
												for (W[11] = 1; W[11] < 10; W[11]++) {
													for (W[12] = 1; W[12] < 10; W[12]++) {
														for (W[13] = 1; W[13] < 10; W[13]++) {
															int x = 0;
															int y = 0;
															int z = 0;
															for (int i = 0; i < 14; i++) {
																x = z % 26;
																z /= Z[i];
																if (x + X[i] != W[i]) {
																	z *= 26;
																	z += W[i] + Y[i];
																}
															}
															if (z == 0) {
																cout << "The lowest valid MONAD is ";
																//found it!
																for (int j = 0; j < 14; j++) {
																	cout << W[j];
																}
																cout << endl;
																return;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


void computeLow() {
	for (W[0] = 9; W[0] > 0; W[0]--) {
		for (W[1] = 9; W[1] > 0; W[1]--) {
			for (W[2] = 9; W[2] > 0; W[2]--) {
				for (W[3] = 9; W[3] > 0; W[3]--) {
					for (W[4] = 9; W[4] > 0; W[4]--) {
						for (W[5] = 9; W[5] > 0; W[5]--) {
							for (W[6] = 9; W[6] > 0; W[6]--) {
								for (W[7] = 9; W[7] > 0; W[7]--) {
									for (W[8] = 9; W[8] > 0; W[8]--) {
										for (W[9] = 9; W[9] > 0; W[9]--) {
											for (W[10] = 9; W[10] > 0; W[10]--) {
												for (W[11] = 9; W[11] > 0; W[11]--) {
													for (W[12] = 9; W[12] > 0; W[12]--) {
														for (W[13] = 9; W[13] > 0; W[13]--) {
															int x = 0;
															int y = 0;
															int z = 0;
															for (int i = 0; i < 14; i++) {
																x = z % 26;
																z /= Z[i];
																if (x + X[i] != W[i]) {
																	z *= 26;
																	z += W[i] + Y[i];
																}
															}
															if (z == 0) {
																//found it!
																cout << "The highest valid MONAD is ";
																for (int j = 0; j < 14; j++) {
																	cout << W[j];
																}
																cout << endl;
																return;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int main(int argc, char * argv[]) {
	X[0] = 10;
	Y[0] = 10;
	Z[0] = 1;

	X[1] = 13;
	Y[1] = 5;
	Z[1] = 1;

	X[2] = 15;
	Y[2] = 12;
	Z[2] = 1;

	X[3] = -12;
	Y[3] = 12;
	Z[3] = 26;

	X[4] = 14;
	Y[4] = 6;
	Z[4] = 1;

	X[5] = -2;
	Y[5] = 4;
	Z[5] = 26;

	X[6] = 13;
	Y[6] = 15;
	Z[6] = 1;

	X[7] = -12;
	Y[7] = 3;
	Z[7] = 26;

	X[8] = 15;
	Y[8] = 7;
	Z[8] = 1;

	X[9] = 11;
	Y[9] = 11;
	Z[9] = 1;

	X[10] = -3;
	Y[10] = 2;
	Z[10] = 26;

	X[11] = -13;
	Y[11] = 12;
	Z[11] = 26;

	X[12] = -12;
	Y[12] = 4;
	Z[12] = 26;

	X[13] = -13;
	Y[13] = 11;
	Z[13] = 26;

	computeLow();
	computeHigh();



	return 0;
}