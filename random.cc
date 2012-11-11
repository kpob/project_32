/*
 * random.cc
 *
 *  Created on: 29-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#include "includes/random.h"
#include "includes/game.h"

#include <vector>
#include <stdlib.h>
Random::Random() : AI() {

}

void Random::pickState(){
	std::vector<GameState *> next = nextStates(Game::getInstance().state());
	int random = rand() % next.size();
	Game::getInstance().updateState(next.at(random));
}
