#include "pch.h"
#include "Integer.h"
#include <assert.h>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
namespace {
	int char2int(char c) {
		return c - '0';
	}
}
Integer::Integer()
	:
	fString()
{
}

Integer::Integer(const string& input)
	:
	fString(input)
{
}

Integer::~Integer() {}

Integer Integer::substr(size_t pos, size_t len) const {
	return fString.substr(pos, len);
}

void equalizeLengthsPadLeft(Integer& first,	Integer& second) {
	if (first.size() < second.size()) {
		first.padLeft(second.size() - first.size());
	}
	else if (first.size() > second.size()) {
		second.padLeft(first.size() - second.size());
	}
}
void equalizeLengthsPadRight(string& first, string& second) {
	if (first.size() < second.size()) {
		first += string(second.size() - first.size(), '0');
	}
	else if (first.size() > second.size()) {
		second += string(first.size() - second.size(), '0');
	}
}

Integer Integer::operator+(const Integer& other) const {
	// For the time being, just conver to integer and return
	std::string first = fString;

	std::reverse(first.begin(), first.end());
	std::string second = other.fString;
	std::reverse(second.begin(), second.end());
	equalizeLengthsPadRight(first, second);

	std::string::iterator first_it = first.begin();
	std::string::iterator second_it = second.begin();
	std::string resultStr;
	int carry = 0;
	while (first_it != first.end()) {
		int sum = char2int(*first_it) + char2int(*second_it) + carry;
		carry = 0;
		if (sum >= 10) {
			sum = sum % 10;
			carry = 1;
		}
		resultStr += std::to_string(sum);
		first_it++;second_it++;
	}
	if (carry) {
		resultStr += '1';
	}
	std::reverse(resultStr.begin(), resultStr.end());
	return resultStr;
}

Integer Integer::operator-(const Integer& other) const {

	std::string first = fString;
	std::reverse(first.begin(), first.end());
	std::string second = other.fString;
	std::reverse(second.begin(), second.end());

	// Equalize
	equalizeLengthsPadRight(first, second);

	std::string::iterator first_it = first.begin();
	std::string::iterator second_it = second.begin();
	std::string resultStr;
	while (first_it != first.end()) {
		int up = char2int(*first_it);
		int down = char2int(*second_it);
		int localResult;
		if (up >= down) {
			localResult = up - down;
		}
		else {
			// Keep searching forward until you get a non-zero value
			auto next_it = first_it + 1;
			while (true) {
				if (char2int(*next_it) > 0) {
					// Found the first non-zero number
					break;
				}
				next_it++;
			}
			*next_it = std::to_string(char2int(*next_it) - 1)[0];
			// Now chase back to first_it setting 9's 
			// on the way. Make sure everything was 0 
			// beforehand
			next_it--;
			while (next_it != first_it) {
				assert(char2int(*next_it) == 0);
				*next_it = std::to_string(9)[0];
				next_it--;
			}

			localResult = up + 10 - down;
		}
		assert(localResult >= 0);
		resultStr += std::to_string(localResult);
		first_it++;
		second_it++;
	}
	std::reverse(resultStr.begin(), resultStr.end());
	return resultStr;

}

Integer Integer::operator*(const Integer& other) const {
	// Only allow multiplication when size is 1
	assert(size() == other.size() == 1);
	return std::to_string(std::stoi(fString)*std::stoi(other.fString));
}

void Integer::padRight(size_t num) {
	fString += std::string(num, '0');
}

void Integer::padLeft(size_t num) {
	fString.insert(0, num, '0');
}

void Integer::print() const {
	std::cout << fString << std::endl;
}

void Integer::stripLeadingZeros() {
	// Don't strip if all are zeros - this will lead to an empty string
	if (std::all_of(fString.cbegin(), fString.cend(), [](char c) {return ('0' == c); })) {
		return;
	}

	fString.erase(0, fString.find_first_not_of('0'));
}