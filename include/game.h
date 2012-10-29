/*
 * game.h
 *
 *  Created on: 19-10-2012
 *      Author: qwerty
 */

#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "player.h"

class Game {
private:
	Game();
	Game(const Game &);

	Game& operator=(const Game&);
	
	GameState *currentState;
	GameState *previousState;

	Player *pWhite;
	Player *pBlack;

	bool isSet;
public:

	static Game& getInstance() {
		static Game instance;
		return (instance);
	}

	GameState *state() {
		return (currentState);
	}

	GameState *prevState() {
		return (previousState);
	}

	Player *p1(){
		return pWhite;
	}

	Player *p2(){
		return pBlack;
	}

	Player *currentPlayer();

	void newGame();

	void setPlayers(std::string player1, std::string player2);

	bool isStarted();
	bool arePlayersSet();

	BITBOARD lastMoveBitboard();
	BITBOARD opponentPawnsDiffBitboard();
	void updateState(GameState *newState);

};

#endif /* GAME_H_ */
