// convert.cpp : Defines the entry point for the console application.
// 
/* problem statement 
Question: Convert a “string” to float without using any libraries.

	Example 1.
	Input : convert(“123”)
	Output : 123

	Example 2 :
	Input : convert(“1.21”)
	Output : 1.21

	Public void convert(String s)
{
}

*/


#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

//implementation using the built in library function of std::stof()
float convert1(string s)
{
	return stof(s);
}

//test function to display the output
void print_convert1(string s)
{
	try {
		cout << std::stof(s) << std::endl;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
		cout << "You may have entered an invalid string of number" << endl;
	}
}

//implementation using no library
float convert2(string s)
{
	try {
		bool negative = false;
		bool gotPoint = false;
		float factor1 = 1.0;
		int pointdigit = 0;
		float result = 0.0;
		float result_int = 0.0;
		float result_afterpoint = 0.0;
		int nonblankcount = 0;
		int len = s.length();
		const char* t = s.c_str();
		char* cp = (char *)malloc(sizeof(char)*len);
		for (int i = 0; i < len; i++) {
			cp[i] = t[i];
		}
		for (int i = 0; i < len; i++) {
			nonblankcount++;
			switch (t[i]) {
			case ' ':
				nonblankcount--;
				continue;
				break;
			case '.':
				if (gotPoint == false) {
					gotPoint = true;
					result_int = result;
					result = 0.0;
					result_afterpoint = 0.0;
					nonblankcount = 0;
					pointdigit = i+1;
				}
				else
				{
					cout << "invalid input at debug locatio 1" << endl;
					free(cp);
					return -5555.55554f;
				}

				break;
			case '-':
				if ((i == 0) || (nonblankcount == 0))
					negative = true;
				else
				{
					cout << "invalid input at debug location 2" << endl;
					free(cp);
					return -5555.55554f;
				}
				break;
			case '0':
				result = result * 10.0;
				break;
			case '1':
				result = result * 10.0+1.0;
				break;
			case '2':
				result = result * 10.0 + 2.0;
				break;
			case '3':
				result = result * 10.0 + 3.0;
				break;
			case '4':
				result = result * 10.0 + 4.0;
				break;
			case '5':
				result = result * 10.0 + 5.0;
				break;
			case '6':
				result = result * 10.0 + 6.0;
				break;
			case '7':
				result = result * 10.0 + 7.0;
				break;
			case '8':
				result = result * 10.0 + 8.0;
				break;
			case '9':
				result = result * 10.0 + 9.0;
				break;
			default:
				cout << "invalid input at debug loation 3" << endl;
				free(cp);
				return -5555.5555;
				break;
			};
			continue;
		}

		if (gotPoint) {
			for (int i = pointdigit; i < len; i++)
			{
				factor1 = 10.0*factor1;
			}

			result_afterpoint = result;
			result = result_int + result_afterpoint / (1.0*factor1);
		}
	//	else
	//		result = result_int;

		if (negative == true)
			result = -1.0* result;
		return result;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
		cout << "You may have entered an invalid string of number" << endl;
	}
}


//test function to display the output
void print_convert2(string s)
{
	try {
		cout << convert2(s) << std::endl;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
		cout << "You may have entered an invalid string of number" << endl;
	}
}
//This main program runs as a test program to get input and display output for the convert function
int main()
{
	while (true)
	{
		cout << "Please enter a numerical string :" << endl;
		string s;
		cin >> s;
		cout << " the conversion result of using std::stf() is : " << endl;
		print_convert1(s);
		cout << " the conversion result of my implementation is : " << endl;
		print_convert2(s);
	}
    return 0;
}

