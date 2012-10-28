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
#include "include/helper.h"

Game::Game() : currentState(0), pWhite(0), pBlack(0){
}

void Game::newGame(){
	currentState = new GameState(0x00000050, 0x02000000, 0, white);
	pWhite = new Player(new MinMax(new MoveGen), white, "nacl");
	pBlack = new Player(new MinMax(new MoveGen), black, "nacl");
}

void Game::newGame(std::string player1, std::string player2){
	std::vector<std::string> pWhiteArgs = helper::string2Player(player1);
	//std::vector<std::string> pBlackArgs = helper::string2Player(player2);

	if(pWhiteArgs.at(1) == "js"){
		pWhite = new Player(0, white, "js");
	}else{
		if(pWhiteArgs.at(0) == "minmax")
			pWhite = new Player(new MinMax(new MoveGen()), white, "nacl");
		else if(pWhiteArgs.at(0) == "ab")
			pWhite = new Player(new MinMax(new MoveGen()), white, "nacl");
		else if(pWhiteArgs.at(0) == "montecarlo")
			pWhite = new Player(new MinMax(new MoveGen()), white, "nacl");
	}

	

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
