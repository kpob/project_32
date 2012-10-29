/*
 * random.h
 *
 *  Created on: 29-10-2012
 *      Author: Krzysztof Pobiarżyn
 */
#ifndef RANDOM_H_
#define RANDOM_H_

#include "ai.h"
#include "game_state.h"

class Random : public AI{
private:

public:
	Random();

	int compute(GameState *state, int depth);
	void pickState();
};

#endif
