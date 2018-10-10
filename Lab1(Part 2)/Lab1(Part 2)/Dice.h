#pragma once
#include<vector>

class Dice
{
private:
	int num_of_edges;
	std::vector<long double> edges_probability;
public:
	int get_max();
	void set_probability(std::vector<double> &probabilities);
	double get_probability(int num);
	Dice(int number_of_edges);
	~Dice();
};

