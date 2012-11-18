/*
 * search_node.cc
 *
 *  Created on: 31-10-2012
 *      Author: KrzysztofPobiarżyn
 */
#include "includes/search_node.h"
#include "includes/game.h"

SearchNode::SearchNode(GameState *state, int value) : state(state), value(value){

}

SearchNode::~SearchNode(){
	//if(state != Game::getInstance().state())
	delete state;
}

int SearchNode::getValue(){
	return (value);
}

GameState *SearchNode::getState(){
	return (state);
}

void SearchNode::setValue(int val){
	value = val;
}

void SearchNode::setState(GameState* val){
	delete state;
	state = new GameState(val->whites(), val->blacks(), val->queens(), val->player());
}
