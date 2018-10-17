#pragma once
#include "Dice.h"
#include <iostream>
#include <iomanip>

class Game
{
private:
	std::vector<Dice*> dices;

public:
	Game();
	~Game();

	double show_sums(int sum);
	void set_dices(std::vector<std::vector<double> > config);
};

