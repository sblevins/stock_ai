#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Neuron
{
public:
	double sum;
	double threshold;
	vector<pair<string, Neuron*>> output;
	Neuron();
	void push_output(pair<string, Neuron*>);
	void print_output();
	void send_output();//TODO change this after modifying threshold encoding
};



#endif