#include "include/move_gen.h"
#include "include/helper.h"
#include <stdint.h>
#include <iostream>
#include "include/game.h"
#include "include/game_state.h"

MoveGen::MoveGen(){
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

std::vector<GameState*> MoveGen::nextStates(GameState *gs) {
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

		if (!getJumpers(gs))
			nextMoves(gs, i, v);
		else
			nextJumps(gs,i, v);
	}
	return (v);
}

/*
 * MOVES GENERATOR
 */

void MoveGen::nextMoves(GameState *gs, int from, std::vector<GameState*> &v) {
	GameState *next;
	for(int i=0; i<6; i++){
		next = move(gs, from, from + moveDirections[i], false);
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

void MoveGen::nextJumps(GameState *gs, int from, std::vector<GameState*> &v) {
	GameState *next;
	int jumps = 0;
	for(int i=0; i<4; i++){
		next = jump(gs, from, from+jumpDirections[i], false);
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

/*
 * AI ALGORITIHMS
 */

int MoveGen::MinMax(GameState *state, int depth){
	//GameState * gs = Game::getInstance().state();
	//Game::getInstance().state()->player();
	std::vector<GameState *> next = nextStates(state);
	std::cout << "state " << state << " depth " << depth << " ruch " <<state->player() << std::endl;
	std::cout << "size " << next.size() << std::endl;
	for(unsigned i=0; i<next.size(); i++){
		std::cout << next.at(i) << " next.at(" << i << ") blacks " << next.at(i)->blacks()
				<< " white " << next.at(i)->whites() << std::endl;
	}
	if (next.size() == 0 || depth == 0)
		return (reward(state, Game::getInstance().state()->player()));
	//std::cout << "next.at(0) " << next.at(0)->blacks() << " " << next.at(0)->whites() << std::endl;
	int result = MinMax(next.at(0), depth-1);
	if(state->player() == Game::getInstance().state()->player()){
		std::cout << "me" << std::endl;
		for(unsigned i=1; i<next.size(); i++){
			int val = MinMax(next.at(i), depth-1);
			if(val > result)
				result = val;
		}
	}else{
		std::cout << "opp" << std::endl;
		for(unsigned i=1; i<next.size(); i++){
			int val = MinMax(next.at(i), depth-1);
			if(val < result)
				result = val;
		}
	}
	return (result);
}

int MoveGen::reward(GameState *s, int player) {
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
	std::cout << "rew " << result << std::endl;
	return (result);
}

/*
 * move_gen.cc
 *
 *  Created on: 24-10-2012
 *      Author: qwerty
 */

bool MoveGen::isEmpty(GameState *state, int32_t position) {
	return (((state->whites() | state->blacks()) & position) ? false : true);
}

/*
 *  Poniższe fukcje zwracają nowe pozycje po ruchach we wszystkich kierunkach
 */

BITBOARD MoveGen::upLeft(BITBOARD position) {
	return (((position & left3_5mask) << 3) | ((position & left4mask) << 4));
}

BITBOARD MoveGen::upRight(BITBOARD position) {
	return (((position & right4mask) << 4) | ((position & right5_3mask) << 5));
}

BITBOARD MoveGen::downLeft(BITBOARD position) {
	return (((position & left3_5mask) >> 5) | ((position & left4mask) >> 4));
}

BITBOARD MoveGen::downRight(BITBOARD position) {
	return (((position & right4mask) >> 4) | ((position & right5_3mask) >> 3));
}

GameState *MoveGen::move(GameState *gs, const int from, const int to, bool isReal) {
	BITBOARD position = helper::shift(from);
	BITBOARD moveResult = 0;

	BITBOARD whites = gs->whites();
	BITBOARD blacks = gs->blacks();
	BITBOARD queens = gs->queens();
	int player = gs->player();
	GameState *newState = 0;

	int diff = to - from;

	if (isWhitePawn(gs, position)) {
		if (((left3_5mask & position) && diff == 3) || ((left4mask & position) && diff == 4))
			moveResult = upLeft(position);
		else if (((right4mask & position) && diff == 4) || ((right5_3mask & position) && diff == 5))
			moveResult = upRight(position);
	} else if (isBlackPawn(gs, position)) {
		if (((left3_5mask & position) && diff == -5) || ((left4mask & position) && diff == -4))
			moveResult = downLeft(position);
		else if (((right4mask & position) && diff == -4) || ((right5_3mask & position) && diff == -3))
			moveResult = downRight(position);
	} else if (isQueen(gs, position)) {
		if (((left3_5mask & position) && diff == 3) || ((left4mask & position) && diff == 4))
			moveResult = upLeft(position);
		else if (((right4mask & position) && diff == 4) || ((right5_3mask & position) && diff == 5))
			moveResult = upRight(position);
		else if (((left3_5mask & position) && diff == -5) || ((left4mask & position) && diff == -4))
			moveResult = downLeft(position);
		else if (((right4mask & position) && diff == -4) || ((right5_3mask & position) && diff == -3))
			moveResult = downRight(position);
	}

	if (isEmpty(gs, moveResult) && moveResult) {
		if (player == white)
			whites ^= position | moveResult;
		else
			blacks ^= position | moveResult;
		if (((moveResult & blackLastLine) || (moveResult & whiteLastLine)) && !isQueen(gs, position))
			queens |= moveResult;
		if (position & queens)
			queens ^= position | moveResult;
		newState = new GameState(whites, blacks, queens);
	} else
		moveResult = 0;

	if (isReal && moveResult)
		Game::getInstance().updateState(newState);


	return (newState);
}

bool MoveGen::isBlackPawn(GameState *state, BITBOARD position) {
	return ((state->blacks() & ~state->queens() & position) && state->player() == black);
}

bool MoveGen::isWhitePawn(GameState *state, BITBOARD position) {
	return ((state->whites() & ~state->queens() & position) && state->player() == white);
}

bool MoveGen::isQueen(GameState *state, BITBOARD position) {
	return (state->queens() & position);
}

GameState *MoveGen::jump(GameState *state, const int fieldNumber, const int to, bool isReal) {
	const BITBOARD position = helper::shift(fieldNumber);

	int direction = to - fieldNumber;
	GameState *newState = 0;
	switch (direction) {
	case UP_LEFT:
		newState = jumpUpLeft(state, position);
		break;
	case DOWN_LEFT:
		newState = jumpDownLeft(state, position);
		break;
	case UP_RIGHT:
		newState = jumpUpRight(state, position);
		break;
	case DOWN_RIGHT:
		newState = jumpDownRight(state, position);
		break;
	default:
		return (0);
	}
	if (isReal && newState != 0)
		Game::getInstance().updateState(newState);
	return (newState);
}

/*
 *  Poniższe fukcje zwracają nowe pozycje po atakach we wszystkich kierunkach
 */

GameState *MoveGen::jumpUpLeft(GameState *state, BITBOARD position) {
	if (state->player() == white && isLegalWhiteJump(state, position, UP_LEFT))
		return (whiteJump(state, position, UP_LEFT));
	else if (state->player() == black && isLegalBlackJump(state, position, UP_LEFT))
		return (blackJump(state, position, UP_LEFT));
	return (0);
}

GameState *MoveGen::jumpDownLeft(GameState *state, BITBOARD position) {
	if (state->player() == white && isLegalWhiteJump(state, position, DOWN_LEFT))
		return (whiteJump(state, position, DOWN_LEFT));
	else if (state->player() == black && isLegalBlackJump(state, position, DOWN_LEFT)) {
		return (blackJump(state, position, DOWN_LEFT));
	}
	return (0);
}

GameState *MoveGen::jumpUpRight(GameState *state, BITBOARD position) {
	if (state->player() == white && isLegalWhiteJump(state, position, UP_RIGHT))
		return (whiteJump(state, position, UP_RIGHT));
	else if (state->player() == black && isLegalBlackJump(state, position, UP_RIGHT))
		return (blackJump(state, position, UP_RIGHT));
	return (0);
}

GameState *MoveGen::jumpDownRight(GameState *state, BITBOARD position) {
	if (state->player() == white && isLegalWhiteJump(state, position, DOWN_RIGHT))
		return (whiteJump(state, position, DOWN_RIGHT));
	else if (state->player() == black && isLegalBlackJump(state, position, DOWN_RIGHT))
		return (blackJump(state, position, DOWN_RIGHT));
	return (0);
}

/*
 * 	BLACK JUMPS
 */

bool MoveGen::isLegalBlackJump(GameState *state, BITBOARD position, int direction) {
	BITBOARD whites = state->whites();
	switch (direction) {
	case UP_LEFT:
		return ((upLeft(position) & whites) && isEmpty(state, (position << 7))
				&& isQueen(state, position));
	case UP_RIGHT:
		return ((upRight(position) & whites) && isEmpty(state, (position << 9))
				&& isQueen(state, position));
	case DOWN_LEFT:
		return ((downLeft(position) & whites) && isEmpty(state, (position >> 9)));
	case DOWN_RIGHT:
		return ((downRight(position) & whites) && isEmpty(state, (position >> 7)));
	default:
		return (false);
	}
}

GameState *MoveGen::blackJump(GameState *state, BITBOARD position, int direction) {
	BITBOARD targetPosition = 0;
	BITBOARD move = 0;

	BITBOARD whites = state->whites();
	BITBOARD blacks = state->blacks();
	BITBOARD queens = state->queens();
	switch (direction) {
	case UP_LEFT:
		targetPosition = position << 7;
		move = upLeft(position);
		break;
	case UP_RIGHT:
		targetPosition = position << 9;
		move = upRight(position);
		break;
	case DOWN_LEFT:
		targetPosition = position >> 9;
		move = downLeft(position);
		break;
	case DOWN_RIGHT:
		targetPosition = position >> 7;
		move = downRight(position);
		break;
	}
	whites ^= move;
	blacks ^= position; 		//zdejmij czarny ze starej pozycji
	blacks ^= targetPosition; 	//postaw czarny
	if (((targetPosition & blackLastLine)) && !isQueen(state, position))
		queens |= targetPosition;
	if (position & queens)
		queens ^= targetPosition | position;
	return (new GameState(whites, blacks, queens));
}

/*
 * 	WHITE JUMPS
 */

bool MoveGen::isLegalWhiteJump(GameState *state, BITBOARD position,
		int direction) {
	BITBOARD blacks = state->blacks();
	switch (direction) {
	case UP_LEFT:
		return ((upLeft(position) & blacks) && isEmpty(state, (position << 7)));
	case UP_RIGHT:
		return ((upRight(position) & blacks) && isEmpty(state, (position << 9)));
	case DOWN_LEFT:
		return ((downLeft(position) & blacks) && isEmpty(state, (position >> 9))
				&& isQueen(state, position));
	case DOWN_RIGHT:
		return ((downRight(position) & blacks)
				&& isEmpty(state, (position >> 7)) && isQueen(state, position));
	default:
		return (false);
	}
}

GameState *MoveGen::whiteJump(GameState *state, BITBOARD position, int direction) {
	BITBOARD targetPosition = 0;
	BITBOARD move = 0;

	BITBOARD whites = state->whites();
	BITBOARD blacks = state->blacks();
	BITBOARD queens = state->queens();

	switch (direction) {
	case UP_LEFT:
		targetPosition = position << 7;
		move = upLeft(position);
		break;
	case UP_RIGHT:
		targetPosition = position << 9;
		move = upRight(position);
		break;
	case DOWN_LEFT:
		targetPosition = position >> 9;
		move = downLeft(position);
		break;
	case DOWN_RIGHT:
		targetPosition = position >> 7;
		move = downRight(position);
		break;
	}

	blacks ^= move;
	whites ^= position; 		//zdejmij czarny ze starej pozycji
	whites ^= targetPosition;	//postaw czarny

	if (((targetPosition & whiteLastLine)) && !isQueen(state, position)) // jesli nie jest damka
		queens |= targetPosition;										//zrob damke
	if (position & queens)												//jesli damka
		queens ^= targetPosition | position;							//przesun
	return (new GameState(whites, blacks, queens));
}

/*
 * 	GETTING MOVERS AND JUMPERS
 */

BITBOARD MoveGen::getMovers(GameState *state) {
	BITBOARD whites = state->whites();
	BITBOARD blacks = state->blacks();
	BITBOARD queens = state->queens();

	BITBOARD player = 0;
	BITBOARD opponent = 0;
	BITBOARD playerQueens = 0;

	if (state->player() == white) {
		player = whites;
		opponent = blacks;
		playerQueens = player & queens;
	} else {
		opponent = helper::reverse(whites);
		player = helper::reverse(blacks);
		playerQueens = player & helper::reverse(queens);
	}

	const BITBOARD nOcc = ~(opponent | player);

	BITBOARD movers = (nOcc >> 4) & player;
	movers |= ((nOcc & left3_5mask) >> 5) & player;
	movers |= ((nOcc & right5_3mask) >> 3) & player;

	if (playerQueens) {
		movers |= (nOcc << 4) & playerQueens;
		movers |= ((nOcc & left3_5mask) << 5) & playerQueens;
		movers |= ((nOcc & right5_3mask) << 3) & playerQueens;
	}

	if (state->player() == black)
		movers = helper::reverse(movers);

	return (movers);
}

BITBOARD MoveGen::getJumpers(GameState *state) {
	BITBOARD whites = state->whites();
	BITBOARD blacks = state->blacks();
	BITBOARD queens = state->queens();

	BITBOARD player = 0;
	BITBOARD opponent = 0;
	BITBOARD playerQueens = 0;

	if (state->player() == white) {
		player = whites;
		opponent = blacks;
		playerQueens = player & queens;
	} else {
		opponent = helper::reverse(whites);
		player = helper::reverse(blacks);
		playerQueens = player & helper::reverse(queens);
	}

	const BITBOARD nOcc = ~(opponent | player);
	BITBOARD movers = 0;

	//bicie w przód
	//z każdego rzędu możliwy jest ruch o 4 pola więc najpierw porownujemy
	//wolne pola przesuniete o 4 z pionkami przeciwnika, wtedy wiemy że nasz
	//pionek ruszy się o 3 lub 5 pól w zależności od kierunku
	//potem sprawdzamy analogiczny warunek - wolne pole znajduje się 3 lub 5 pól
	//za przeciwnikiem, a przeciwnik o 4 pola od naszego piona
	//bicie damek (czyli bicie do tyłu odbywa się analogicznie)

	BITBOARD temp = (nOcc >> 4) & opponent;
	if (temp)
		movers |= (((temp & left3_5mask) >> 5) | ((temp & right5_3mask) >> 3)) & player;
	temp = (((nOcc & left3_5mask) >> 5) | ((nOcc & right5_3mask) >> 3)) & opponent;
	movers |= (temp >> 4) & player;

	//bicie w tył
	if (playerQueens) {
		temp = (nOcc << 4) & opponent;
		if (temp)
			movers |= (((temp & left3_5mask) << 3) | ((temp & right5_3mask) << 5)) & player;
		temp = (((nOcc & left3_5mask) << 3) | ((nOcc & right5_3mask) << 5)) & opponent;
		movers |= (temp << 4) & player;
	}

	if (state->player() == black)
		movers = helper::reverse(movers);

	return (movers);
}
