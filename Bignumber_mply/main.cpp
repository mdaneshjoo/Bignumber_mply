// Bignumber_mply.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>
#include "Integer.h"

Integer multiply(const Integer& inp1, const Integer& inp2) {
	Integer first = inp1;
	Integer second = inp2;

	equalizeLengthsPadLeft(first, second);

	assert(first.size() == second.size());
	size_t sz = first.size();

	// Base case 
	if (sz == 1) {
		return first * second;
	}

	int n = sz / 2;
	Integer A = first.substr(0, n);
	Integer B = first.substr(n, sz - n);
	Integer C = second.substr(0, n);
	Integer D = second.substr(n, sz - n);

	Integer AC = multiply(A, C);
	Integer BD = multiply(B, D);

	Integer A_plus_B = A + B;
	Integer C_plus_D = C + D;
	Integer sum = multiply(A_plus_B, C_plus_D);
	Integer AD_plus_BC = sum - AC - BD;

	AC.padRight(2 * (sz - n));
	AD_plus_BC.padRight(sz - n);

	Integer result = AC + AD_plus_BC + BD;
	result.stripLeadingZeros();

	return result;

}

int main() {
	Integer first("3141592653589793238462643383279502884197169399375105820974944592");
	Integer second("2718281828459045235360287471352662497757247093699959574966967627");

	Integer ans = multiply(first, second);

	ans.print();
	return 0;
}