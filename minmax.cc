/*
 * minmax.cc
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#include "include/minmax.h"
#include "include/game.h"
#include "include/search_node.h"

MinMax::MinMax() :
		AI(), depth(2) {
}

MinMax::MinMax(int depth) : AI(), depth(depth){

}

GameState *MinMax::compute(GameState *state) {
	std::vector<GameState *> next = nextStates(state);
	int bv = -10000000;
	GameState* bs = 0;

	for (unsigned i = 0; i < next.size(); i++) {
//		std::cout << "FOR COMUPTE i = " << i << "\n" << next.at(i)->toString() << std::endl;
		SearchNode* val = search(next.at(i), depth);
		if (val->getValue() > bv) {
			bs = next.at(i);
			bv = val->getValue();
		}
	}
//	std::cout << "RETURN\n" << bs->toString() << std::endl;
	return (bs);
}

SearchNode* MinMax::search(GameState* state, int depth) {
	//std::cout << state << " " << depth << " " << state->player() << std::endl;
	std::vector<GameState *> next = nextStates(state);
	if (next.size() == 0 || depth == 0)
		return (reward(state));
	SearchNode *bestMove;
	if(state->player() != Game::getInstance().state()->player())
		bestMove = new SearchNode(0,10000);// search(next.at(0), depth - 1);
	else
		bestMove = new SearchNode(0,-10000);// search(next.at(0), depth - 1);
	if(state->player() == Game::getInstance().state()->player()) {
		for (unsigned i =0; i < next.size(); i++) {
			SearchNode *val = search(next.at(i), depth - 1);
		//	std::cout << "MAX\nGLEBOKOSC " << depth << " PLAYER " << ((state->player() == black) ? "black\n" : "white\n") << val->toString() << "\nze stanu " << state->toString() << "\n\n";
			if (val->getValue() > bestMove->getValue())
				bestMove = val;
		}
	} else {
		//std::cout << "MIN" << std::endl;
		for (unsigned i = 0; i < next.size(); i++) {
			SearchNode *val = search(next.at(i), depth - 1);
			//std::cout << "MIN\nGLEBOKOSC " << depth << " PLAYER " << ((state->player() == black) ? "black\n" : "white\n") << val->toString() << "\nze stanu " << state->toString() << "\n\n";
			if (val->getValue() < bestMove->getValue())
				bestMove = val;
		}
	}

//	if(bestMove->getState() != 0)
//		std::cout << "WYBRANO\nGLEBOKOSC " << depth << " PLAYER " << ((state->player() == black) ? "black\n" : "white\n") << bestMove->toString() << "\nze stanu " << state->toString() << "\n\n";
//	else
//		std::cout << "null depth " << depth << std::endl;
	return (bestMove);
}

void MinMax::pickState(){
	GameState *newState = compute(Game::getInstance().state());
	Game::getInstance().updateState(newState);
}


