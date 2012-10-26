/*
 * helper.cc
 *
 *  Created on: 24-10-2012
 *      Author: qwerty
 */

#include "include/helper.h"
#include "include/types.h"
#include "include/game_state.h"
#include <sstream>
#include <string>

namespace helper{

BITBOARD shift(int i) {
	return (1 << i);
}


/*
 *  WYDRUK PLANSZY -  DO DEBUGOWANIA
 */

std::string printBoard(GameState *state) {
	std::stringstream stream;
	for (int i = 63; i >= 0; i--) {
		if (i % 8 == 7 && i != 63) {
			stream << "\n";
		}
		if (i % 2 == 0
				&& ((i >= 0 && i < 8) || (i >= 16 && i < 24)
						|| (i >= 32 && i < 40) || (i >= 48 && i < 56))) {
			if ((helper::shift(i / 2) & state->whites()) != 0) {
				stream << i / 2 << "WH ";
				if (i / 2 < 10)
					stream << " ";
			} else if ((helper::shift(i / 2) & state->blacks()) != 0) {
				stream << i / 2 << "BL ";
				if (i / 2 < 10)
					stream << " ";
			} else {
				stream << "---- ";
			}
		} else if (i % 2 == 1
				&& ((i >= 8 && i < 16) || (i >= 24 && i < 32)
						|| (i >= 40 && i < 48) || (i >= 56 && i < 64))) {
			if ((helper::shift(i / 2) & state->whites()) != 0) {
				stream << i / 2 << "WH ";
				if (i / 2 < 10)
					stream << " ";
			} else if ((helper::shift(i / 2) & state->blacks()) != 0) {
				stream << i / 2 << "BL ";
				if (i / 2 < 10)
					stream << " ";
			} else {
				stream << "---- ";
			}
		} else {
			stream << "---- ";
		}
	}
	stream << "\n";
	return (stream.str());
}

BITBOARD reverse(BITBOARD bitboard) {
	BITBOARD result = 0;
	for(int i = 0; i<32; i++)
		if((bitboard & (1 << (31-i))))
			result += (1 << i);
	return (result);
}

}

