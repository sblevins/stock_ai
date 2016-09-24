#include "belvis.h"
using namespace std;

string belvis::trim_string(string s, int len)
{
	if (s.size() <= len)
		return s;
	return s.erase(len, string::npos);
}


double belvis::rand_double(double max)
{
	double f = (double)rand() / RAND_MAX + 1.0f;//+1 excludes max
	return f * max;
}


vector<string> belvis::chr_split(string str, char delim)
{
	list<int> indices;//the index of each delimeter
	int chunks = 1;//the number of chunks to split the string into
	vector<string> substrings;
	size_t substring_start = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == delim)
		{
			chunks++;
			string substr = str.substr(substring_start, i - substring_start);
			if (substr != "")
				substrings.push_back(substr);
			substring_start = i + 1;
		}
	}
	string substr = str.substr(substring_start, string::npos);
	if (substr != "")
		substrings.push_back(substr);
	return substrings;
}


bool belvis::prob(double p)
{
	if (static_cast <double> (rand()) / static_cast <double> (RAND_MAX) < p)
		return true;
	return false;
}


string belvis::chr_remove(string str, char remove)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == remove)
		{
			str = str.substr(0, i) + str.substr(i + 1, string::npos);//comebine the half of the string before the delimete with the half after the delimeter
			i -= 1;//account for char being removed
		}
	}
	return str;
}


string belvis::chr_replace(string str, char remove, char replace)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == remove)
			str[i] = replace;
	}
	return str;
}


bool belvis::file_is_empty(ifstream& file)
{
	return file.peek() == ifstream::traits_type::eof();
}