/*
 * minmax.h
 *
 *  Created on: 26-10-2012
 *      Author: qwerty
 */

#ifndef MINMAX_H_
#define MINMAX_H_

#include "ai.h"
#include "game_state.h"

class MinMax : public AI{

public:
	MinMax(MoveGen *gen);
	//~MinMax();

	int compute(GameState *state, int depth);
};


#endif /* MINMAX_H_ */