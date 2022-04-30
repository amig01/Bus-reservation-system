#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

const int BUSES = 10;
const int SEATS = 20;
const int PASSENGERS = 200;
const int CITIES = 10;

const bool EMPTY = true;
const bool BUSY = true;
const bool FREE = false;
const bool SUCCESS = true;
const bool FAIL = false;

const char* file_name = "FILE.dat";

const std::string cities[CITIES] = { "KHIVA", "BUKHARA", "SAMARKAND", "NUKUS", "JIZAKH", "KASHKADARYA", "SURKHANDARYA", "ALAT", "VOBKENT", "GULISTAN" };

int inputInRange(int value1, int value2 = 0)
{
	int input; cin >> input;
	while (cin.fail() || input > max(value1, value2) || input < min(value1, value2))
	{
		cout << "PLEASE ENTER VALID VALUE: ";
		cin.clear();
		cin.ignore(32767, '\n');
		cin >> input;
	}
	return input;
}

void putEnters(int number = 1)
{
	for (int i = 0; i < number; i++)
		cout << endl;
}

int getDigit(int number)
{
	if (number < 9)
		return number;
	else
		return number / 10 + number % 10;
}

int numOfDigits(long number)
{
	return to_string(number).length();
}

long getPrefix(long number, int k)
{
	if (numOfDigits(number) > k)
	{
		string num = to_string(number);
		return stol(num.substr(0, k));
	}
	return number;
}

bool prefixMatched(long number, int d)
{
	return getPrefix(number, numOfDigits(d)) == d;
}

int sumOfDoubleEvenDigits(long int number)
{
	int sum = 0;
	string num = to_string(number);
	for (int i = numOfDigits(number) - 2; i >= 0; i -= 2)
		sum += getDigit(int(num[i] - '0') * 2);

	return sum;
}

int sumOfOddDigits(long number)
{
	int sum = 0;

	for (int i = 0; i < numOfDigits(number) - 1; i += 2)
		sum += to_string(number)[i] - '0';
	return sum;
}

bool isValid(long int& number)
{
	bool valid_digits = (numOfDigits(number) >= 13 && numOfDigits(number) <= 16);
	bool valid_prefixes = (prefixMatched(number, 4) || prefixMatched(number, 5) || prefixMatched(number, 37) || prefixMatched(number, 6));
	if (valid_digits && valid_prefixes)
		return (sumOfDoubleEvenDigits(number) + sumOfOddDigits(number)) % 10 == 0;
}
