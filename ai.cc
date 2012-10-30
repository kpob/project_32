/*
 * ai.cc
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#include "include/ai.h"
#include "include/game_state.h"
#include <vector>

AI::AI(){
	jumpDirections[0] = UP_LEFT;
	jumpDirections[1] = UP_RIGHT;
	jumpDirections[2] = DOWN_LEFT;
	jumpDirections[3] = DOWN_RIGHT;

	moveDirections[0] = 3;
	moveDirections[1] = -3;
	moveDirections[2] = 4;
	moveDirections[3] = -4;
	moveDirections[4] = 5;
	moveDirections[5] = -5;
}

/*
 * STATES GENERATOR
 */

std::vector<GameState*> AI::nextStates(GameState *gs) {
	MoveGen &generator = MoveGen::getInstance();
	std::vector<GameState*> v;
	int player = gs->player();
	for (unsigned i = 0; i < 32; i++) {
		if (player == white) {
			if ((gs->whites() & (1 << i)) == 0)
				continue;
		} else if (player == black) {
			if ((gs->blacks() & (1 << i)) == 0)
				continue;
		}

		if (generator.getJumpers(gs) == 0)
			nextMoves(gs, i, v);
		else
			nextJumps(gs,i, v);
	}
	return (v);
}

/*
 * MOVES GENERATOR
 */

void AI::nextMoves(GameState *gs, int from, std::vector<GameState*> &v) {
	MoveGen &generator = MoveGen::getInstance();
	GameState *next;
	for(int i=0; i<6; i++){
		next = generator.move(gs, from, from + moveDirections[i], false);
		if (next){
			next->setPlayer(gs->player());
			next->tooglePlayer();
			v.push_back(next);
		}
	}
}

/*
 * JUMPS GENERATOR
 */

void AI::nextJumps(GameState *gs, int from, std::vector<GameState*> &v) {
	MoveGen &generator = MoveGen::getInstance();
	GameState *next;
	int jumps = 0;
	for(int i=0; i<4; i++){
		next = generator.jump(gs, from, from+jumpDirections[i], false);
		if(next){
			jumps++;
			if(next->queens() == gs->queens()) //todo: POWINNY BYC DAMKI DANEGO KOLORU
				nextJumps(next,from+jumpDirections[i], v);
			else{ //jesli stal sie damka - koniec ruchu
				next->tooglePlayer();
				v.push_back(next);
			}
		}
	}
	if(jumps==0)
		v.push_back(gs);
}

int AI::reward(GameState *s, int player) {
	const int queenVal = 5;
	const int pawnVal = 2;
	const BITBOARD blackQuuens = s->blacks() & s->queens();
	const BITBOARD whiteQuuens = s->whites() & s->queens();
	const BITBOARD blackPawns = s->blacks() & ~s->queens();
	const BITBOARD whitePawns = s->whites() & ~s->queens();
	int result = 0;

	BITBOARD pos;
	for (int i = 0; i < 32; i++) {
		pos = (1 << pos);
		if (pos & blackQuuens)
			result -= queenVal;
		else if (pos & blackPawns)
			result -= pawnVal;
		else if ((pos) & whitePawns)
			result += pawnVal;
		else if (pos & whiteQuuens)
			result += queenVal;
		if (player == black)
			result = -result;
	}
	return (result);
}

