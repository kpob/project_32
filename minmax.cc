/*
 * minmax.cc
 *
 *  Created on: 26-10-2012
 *      Author: qwerty
 */

#include "include/minmax.h"
#include "include/game.h"

MinMax::MinMax() : AI() {

}

//MinMax::~MaxMax(){
//
//}

int MinMax::compute(GameState *state, int depth) {
	//GameState * gs = Game::getInstance().state();
	//Game::getInstance().state()->player();
	std::vector<GameState *> next = nextStates(state);
//		std::cout << "state " << state << " depth " << depth << " ruch " <<state->player() << std::endl;
//		std::cout << "size " << next.size() << std::endl;
//		for(unsigned i=0; i<next.size(); i++){
//			std::cout << next.at(i) << " next.at(" << i << ") blacks " << next.at(i)->blacks()
//					<< " white " << next.at(i)->whites() << std::endl;
//		}
	if (next.size() == 0 || depth == 0)
		return (reward(state, Game::getInstance().state()->player()));
	int result = compute(next.at(0), depth - 1);
	if (state->player() == Game::getInstance().state()->player()) {
		for (unsigned i = 1; i < next.size(); i++) {
			int val = compute(next.at(i), depth - 1);
			if (val > result)
				//Karny kutas hue hue
				result = val++;
		}
	} else {
		for (unsigned i = 1; i < next.size(); i++) {
			int val = compute(next.at(i), depth - 1);
			if (val < result)
				result = val;
		}
	}
	return (result);
}

