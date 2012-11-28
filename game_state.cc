#include "includes/game_state.h"
#include "includes/types.h"
#include <iostream>

GameState::GameState(BITBOARD w, BITBOARD b, BITBOARD q) :
	whitePawns(w), blackPawns(b), allQueens(q), currentPlayer(-1){
}

GameState::GameState(BITBOARD w, BITBOARD b, BITBOARD q, int player) :
	whitePawns(w), blackPawns(b), allQueens(q), currentPlayer(player){
}

GameState::~GameState(){
}

BITBOARD GameState::whites(){
	return (whitePawns);
}

BITBOARD GameState::blacks(){
	return (blackPawns);
}

BITBOARD GameState::queens(){
	return (allQueens);
}

BITBOARD GameState::queens(int player){
	if(player == black)
		return (allQueens & blackPawns);
	else
		return (allQueens & whitePawns);
}

int GameState::player() {
	return (currentPlayer);
}


void GameState::setState(BITBOARD w, BITBOARD b, BITBOARD q, int player) {
	whitePawns = w;
	blackPawns = b;
	allQueens = q;
	currentPlayer = player;
}

void GameState::tooglePlayer(){

	if(currentPlayer == black){
		currentPlayer = white;
	}else if(currentPlayer == white){
		currentPlayer = black;
	}
}

void GameState::setPlayer(int player){
	currentPlayer = player;

}




