/*
 * game.cc
 *
 *  Created on: 19-10-2012
 *      Author: qwerty
 */

#include "include/game.h"
#include "include/types.h"
#include <stdlib.h>
#include <iostream>

Game::Game() : currentState(0){
}

void Game::newGame(){
	currentState = new GameState(0x00000050, 0x02000000, 0, white);
}

bool Game::isStarted(){
	if(currentState == 0)
		return (false);
	return (true);
}

void Game::updateState(GameState* newState) {
	int pl = currentState->player();
	currentState = newState;
	currentState->setPlayer(pl);
	currentState->tooglePlayer();
}
