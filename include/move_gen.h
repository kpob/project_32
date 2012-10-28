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

	//void nextMoves(GameState *gs, int from, std::vector<GameState*> &v);
	//void nextJumps(GameState *gs, int from, std::vector<GameState*> &v);

	//int reward(GameState *s, int player);
	
	
public:
	std::vector<GameState *> genere(int depth);
	//std::vector<GameState*> nextStates(GameState *gs);
	static MoveGen& getInstance() {
		static MoveGen instance;
		return (instance);
	}

	int MinMax(GameState *state, int);

	GameState *move(GameState *state,const int from, const int to, bool);
	GameState *jump(GameState *state,const int from, const int to, bool );

	BITBOARD getJumpers(GameState *state);
	BITBOARD getMovers(GameState *state);

};

//	int nextUpLeft[32] = { -1, 4, 5, 6, 8, 9, 10, 11, -1, 12, 13, 14, 16, 17,
//			18, 19, -1, 20, 21, 22, 24, 25, 26, 27, -1, 28, 29, 30, -1, -1, -1,
//			-1 };
//	int nextUpRight[32] = { 4, 5, 6, 7, 9, 10, 11, -1, 12, 13, 14, 15, 17, 18,
//			19, -1, 20, 21, 22, 23, 25, 26, 27, -1, 28, 29, 30, 31, -1, -1, -1,
//			-1 };
//	int nextDownLeft[32] = { -1, -1, -1, -1, 0, 1, 2, 3, -1, 4, 5, 6, 8, 9, 10,
//			11, -1, 12, 13, 14, 16, 17, 18, 19, -1, 20, 21, 22, 24, 25, 26, 27 };
//	int nextDownRight[32] = { -1, -1, -1, -1, 1, 2, 3, -1, 4, 5, 6, 7, 9, 10,
//			11, -1, 12, 13, 14, 15, 17, 18, 19, -1, 20, 21, 22, 23, 25, 26, 27,
//			-1 };
	//GameState *state;

#endif /* MOVE_GEN_H_ */
