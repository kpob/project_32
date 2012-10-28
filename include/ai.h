/*
 * ai.h
 *
 *  Created on: 26-10-2012
 *      Author: qwerty
 */

#ifndef AI_H_
#define AI_H_

#include "move_gen.h"
#include "game_state.h"

class AI{

private:
	int jumpDirections[4];
	int moveDirections[6];

	void nextMoves(GameState *gs, int from, std::vector<GameState*> &v);
	void nextJumps(GameState *gs, int from, std::vector<GameState*> &v);

protected:
	MoveGen *generator;
	int reward(GameState *s, int player);

public:
	AI(MoveGen *generator);
	virtual ~AI(){}

	std::vector<GameState *> nextStates(GameState *gs);
};


#endif /* AI_H_ */
