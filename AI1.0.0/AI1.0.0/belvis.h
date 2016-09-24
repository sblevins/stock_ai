/*
~~~~~~~~~~~~DISCLAIMER~~~~~~~~~~~~~~~~
the randomness of these random functions is quite bad
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
some useful, but mostly un-related c++ functions
Author: Stephen Blevins
*/
#ifndef BELVIS_H
#define BELVIS_H
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <unordered_map>
#include <fstream>
using namespace std;
class belvis
{
public:
	static string trim_string(string, int);//removes characters off the end of a string so that it is the length of int


	static double rand_double(double max);//generates a random double between 0 and max


	static vector<string> chr_split(string, char);//splits a string into n pieces along a single char delimeter


	static string chr_remove(string, char);//removes all instances of char from a string


	static string chr_replace(string, char remove, char replace);//replaces all instances of remove with replace in string

	//you still need to seed the random number generator using srand() before using this function
	static bool prob(double);//randomly returns true or false based on the probability parameter between 0 and 1


	static bool file_is_empty(ifstream& file);//returns true if a file is empty
};



#endif