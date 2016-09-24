#include "Network.h"

using namespace std;

Network::Network(Chromosome c)
{
	for (int i = 0; i < c.numNeurons; i++)//declare vector of empty neurons
	{
		Neuron n;
		neurons.push_back(n);
	}
	for (int i = 0; i < c.numNeurons; i++)
	{
		for (int j = 0; j < c.numNeurons; j++)
		{	
			if (c.gene[i][j] != "0")
			{

				pair<string, Neuron*> p;
				p.first = c.gene[i][j];
				p.second = &neurons[j];
				neurons[i].push_output(p);
				
			}
			neurons[i].threshold = c.threshold[i];//set the threshold of each neuron
		}
	}
}

