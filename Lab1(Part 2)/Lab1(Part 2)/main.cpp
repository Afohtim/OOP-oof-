#include "Game.h"

int main()
{
	Game game1;
	std::vector<std::vector<double> > dices_config({ {0.5, 0.5}, {0.1, 0.2, 0.3, 0.4}, {0.1, 0.2, 0.2, 0.1, 0.1, 0.2, 0.1} });
	game1.set_dices(dices_config);
	game1.show_sums(10);
	system("pause");
}