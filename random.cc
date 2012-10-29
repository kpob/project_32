/*
 * random.cc
 *
 *  Created on: 29-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#include "include/random.h"
#include "include/game.h"

#include <vector>
#include <stdlib.h>
Random::Random() : AI() {

}

int Random::compute(GameState *gs, int depth){
	//MoveGen &generator = MoveGen::getInstance();
	//std::vector<GameState *> next = nextStates(state);
	return 0;
}

void Random::pickState(){
	std::vector<GameState *> next = nextStates(Game::getInstance().state());
	int random = rand() % next.size();
	Game::getInstance().updateState(next.at(random));
}
