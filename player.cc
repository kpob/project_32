/*
 * player.cc
 *
 *  Created on: 26-10-2012
 *      Author: Krzysztof Pobiarżyn
 */
#include "include/player.h"
#include "include/random.h"
#include "include/minmax.h"

Player::Player(AI *algorithm, int color, std::string language) :
	algorithm(algorithm),  color(color),  language(language){
}
Player::~Player(){

}

void Player::nextMove(){
	algorithm->pickState();
}




