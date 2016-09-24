#include "Neuron.h"


Neuron::Neuron() {
	sum = 0;
};

void Neuron::push_output(pair<string, Neuron*> p)
{
	output.push_back(p);
}

void Neuron::print_output()
{
	for (auto out: output)
	{
		cout << out.first << " ";
	}
	cout << endl;
}

void Neuron::send_output()
{
	if (sum >= threshold || threshold == 0)//TODO~~~~~~~~~~~~~~~~~~Change this threshold logic~~~~~~~~~~~~~~~~~~~~~~ 
	{
		for (auto out : output)
		{
			if (out.first[0] == 's')
			{
				out.first.erase(out.first.begin());//erase the s token before converting to double
				out.second->sum += stod(out.first);//convert string to double and add it to the recieving neuron's sum
			}
			else
				out.second->sum += stod(out.first);//convert string to double and add it to the recieving neuron's sum
		}
	}
}