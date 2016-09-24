#include "Market.h"
using namespace std;

void Market::load_equity_data(char* directory)//hot  mess
{
	set<int> tempdates;
	vector<string> files = getsymbols(directory);
	ofstream symbol_range_outfile("symbol_range", fstream::trunc);//currently for testing purposes only
	for (int i = 0; i < files.size(); i++)
	{
		int start_index;
		int end_index;
		vector<vector<string>> symbolvec;
		string value;
		string path = (string)directory + "\\table_" + files[i] + ".csv";
		cout << "loading " << path << "...\n";
		ifstream file(path);
		bool first_iteration = true;
		while (file.good())
		{
			getline(file, value, '\n');
			vector<string> tempvec = belvis::chr_split(value, ',');
			if (first_iteration)
			{
				start_index = stoi(tempvec[0]);
				first_iteration = false;
			}
			if (tempvec.size() != 0)
			{
				tempdates.insert(stoi(tempvec[0]));
				tempvec.erase(tempvec.begin() + 1);
				symbolvec.push_back(tempvec);
				end_index = stoi(tempvec[0]);
			}
			/*for (int i = 0; i < tempvec.size(); i++)
			{
				cout << tempvec[i] << endl;
			}
			system("pause");*/
		}
		file.close();
		pair<int, int> range_pair(start_index, end_index);
		pair<string, pair<int, int>> temp_pair(files[i], range_pair);
		symbol_range.insert(temp_pair);
		pair<string, vector<vector<string>>> p(files[i], symbolvec);
		history.insert(p); 
	}
	date_index_to_file("date_index", tempdates);//saves the date index to a file
	int i = 0;
	for (auto date : tempdates)
	{
		pair<int, int> p;
		p.first = date;
		p.second = i;
		dates.insert(p);
		i++;
	}
	for (auto item : symbol_range)//replace the dates in the symbol_range map with their indexes instead
	{
		item.second.first = dates.at(item.second.first);
		item.second.second = dates.at(item.second.second);
		symbol_range_outfile << item.first << " " << item.second.first << " " << item.second.second << endl;
	}
	symbol_range_outfile.close();
}

Market::Market() {}

vector<string> Market::getsymbols(char* directory)
{	
	if (symbols.size() == 0)
	{
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir(directory)) != NULL)
		{
			while ((ent = readdir(dir)) != NULL)
			{
				symbols.push_back(ent->d_name);//add all files in directory to vector
			}
			closedir(dir);
		}//~~~~~~~~~~~~~~~~THE LINE BELOW MAY CHANGE DEPENDING ON DATA~~~~~~~~~~~~~~~~~~~~
		symbols.erase(symbols.begin(), symbols.begin() + 2);//erase non-data files in directory
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		for (int i = 0; i < symbols.size(); i++)
		{
			symbols[i] = symbols[i].substr(6, string::npos - 3)//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				.erase(symbols[i].substr(6, string::npos - 3).find(".csv"));//~~~this line changes depending on data loaded~~~~~~~~~~~~~~~~~
		}//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	return symbols;
}

//cout << files[i].substr(6, string::npos - 3).erase(files[i].substr(6, string::npos - 3).find(".csv")) << endl;

void Market::map_dates()
{
	for (auto symbol : symbols)
	{
		history.at(symbol);
	}
}


void Market::date_index_to_file(string filename, set<int> s)
{
	ofstream file;
	file.open(filename, fstream::trunc);//discard the contents of the existing file to be replaced
	int i = 0;
	for (auto date : s)
	{
		file << date << " " << i << endl;
		i++;
	}
	file.close();
}