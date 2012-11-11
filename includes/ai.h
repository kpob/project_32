/*
 * ai.h
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#ifndef AI_H_
#define AI_H_

#include "move_gen.h"
#include "game_state.h"
#include "search_node.h"

class AI{

private:
	int jumpDirections[4];
	int moveDirections[6];

	void nextMoves(GameState *gs, int from, std::vector<GameState*> &v);
	void nextJumps(GameState *gs, int from, std::vector<GameState*> &v);

protected:


public:
	AI();
	virtual ~AI(){}
	virtual void pickState() = 0;
	std::vector<GameState *> nextStates(GameState *gs);
	SearchNode* reward(GameState *s);
	
};


#endif /* AI_H_ */
