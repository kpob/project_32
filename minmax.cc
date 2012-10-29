/*
 * minmax.cc
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#include "include/minmax.h"
#include "include/game.h"

MinMax::MinMax() : AI() {

}

//MinMax::~MaxMax(){
//
//}

int MinMax::compute(GameState *state, int depth) {
	
	std::vector<GameState *> next = nextStates(state);

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

