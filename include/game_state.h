/*
 * game_state.h
 *
 *  Created on: 19-10-2012
 *      Author: qwerty
 */

#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "types.h"

class GameState{

private:
	BITBOARD whitePawns;
	BITBOARD blackPawns;
	BITBOARD allQueens;

	int currentPlayer;

public:

	GameState(BITBOARD w, BITBOARD b, BITBOARD q);

	GameState(BITBOARD w, BITBOARD b, BITBOARD q, int player);

	BITBOARD whites(){
		return (whitePawns);
	}

	BITBOARD blacks(){
		return (blackPawns);
	}

	BITBOARD queens(){
		return (allQueens);
	}

	BITBOARD queens(int player){
		if(player == black)
			return (allQueens & blackPawns);
		else
			return (allQueens & whitePawns);
	}

	int player() {
		return (currentPlayer);
	}

	void setState(BITBOARD w, BITBOARD b, BITBOARD q, int player);
	void tooglePlayer();
	void setPlayer(int player);

};

#endif /* GAME_STATE_H_ */
