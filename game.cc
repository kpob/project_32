/*
 * game.cc
 *
 *  Created on: 19-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#include "includes/game.h"
#include "includes/types.h"
#include <stdlib.h>
#include <iostream>

#include "includes/player.h"
#include "includes/move_gen.h"
#include "includes/minmax.h"
#include "includes/random.h"
#include "includes/helper.h"

Game::Game() : currentState(0), previousState(0), pWhite(0), pBlack(0), isSet(false){
}

void Game::newGame(){
	currentState = new GameState(0x00000fff, 0xfff00000, 0, black);
}

void Game::setPlayers(std::string player1, std::string player2){
	std::vector<std::string> pBlackArgs = helper::args2vector(player1);
	std::vector<std::string> pWhiteArgs = helper::args2vector(player2);

	if(pWhiteArgs.at(1) == "js"){
		pWhite = new Player(0, white, "js");
	}else{
		if(pWhiteArgs.at(2).find("minmax") == 0)
			pWhite = new Player(new MinMax(), white, "nacl");
		else if(pWhiteArgs.at(2) == "ab")
			pWhite = new Player(new MinMax(), white, "nacl");
		else if(pWhiteArgs.at(2) == "montecarlo")
			pWhite = new Player(new MinMax(), white, "nacl");
		else if(pWhiteArgs.at(2) == "random")
			pWhite = new Player(new Random(), white, "nacl");
	}

	if(pBlackArgs.at(1) == "js"){
		pBlack = new Player(0, black, "js");
	}else{
		if(pBlackArgs.at(2) == "minmax")
			pBlack = new Player(new MinMax(), black, "nacl");
		else if(pBlackArgs.at(2) == "ab")
			pBlack = new Player(new MinMax(), black, "nacl");
		else if(pBlackArgs.at(2) == "montecarlo")
			pBlack = new Player(new MinMax(), black, "nacl");
		else if(pBlackArgs.at(2) == "random")
			pBlack = new Player(new Random(), black, "nacl");
	}

	isSet = true;
}

bool Game::isStarted(){
	if(currentState == 0)
		return (false);
	return (true);
}

bool Game::arePlayersSet(){
	if(isSet == false)
		return (false);
	return (true);
}

void Game::updateState(GameState* newState) {
	//int pl = currentState->player();
	previousState = currentState;
	currentState = newState;
	currentState->setPlayer(previousState->player());
	//currentState->tooglePlayer();
}

BITBOARD Game::lastMoveBitboard(){
	BITBOARD move = 0;
	if(previousState->player() == white)
		move = previousState->whites() ^ currentState->whites();
	else	
		move = previousState->blacks() ^ currentState->blacks();
	return (move);
}

BITBOARD Game::opponentPawnsDiffBitboard(){
	BITBOARD pawnsDiff;
	if(previousState->player() == white)
		pawnsDiff = previousState->blacks() ^ currentState->blacks();
	else
		pawnsDiff = previousState->whites() ^ currentState->whites();
	return (pawnsDiff);
}

Player *Game::currentPlayer(){
	if(currentState->player() == white)
		return pWhite;
	return pBlack;
}
