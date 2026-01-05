#include <iostream>

class Player {
	double Health;
	int Score;
	bool IsAlive;
};

int main() {
	std::cout << "player class size: " << sizeof(Player) << " bytes" << std::endl;


	std::system("pause");
	return 0;
}