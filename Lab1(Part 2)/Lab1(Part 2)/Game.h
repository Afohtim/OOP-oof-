#pragma once
#include "Dice.h"
#include <iostream>
#include <iomanip>

class Game
{
private:
	std::vector<Dice> dices;
public:
	Game();
	~Game();

	void show_sums(int sum);
};

