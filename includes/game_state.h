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
	~GameState();

	GameState(BITBOARD w, BITBOARD b, BITBOARD q, int player);

	BITBOARD whites();

	BITBOARD blacks();

	BITBOARD queens();

	BITBOARD queens(int player);

	int player();

	bool operator ==(const GameState& gs){
		return whitePawns==gs.whitePawns && blackPawns==gs.blackPawns && allQueens==gs.allQueens;
	}

	void setState(BITBOARD w, BITBOARD b, BITBOARD q, int player);
	void tooglePlayer();
	void setPlayer(int player);

};

#endif /* GAME_STATE_H_ */
