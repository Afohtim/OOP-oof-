#include "Dice.h"



int Dice::get_max()
{
	return num_of_edges;
}

void Dice::set_probability(std::vector<double> &probabilities)
{
	if (probabilities.size() != num_of_edges)
	{
		throw;
	}
	for (int i = 0; i < probabilities.size(); ++i)
	{
		edges_probability[i] = probabilities[i];
	}
}

double Dice::get_probability(int num)
{
	return edges_probability[num - 1];
}


Dice::Dice(int number_of_edges)
{
	num_of_edges = number_of_edges;
	edges_probability.resize(number_of_edges, 0);
}


Dice::~Dice()
{
}
