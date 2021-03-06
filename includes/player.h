/*
 * player.h
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "ai.h"
#include <string>

class Player{
private:

	AI *algorithm;
	int color;
	std::string language;

public:
	Player(AI *algoritihm, int color, std::string language);
	~Player(){
		delete algorithm;
	}

	std::string lang(){
		return language;	
	}

	void nextMove();

};


#endif /* PLAYER_H_ */
