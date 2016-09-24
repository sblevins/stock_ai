#ifndef INPUT_H
#define INPUT_H
#include <string>
#include <vector>
using namespace std;

class input
{
public:
	string symbol;//ticker symbol
	int date_offset;//the offset from the date being tested
	int data_index;//which piece of data is being retrieved high/low/open/close/volume
};



#endif