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

namespace helper{

BITBOARD shift(int i);
std::string printBoard(GameState *state);
BITBOARD reverse(BITBOARD bitboard);
}
#endif /* HELPER_H_ */
