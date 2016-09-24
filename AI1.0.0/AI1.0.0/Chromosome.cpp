#include "Chromosome.h"
#include <random>
#include <iostream>
#include "stocc\stocc.h"
using namespace std;

Chromosome::Chromosome(){}

string Chromosome::randWeight(bool thresh)
{
	string weight;
	//~~~~~~TODO this distribution is not very modular and needs tweaking for final version~~~~~~~~~~~~~
	//~~~~~~TODO change seed to StochasticLib1 random number generator~~~~~~~~~~~~~~~~
	double num = StochasticLib1(rand()).Normal(0, 1);//random number generated along normal distribution standard deviation = 1, mean = 0
	if (rand() % 2 == 0)//no edge
		weight = "0";
	else if (rand() % 2 == 0 || !thresh)//output sum of all inputs multiplied by some weight
		weight = "s" + to_string(num);
	else//output is a constant value
		weight = to_string(num);
	return weight;
}

void Chromosome::printweights()
{
	for (int i = 0; i < gene.size(); i++)
	{
		for (int j = 0; j < gene[i].size(); j++)
		{
			cout << gene[i][j] << " ";
		}
		cout << endl;
	}
}

void Chromosome::printadj()
{
	for (int i = 0; i < gene.size(); i++)
	{
		for (int j = 0; j < gene[i].size(); j++)
		{
			if (gene[i][j] == "0")
				cout << "0 ";
			else
				cout << "1 ";
		}
		cout << endl;
	}
}

void Chromosome::randFF()
{
	StochasticLib1 stoc(rand());
	for (int i = 0; i < inputs.size(); i++)//for each input node generate random edges to the rest of the graph
	{
		vector<string> tempvec;//vector that stores the output edges of a single neuron
		//the if else block correspond to whether or not a threshold is set
		if (belvis::prob(.2))//TODO~~~~~~~~~~~~~~This is not modular~~~~~~~~~~~~~~~~~
		{
			threshold.push_back(stoc.Normal(0, 3.0));//assign neurons a threshold along a normal distribution
			for (int j = 0; j < inputs.size(); j++)//push zeros into the input nodes' edge vectors so they dont input into other input nodes
				tempvec.push_back("0");
			for (int j = inputs.size(); j < numNeurons; j++)//generate random edges for the rest of the graph
				tempvec.push_back(belvis::trim_string(randWeight(true), 10));
			gene.push_back(tempvec);
		}
		else
		{
			threshold.push_back(0);
			for (int j = 0; j < inputs.size(); j++)//push zeros into the input nodes' edge vectors so they dont input into other input nodes
				tempvec.push_back("0");
			for (int j = inputs.size(); j < numNeurons; j++)//generate random edges for the rest of the graph
				tempvec.push_back(belvis::trim_string(randWeight(false), 10));
			gene.push_back(tempvec);
		}
	}
	for (int x = inputs.size(); x < numNeurons; x++)//generate the rest of the matrix without cycles
	{
		vector<string> tempvec; //vector that stores the output edges of a single neuron
		if (belvis::prob(.2))//TODO~~~~~~~~~~~~~~This is not modular~~~~~~~~~~~~~~~~~
		{
			threshold.push_back(stoc.Normal(0, 3.0));//assign neurons a threshold along a normal distribution
			for (int j = 0; j < x + 1; j++)//in order for the matrix to represent a DAG there must be all zeroes on and below its scalar
				tempvec.push_back("0");//assign all zeros below the scalar
			for (int j = x + 1; j < numNeurons; j++)
				tempvec.push_back(belvis::trim_string(randWeight(true), 10));//assign random weights above the scalar
			gene.push_back(tempvec);
		}
		else
		{
			threshold.push_back(0);
			for (int j = 0; j < x + 1; j++)//in order for the matrix to represent a DAG there must be all zeroes on and below its scalar
				tempvec.push_back("0");//assign all zeros below the scalar
			for (int j = x + 1; j < numNeurons; j++)
				tempvec.push_back(belvis::trim_string(randWeight(false), 10));//assign random weights above the scalar
			gene.push_back(tempvec);
		}
	}
}

void Chromosome::rand_inputs() 
{
	StochasticLib1 stoc(rand());
	Market m;//TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~change this so all chromosomes reference the same market object~~~~~
	vector<string> symbols = m.getsymbols("daily");
	for (int i = 0; i < numNeurons / 3; i++)
	{
		struct input temp;
		temp.symbol = symbols[rand() % symbols.size()];
		temp.date_offset = (int)abs(stoc.Normal(0, 10));
		temp.data_index = rand() % 5;//which piece of data about the symbol is being selected
		inputs.push_back(temp);
	}
}

void Chromosome::printthreshold()
{
	for (auto i : threshold)
	{
		cout << i << endl;
	}
}

void Chromosome::print_inputs()
{
	for (auto input : inputs)
	{
		cout << input.symbol << " " << input.date_offset << " " << input.data_index << endl;
	}
}