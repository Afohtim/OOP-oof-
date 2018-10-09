#include "Game.h"



Game::Game()
{
	const int dices_num = 7;
	int arr[dices_num] = {2, 4, 6, 8, 10, 12, 20};
	for (int i = 0; i < dices_num; ++i)
	{
		dices.push_back(Dice(arr[i]));
		double sum = arr[i] * (arr[i] + 1) / 2;
		std::vector<double> probabilities;
		for (double j = 0; j < arr[i]; ++j)
		{
			probabilities.push_back(j / sum);
		}
		dices.back().set_probability(probabilities);
	}
}


Game::~Game()
{
}

void Game::show_sums(int sum)
{
	std::vector<int> rolls(dices.size(), 1);
	int variants = 1;
	for (int i = 0; i < dices.size(); ++i)
	{
		variants *= dices[i].get_max();
	}
	for (int i = 0; i < variants; ++i)
	{
		int current_sum = 0;
		for (auto roll : rolls)
			current_sum += roll;
		if (current_sum == sum)
		{
			for (auto roll : rolls)
				std::cout << roll << ' ';
			double percent = 1;
			for (int j = 0; j < dices.size(); ++j)
			{
				percent *= dices[j].get_probability(rolls[j]);
			}
			std::cout << std::fixed << std::setprecision(2) << percent << "%\n";

		}
	}
	// add 1 to first

}
