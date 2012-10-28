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

Game::Game() : currentState(0), pWhite(0), pBlack(0), isSet(false){
}

void Game::newGame(){
	currentState = new GameState(0x00000fff, 0xfff00000, 0, black);
}

void Game::setPlayers(std::string player1, std::string player2){
	std::vector<std::string> pWhiteArgs = helper::string2Player(player1);
	std::vector<std::string> pBlackArgs = helper::string2Player(player2);

	if(pWhiteArgs.at(1) == "js"){
		pWhite = new Player(0, white, "js");
	}else{
		if(pWhiteArgs.at(2) == "minmax")
			pWhite = new Player(new MinMax(new MoveGen()), white, "nacl");
		else if(pWhiteArgs.at(2) == "ab")
			pWhite = new Player(new MinMax(new MoveGen()), white, "nacl");
		else if(pWhiteArgs.at(2) == "montecarlo")
			pWhite = new Player(new MinMax(new MoveGen()), white, "nacl");
	}

	if(pBlackArgs.at(1) == "js"){
		pBlack = new Player(0, black, "js");
	}else{
		if(pBlackArgs.at(2) == "minmax")
			pBlack = new Player(new MinMax(new MoveGen()), black, "nacl");
		else if(pBlackArgs.at(2) == "ab")
			pBlack = new Player(new MinMax(new MoveGen()), black, "nacl");
		else if(pBlackArgs.at(2) == "montecarlo")
			pBlack = new Player(new MinMax(new MoveGen()), black, "nacl");
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
