#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <vector>
#include "Market.h"
#include <string>
#include "input.h"
#include "stocc/stocc.h"
using namespace std;
class Chromosome
{
private:
	
public:
	Chromosome();
	int numNeurons;
	vector<input> inputs;//symbols being input into neural network
	vector<string> outputs;//output symbols


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	TODO modify threshold encoding so that it allows 0 to be set as a threshold
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	vector<double> threshold;



	vector<vector<string>> gene;//genetic code stored as an nxn adjacency matrix
	//input neurons are stored in the FIRST n slots of the gene vector
	//output neurons are stored in the LAST m slots of the gene vector
	string randWeight(bool threshold);//only assigns constant weight if bool is there is a threshold true=threshold false=nothreshold
	void printweights();//prints adjacency matrix of weight values
	void printadj();//prints binary adjacency matrix 1=edge 0=no edge
	void printthreshold();//prints the thresholds of the neurons
	void randFF();//generate random edges and thresholds for feed forward network
	void rand_inputs();//generate random inputs to network
	void print_inputs();//prints info about all inputs
	void compute_network_range();//calculates the date range in which all inputs are active
};


#endif
