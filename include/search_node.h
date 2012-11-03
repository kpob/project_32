/*
 * search_node.h
 *
 *  Created on: 31-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#ifndef SEARCH_NODE_H_
#define SEARCH_NODE_H_

#include "game_state.h"
class SearchNode{
private:
	GameState *state;
	int value;

public:
	SearchNode(GameState *state, int value);

	int getValue();
	GameState* getState();

	void setValue(int val);

};


#endif /* SEARCH_NODE_H_ */
