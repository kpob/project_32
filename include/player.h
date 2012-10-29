/*
 * player.h
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "ai.h"

class Player{
private:

	AI *algoritihm;
	int color;
	std::string language;

public:
	Player(AI *algoritihm, int color, std::string language);
	~Player();

	std::string lang(){
		return language;	
	}

	void nextMove();

};


#endif /* PLAYER_H_ */
