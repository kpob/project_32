/*
 * minmax.h
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#ifndef MINMAX_H_
#define MINMAX_H_

#include "ai.h"
#include "game_state.h"

class MinMax : public AI{
private:
	GameState* compute(GameState *state);
	SearchNode* search(GameState* state, int depth);

	int depth;

public:
	MinMax();
	MinMax(int depth);
	//~MinMax();


	void pickState();
	//int max(GameState* state, int depth);
};


#endif /* MINMAX_H_ */
