/*
 * ai.cc
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#include "includes/ai.h"
#include "includes/game_state.h"
#include "includes/game.h"
#include <vector>
#include <iostream>

AI::AI() {
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
			nextJumps(gs, i, v);
	}
	return (v);
}

/*
 * MOVES GENERATOR
 */

void AI::nextMoves(GameState *gs, int from, std::vector<GameState*> &v) {
	MoveGen &generator = MoveGen::getInstance();
	GameState *next;
	for (int i = 0; i < 6; i++) {
		next = generator.move(gs, from, from + moveDirections[i], false);
		if (next) {
			next->setPlayer(gs->player());
			next->tooglePlayer();
			if(v.size() > 0){
				unsigned last = v.size()-1;
				if(next->whites() != v.at(last)->whites() || next->blacks() != v.at(last)->blacks()){
					v.push_back(next);
				}else
					delete next;
			}else
				v.push_back(next);
		}
	}
}

/*
 * JUMPS GENERATOR
 */

void AI::nextJumps(GameState *gs, int from, std::vector<GameState*> &v) {

	GameState *next = 0;
	int player = gs->player();
	int jumps = 0;
	int to;
	for (int i = 0; i < 4; i++) {
		to = from + jumpDirections[i];
		if (to <= 31 && to >= 0)
			next = MoveGen::getInstance().jump(gs, from,
					from + jumpDirections[i], false);
		else
			continue;
		if (next) {
			next->setPlayer(player);
			jumps++;
			if (!(gs->queens() & (1 << from)) && (next->queens() & (1 << to))){
				next->tooglePlayer();
				v.push_back(next);
			}else
				nextJumps(next, from + jumpDirections[i], v);
		}

	}
	if (jumps == 0 && gs != Game::getInstance().state()) {
		if(player == white)
			next = new GameState(gs->whites(), gs->blacks(), gs->queens(), black);
		else
			next = new GameState(gs->whites(), gs->blacks(), gs->queens(), white);
		if(v.size() > 0){
			unsigned last = v.size()-1;
			if(next->whites() != v.at(last)->whites() || next->blacks() != v.at(last)->blacks())
				v.push_back(next);
			else
				delete next;
		}else{
			v.push_back(next);
		}
		
	}
}

SearchNode* AI::reward(GameState *s) {
	const int queenVal = 5;
	const int pawnVal = 2;
	BITBOARD pQueens;
	BITBOARD oQueens;
	BITBOARD pPawns;
	BITBOARD oPawns;

	int player = Game::getInstance().state()->player();
	if(player == black){
		pQueens = s->blacks() & s->queens();
		oQueens = s->whites() & s->queens();
		pPawns = s->blacks() & ~s->queens();
		oPawns = s->whites() & ~s->queens();
	}else{
		oQueens = s->blacks() & s->queens();
		pQueens = s->whites() & s->queens();
		oPawns = s->blacks() & ~s->queens();
		pPawns = s->whites() & ~s->queens();
	}
	int result = 0;

	BITBOARD pos;
	for (int i = 0; i < 32; i++) {
		pos = (1 << i);
		if (pos & oQueens)
			result -= queenVal;
		else if (pos & oPawns)
			result -= pawnVal;
		else if ((pos) & pPawns)
			result += pawnVal;
		else if (pos & pQueens)
			result += queenVal;

	}
	if ((oPawns & oQueens) == 0)
		result += 40;
	else if ((pPawns & pQueens) == 0)
		result -= 40;
	//if (player == black)
	//	result = -result;
	//std::cout << "pl " << player << " res " << result << std::endl;;
	return (new SearchNode(s, result));
}


