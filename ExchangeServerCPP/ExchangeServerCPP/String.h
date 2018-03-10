//
// Created by Shawn Manuel on 1/01/2018.
//

#ifndef SERVERPROGRAM_STRINGPLUSPLUS_H
#define SERVERPROGRAM_STRINGPLUSPLUS_H

#include<iostream>
#include<iomanip>
#include<sstream>
#include<vector>
#include<string>

using namespace std;

class String
{
	public:
		static string charToString(char);
		static string boolToString(bool);
		static bool endsWith(string, string);
		static bool endsWith(string, char);
		static bool startsWith(string, string);
		static bool startsWith(string, char);
		static bool equalsIgnoreCase(string, string);

		static string doubleToString(double, int);
		static double stringToDouble(string);

		static vector<string> stringSplit(string, string);
		static string stringJoin(const vector<string>&, string delimiter = "\n");

		static string toLowerCase(string);
		static string toUpperCase(string);

		static string stringReplace(string, string, string);
		static string trim(string);
};

#endif //SERVERPROGRAM_STRINGPLUSPLUS_H