///*
// * board.cc
// *
// *  Created on: 13-10-2012
// *      Author: Krzysztof Pobiarżyn
// */
//
//#include "include/board.h"
//#include "include/helper.h"
//#include "include/types.h"
//
//#include <iostream>
//#include <sstream>
//
//namespace logic {
//
//Board::Board(){}
//
//
///*
// *  ______________________________________________________________
// *	Piony z rzędów nieparzystych ruszjąc się w góra-prawo "dodają"
// *	do swojej pozycji 4, z kolei z rzędów parzystych - 5.
// *	Analogiczna sytuacja zachodzi przy ruchach w pozostałe kierunki.
// *	Niektóre ruchy są niedozwolone, na przykład z pozycji nr 7
// *	niemożliwym jest ruch góra-prawo stąd maski uzględniać tego
// *	typu przypadki.
// *  ______________________________________________________________
// *  ---------------------------------
// *  |	|28	|	|29	|	|30	|	|31	|		row: 8
// *  ---------------------------------
// *  |24	|	|25	|	|26	|	|27	|	|		row: 7
// *  ---------------------------------
// *  |	|20	|	|21	|	|22	|	|23	|		row: 6
// *  ---------------------------------
// *  |16	|	|17	|	|18	|	|19	|	|		row: 5
// *  ---------------------------------
// *  |	|12	|	|13	|	|14	|	|15	|		row: 4
// *  ---------------------------------
// *  |8	|	|9	|	|10	|	|11	|	|		row: 3
// *  ---------------------------------
// *  |	|4	|	|5	|	|6	|	|7	|		row: 2
// *  ---------------------------------
// *  |0	|	|1	|	|2	|	|3	|	|		row: 1
// *  ---------------------------------
// *
// */
//
///*
// *  Poniższe fukcje zwracają nowe pozycje po ruchach we wszystkich kierunkach
// */
//
//BITBOARD Board::upLeft(BITBOARD position) {
//	return (((position & left3_5mask) << 3) | ((position & left4mask) << 4));
//}
//
//BITBOARD Board::upRight(BITBOARD position) {
//	return (((position & right4mask) << 4) | ((position & right5_3mask) << 5));
//}
//
//BITBOARD Board::downLeft(BITBOARD position) {
//	return (((position & left3_5mask) >> 5) | ((position & left4mask) >> 4));
//}
//
//BITBOARD Board::downRight(BITBOARD position) {
//	return (((position & right4mask) >> 4) | ((position & right5_3mask) >> 3));
//}
//
//GameState *Board::move(const int from, const int to, const int color, bool isReal) {
//	BITBOARD position = helper::shift(from);
//	BITBOARD moveResult = 0;
//
//	BITBOARD whites = currentState->whites();
//	BITBOARD blacks = currentState->blacks();
//	BITBOARD queens = currentState->queens();
//
//	GameState *newState = 0;
//
//	int diff = to - from;
//
//	if (isWhitePawn(position)) {
//		if (((left3_5mask & position) && diff == 3) || ((left4mask & position) && diff == 4))
//			moveResult = upLeft(position);
//		else if (((right4mask & position) && diff == 4) || ((right5_3mask & position) && diff == 5))
//			moveResult = upRight(position);
//	}else if (isBlackPawn(position)) {
//		if (((left3_5mask & position) && diff == -5) || ((left4mask & position) && diff == -4))
//			moveResult = downLeft(position);
//		else if (((right4mask & position) && diff == -4) || ((right5_3mask & position) && diff == -3))
//			moveResult = downRight(position);
//	}else if(isQueen(position)){
//		if (((left3_5mask & position) && diff == 3) || ((left4mask & position) && diff == 4))
//			moveResult = upLeft(position);
//		else if (((right4mask & position) && diff == 4) || ((right5_3mask & position) && diff == 5))
//			moveResult = upRight(position);
//		else if (((left3_5mask & position) && diff == -5) || ((left4mask & position) && diff == -4))
//			moveResult = downLeft(position);
//		else if (((right4mask & position) && diff == -4) || ((right5_3mask & position) && diff == -3))
//			moveResult = downRight(position);
//	}
//
//	if(isEmpty(moveResult) && moveResult){
//		if(color == cWhite)
//			whites ^= position | moveResult;
//		else
//			blacks ^= position | moveResult;
//		if (((moveResult & blackLastLine) || (moveResult & whiteLastLine)) && !isQueen(position))
//			queens |= moveResult;
//		if(position & queens)
//			queens ^= position | moveResult;
//
//		newState = new GameState(whites, blacks, queens);
//	}else
//		moveResult = 0;
//
//	if(isReal && moveResult)
//		currentState = newState;
//
//	return (newState);
//}
//
//bool Board::isBlackPawn(BITBOARD position) {
//	return (currentState->blacks() & ~currentState->queens() & position);
//}
//
//bool Board::isWhitePawn(BITBOARD position) {
//	return (currentState->whites() & ~currentState->queens() & position);
//}
//
//bool Board::isQueen(BITBOARD position){
//	return (currentState->queens() & position);
//}
//
//
//GameState *Board::jump(const int fieldNumber, const int to, const int color, bool isReal) {
//	const BITBOARD position = helper::shift(fieldNumber);
//
//	int direction = to - fieldNumber;
//	GameState *newState = 0;
//	switch (direction) {
//	case UP_LEFT:
//		newState = jumpUpLeft(position, color); break;
//	case DOWN_LEFT:
//		newState = jumpDownLeft(position, color); break;
//	case UP_RIGHT:
//		newState = jumpUpRight(position, color); break;
//	case DOWN_RIGHT:
//		newState = jumpDownRight(position, color); break;
//	default:
//		return (0);
//	}
//	if(isReal && newState!=0)
//		currentState = newState;
//	return (newState);
//}
//
///*
// *  Poniższe fukcje zwracają nowe pozycje po atakach we wszystkich kierunkach
// */
//
//GameState *Board::jumpUpLeft(BITBOARD position, int color) {
//	if (color == cWhite && isLegalWhiteJump(position, UP_LEFT))
//		return (whiteJump(position, UP_LEFT));
//	else if (color == cBlack && isLegalBlackJump(position, UP_LEFT))
//		return (blackJump(position, UP_LEFT));
//	return (0);
//}
//
//GameState *Board::jumpDownLeft(BITBOARD position, int color) {
//	if (color == cWhite && isLegalWhiteJump(position, DOWN_LEFT))
//		return (whiteJump(position, DOWN_LEFT));
//	else if (color == cBlack && isLegalBlackJump(position, DOWN_LEFT)){
//		return (blackJump(position, DOWN_LEFT));
//	}
//	return (0);
//}
//
//GameState *Board::jumpUpRight(BITBOARD position, int color) {
//	if (color == cWhite && isLegalWhiteJump(position, UP_RIGHT))
//		return (whiteJump(position, UP_RIGHT));
//	else if (color == cBlack && isLegalBlackJump(position, UP_RIGHT))
//		return (blackJump(position, UP_RIGHT));
//	return (0);
//}
//
//GameState *Board::jumpDownRight(BITBOARD position, int color) {
//	if (color == cWhite && isLegalWhiteJump(position, DOWN_RIGHT))
//		return (whiteJump(position, DOWN_RIGHT));
//	else if (color == cBlack && isLegalBlackJump(position, DOWN_RIGHT))
//		return (blackJump(position, DOWN_RIGHT));
//	return (0);
//}
//
////----------------------------------------------------------------------
//
//bool Board::isLegalBlackJump(BITBOARD position, int direction) {
//	BITBOARD whites = currentState->whites();
//	switch (direction) {
//	case UP_LEFT:
//		return ((upLeft(position) & whites) && isEmpty((position << 7)) && isQueen(position));
//	case UP_RIGHT:
//		return ((upRight(position) & whites) && isEmpty((position << 9)) && isQueen(position));
//	case DOWN_LEFT:
//		return ((downLeft(position) & whites) && isEmpty((position >> 9)));
//	case DOWN_RIGHT:
//		return ((downRight(position) & whites) && isEmpty((position >> 7)));
//	default:
//		return (false);
//	}
//}
//
//GameState *Board::blackJump(BITBOARD position, int direction) {
//	BITBOARD targetPosition = 0;
//	BITBOARD move = 0;
//
//	BITBOARD whites = currentState->whites();
//	BITBOARD blacks = currentState->blacks();
//	BITBOARD queens = currentState->queens();
//	switch (direction) {
//	case UP_LEFT:
//		targetPosition = position << 7;
//		move = upLeft(position);
//		break;
//	case UP_RIGHT:
//		targetPosition = position << 9;
//		move = upRight(position);
//		break;
//	case DOWN_LEFT:
//		targetPosition = position >> 9;
//		move = downLeft(position);
//		break;
//	case DOWN_RIGHT:
//		targetPosition = position >> 7;
//		move = downRight(position);
//		break;
//	}
//	whites ^= move;
//	blacks ^= position; 		//zdejmij czarny ze starej pozycji
//	blacks ^= targetPosition; 	//postaw czarny
//	if (((targetPosition & blackLastLine)) && !isQueen(position))
//		queens |= targetPosition;
//	if(position & queens)
//		queens ^= targetPosition | position;
//	return (new GameState(whites, blacks, queens));
//}
//
//bool Board::isLegalWhiteJump(BITBOARD position, int direction){
//	BITBOARD blacks = currentState->blacks();
//	switch (direction) {
//	case UP_LEFT:
//		return ((upLeft(position) & blacks) && isEmpty((position << 7)));
//	case UP_RIGHT:
//		return ((upRight(position) & blacks) && isEmpty((position << 9)));
//	case DOWN_LEFT:
//		return ((downLeft(position) & blacks) && isEmpty((position >> 9)) && isQueen(position));
//	case DOWN_RIGHT:
//		return ((downRight(position) & blacks) && isEmpty((position >> 7)) && isQueen(position));
//	default:
//		return (false);
//	}
//}
//
//GameState *Board::whiteJump(BITBOARD position, int direction) {
//	BITBOARD targetPosition = 0;
//	BITBOARD move = 0;
//
//	BITBOARD whites = currentState->whites();
//	BITBOARD blacks = currentState->blacks();
//	BITBOARD queens = currentState->queens();
//
//	switch (direction) {
//	case UP_LEFT:
//		targetPosition = position << 7;
//		move = upLeft(position);
//		break;
//	case UP_RIGHT:
//		targetPosition = position << 9;
//		move = upRight(position);
//		break;
//	case DOWN_LEFT:
//		targetPosition = position >> 9;
//		move = downLeft(position);
//		break;
//	case DOWN_RIGHT:
//		targetPosition = position >> 7;
//		move = downRight(position);
//		break;
//	}
//
//	blacks ^= move;
//	whites ^= position; 		//zdejmij czarny ze starej pozycji
//	whites ^= targetPosition;
//	//postaw czarny
//	if (((targetPosition & whiteLastLine)) && !isQueen(position))
//			queens |= targetPosition;
//	if(position & queens)
//		queens ^= targetPosition | position;
//	return (new GameState(whites, blacks, queens));
//}
//
//BITBOARD Board::reverse(BITBOARD bitboard) {
//	BITBOARD result = 0;
//	for(int i = 0; i<32; i++)
//		if((bitboard & (1 << (31-i))))
//			result += (1 << i);
//	return (result);
//}
//
//BITBOARD Board::getMovers(const int color, GameState *state) {
//	BITBOARD whites = state->whites();
//	BITBOARD blacks = state->blacks();
//	BITBOARD queens = state->queens();
//
//	BITBOARD player = 0;
//	BITBOARD opponent = 0;
//	BITBOARD playerQueens = 0;
//
//	if(color == cWhite){
//		player = whites;
//		opponent = blacks;
//		playerQueens = player & queens;
//	}else{
//		opponent = reverse(whites);
//		player = reverse(blacks);
//		playerQueens = player & reverse(queens);
//	}
//
//	const BITBOARD nOcc = ~(opponent | player);
//
//	BITBOARD movers = (nOcc >> 4) & player;
//	movers |= ((nOcc & left3_5mask) >> 5) & player;
//	movers |= ((nOcc & right5_3mask) >> 3) & player;
//
//	if (playerQueens) {
//		movers |= (nOcc << 4) & playerQueens;
//		movers |= ((nOcc & left3_5mask) << 5) & playerQueens;
//		movers |= ((nOcc & right5_3mask) << 3) & playerQueens;
//	}
//
//	if(color == cBlack)
//		movers = reverse(movers);
//
//	return (movers);
//}
//
//BITBOARD Board::getJumpers(const int color, GameState *state) {
//	BITBOARD whites = state->whites();
//	BITBOARD blacks = state->blacks();
//	BITBOARD queens = state->queens();
//
//	BITBOARD player = 0;
//	BITBOARD opponent = 0;
//	BITBOARD playerQueens = 0;
//
//	if(color == cWhite){
//		player = whites;
//		opponent = blacks;
//		playerQueens = player & queens;
//	}else{
//		opponent = reverse(whites);
//		player = reverse(blacks);
//		playerQueens = player & reverse(queens);
//	}
//
//	const BITBOARD nOcc = ~(opponent | player);
//	BITBOARD movers = 0;
//
//	//bicie w przód
//	//z każdego rzędu możliwy jest ruch o 4 pola więc najpierw porownujemy
//	//wolne pola przesuniete o 4 z pionkami przeciwnika, wtedy wiemy że nasz
//	//pionek ruszy się o 3 lub 5 pól w zależności od kierunku
//	//potem sprawdzamy analogiczny warunek - wolne pole znajduje się 3 lub 5 pól
//	//za przeciwnikiem, a przeciwnik o 4 pola od naszego piona
//	//bicie damek (czyli bicie do tyłu odbywa się analogicznie)
//
//	BITBOARD temp = (nOcc >> 4)  & opponent;
//	if (temp)
//		movers |= (((temp & left3_5mask) >> 5) | ((temp & right5_3mask) >> 3)) & player;
//	temp = (((nOcc & left3_5mask) >> 5) | ((nOcc & right5_3mask) >> 3)) & opponent;
//	movers |= (temp >> 4) & player;
//
//	//bicie w tył
//	if(playerQueens){
//		temp = (nOcc << 4) & opponent;
//		if(temp)
//			movers |= (((temp & left3_5mask) << 3) | ((temp & right5_3mask) << 5)) & player;
//		temp = (((nOcc & left3_5mask) << 3) | ((nOcc & right5_3mask) << 5)) & opponent;
//		movers |= (temp << 4) & player;
//	}
//
//	if(color == cBlack)
//		movers = reverse(movers);
//
//	return (movers);
//}
//
//} //namespace
