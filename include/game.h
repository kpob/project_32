/*
 * game.h
 *
 *  Created on: 19-10-2012
 *      Author: qwerty
 */

#ifndef GAME_H_
#define GAME_H_

#include "board.h"

class Game {
private:
	Game();
	Game(const Game &);

	Game& operator=(const Game&);

	//logic::Board *board;
	GameState *currentState;


public:

	static Game& getInstance() {
		static Game instance;
		return (instance);
	}

	GameState *state() {
		return (currentState);
	}

	void newGame();
	bool isStarted();
	void updateState(GameState *newState);

};

#endif /* GAME_H_ */
