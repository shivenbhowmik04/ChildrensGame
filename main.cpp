#include <iostream>
#include "ChildrenGamev2.h"

int main()
{
	
	Game gameState;
	while (true) {
		if (gameState.Game::input()) {
			continue;
		}
		else {
			return 0;
		}
	}
}

