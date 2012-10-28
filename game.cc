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

#include "include/player.h"
#include "include/move_gen.h"
#include "include/minmax.h"

Game::Game() : currentState(0), pWhite(0), pBlack(0){
}

void Game::newGame(){
	currentState = new GameState(0x00000050, 0x02000000, 0, white);
	pWhite = new Player(new MinMax(new MoveGen), white, "c++");
	pBlack = new Player(new MinMax(new MoveGen), black, "c++");
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
