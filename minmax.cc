/*
 * minmax.cc
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#include "includes/minmax.h"
#include "includes/game.h"
#include "includes/search_node.h"
#include "includes/helper.h"
#include <time.h>
#include <sstream>
#include <iostream>
MinMax::MinMax() :
		AI(), depth(7), serchedStates(0) {
}

MinMax::MinMax(int depth) : AI(), depth(depth){

}


GameState *MinMax::compute(GameState *state) {
	std::vector<GameState *> next = nextStates(state);
	int bv = -10000000;
	GameState* bs = 0;
	serchedStates=0;
	for (unsigned i = 0; i < next.size(); i++) {
		serchedStates++;
		std::vector<GameState *> nn = nextStates(next.at(i));
		SearchNode* val = search(next.at(i), depth);
		if (val->getValue() > bv) {
			std::cout << "log " << "PRZED new value\n"; 
			bs = next.at(i);
			bv = val->getValue();
			std::cout << "log " << "PO new value\n"; 
		}else
			delete val;
	}
	std::cout << "log: " << serchedStates <<"\n"; 
	return (bs);
}

SearchNode* MinMax::search(GameState* state, int depth) {
	serchedStates++;
	std::vector<GameState *> next = nextStates(state);
	if (next.size() == 0 || depth == 0){
		return (reward(state));
	}
	SearchNode *bestMove;
	if(state->player() != Game::getInstance().state()->player())
		bestMove = new SearchNode(0,10000);
	else
		bestMove = new SearchNode(0,-10000);
	if(state->player() == Game::getInstance().state()->player()) {
		for (unsigned i =0; i < next.size(); i++) {
			SearchNode *val = search(next.at(i), depth - 1);
			if (val->getValue() > bestMove->getValue()){
				bestMove->setState(val->getState());
				bestMove->setValue(val->getValue());
				delete val;
			}
		}
	} else {
		for (unsigned i = 0; i < next.size(); i++) {
			SearchNode *val = search(next.at(i), depth - 1);
			if (val->getValue() < bestMove->getValue()){
				bestMove->setState(val->getState());
				bestMove->setValue(val->getValue());
				delete val;
			}
		}
	}

	return (bestMove);
}

void MinMax::pickState(){
	GameState *newState = compute(Game::getInstance().state());
	Game::getInstance().updateState(newState);
}


