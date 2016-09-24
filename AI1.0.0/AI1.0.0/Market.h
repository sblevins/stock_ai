#ifndef MARKET_H
#define MARKET_H
#include <cstdlib>
#include <unordered_map>
#include "dirent.h"
#include <iostream>
#include <string>
#include <fstream>
#include "belvis.h"
#include <set>
#include <unordered_set>
using namespace std;
class Market
{
public:
	Market();
	vector<string> symbols;
	unordered_map<int, int> dates;//maps each date starting at the earliest date, to an int starting at 0 
	unordered_map<string, vector<vector<string>>> history;//
	unordered_map<string, pair<int, int>> symbol_range;//maps symbols to their date range
	vector<string> getsymbols(char* directory_name);//returns a vector of all symbols
	void load_equity_data(char*);//reads csv files in specified directory into map
	void map_dates();
	void date_index_to_file(string filename, set<int>);
};

#endif