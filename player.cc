/*
 * player.cc
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */
#include "include/player.h"
#include "include/random.h"

Player::Player(AI *algoritihm, int color, std::string language) :
	algoritihm(algoritihm),  color(color),  language(language){
}
Player::~Player(){

}

void Player::nextMove(){
	Random* random = dynamic_cast<Random*>(algoritihm);
	if(random != 0) {
	   random->pickState();
	}
}




