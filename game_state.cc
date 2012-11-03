#include "include/game_state.h"
#include "include/types.h"
#include <iostream>

GameState::GameState(BITBOARD w, BITBOARD b, BITBOARD q) :
	whitePawns(w), blackPawns(b), allQueens(q), currentPlayer(-1){
}

GameState::GameState(BITBOARD w, BITBOARD b, BITBOARD q, int player) :
	whitePawns(w), blackPawns(b), allQueens(q), currentPlayer(player){
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
	}else{
		std::cout << "CHUJ" << std::endl;
	}
}

void GameState::setPlayer(int player){
	currentPlayer = player;

}





