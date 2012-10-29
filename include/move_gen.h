/*
 * move_gen.h
 *
 *  Created on: 24-10-2012
 *      Author: qwerty
 */

#ifndef MOVE_GEN_H_
#define MOVE_GEN_H_

#include <vector>
#include "board.h"
#include "game_state.h"

class MoveGen {

private:

	int jumpDirections[4];
	int moveDirections[6];

	MoveGen();
	MoveGen(const MoveGen &);

	MoveGen& operator=(const MoveGen&);

	GameState * jumpUpLeft(GameState *state,const BITBOARD position);
	GameState * jumpDownLeft(GameState *state,const BITBOARD position);
	GameState * jumpUpRight(GameState *state,const BITBOARD position);
	GameState * jumpDownRight(GameState *state,const BITBOARD position);

	bool isLegalBlackJump(GameState *state, BITBOARD position, int direction);
	GameState * blackJump(GameState *state, BITBOARD position, int direction);

	bool isLegalWhiteJump(GameState *state, BITBOARD position, int direction);
	GameState * whiteJump(GameState *state, BITBOARD position, int direction);

	bool isBlackPawn(GameState *state, BITBOARD position);
	bool isWhitePawn(GameState *state, BITBOARD position);
	bool isQueen(GameState *state, BITBOARD position);

	BITBOARD upLeft(BITBOARD position);
	BITBOARD upRight(BITBOARD position);

	BITBOARD downLeft(BITBOARD position);
	BITBOARD downRight(BITBOARD position);

	bool isOccupied(GameState *state, int field);
	bool isEmpty(GameState *state, int32_t position);
	
public:
	std::vector<GameState *> genere(int depth);

	static MoveGen& getInstance() {
		static MoveGen instance;
		return (instance);
	}

	GameState *move(GameState *state,const int from, const int to, bool);
	GameState *jump(GameState *state,const int from, const int to, bool );

	BITBOARD getJumpers(GameState *state);
	BITBOARD getMovers(GameState *state);

	void nextMove(int from, int to);
	//void nextMove(int from, int to);

};

#endif /* MOVE_GEN_H_ */
