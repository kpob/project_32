/*
 * player.cc
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */
#include "includes/player.h"
#include "includes/random.h"
#include "includes/minmax.h"
#include <iostream>

Player::Player(AI *algorithm, int color, std::string language) :
	algorithm(algorithm),  color(color),  language(language){
}
Player::~Player(){

}

void Player::nextMove(){
	std::cout << "W NEXT MOVE\n"; 
	algorithm->pickState();
}




