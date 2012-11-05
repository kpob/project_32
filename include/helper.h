/*
 * helper.h
 *
 *  Created on: 24-10-2012
 *      Author: qwerty
 */

#ifndef HELPER_H_
#define HELPER_H_

#include "types.h"
#include "game_state.h"
#include <string>
#include <vector>

namespace helper{

BITBOARD shift(int i);
std::string printBoard(GameState *state);
BITBOARD reverse(BITBOARD bitboard);
std::vector<std::string> args2vector(std::string);

void bitboard2stream(std::stringstream &stream, const uint32_t bitboard);

std::string message2stringArgs(const std::string message);
void logmsg(const char* pMsg);
void errormsg(const char* pMsg);
}


#endif /* HELPER_H_ */
