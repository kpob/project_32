/*
 * helper.cc
 *
 *  Created on: 24-10-2012
 *      Author: Krzysztof Pobiarżyn
 */

#include "include/helper.h"
#include "include/types.h"
#include "include/game_state.h"
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

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

std::vector<std::string> args2vector(std::string player){
	using namespace std;	
	string arg;
	vector<string> tokens;
	size_t sep_pos = player.find_first_of(",");
	while(sep_pos != string::npos){
		arg = player.substr(0, sep_pos);
		tokens.push_back(arg);
		player = player.substr(sep_pos+1, string::npos);
		sep_pos = player.find_first_of(",");
	}
	tokens.push_back(player);
	return tokens;
}

void bitboard2stream(std::stringstream &stream, const uint32_t bitboard){
	for(int i=0; i<32; i++)
		if(bitboard & (1<<i))
			stream << i << ",";
}

std::string message2stringArgs(const std::string message){
	size_t sepPos = message.find_first_of(":");
	return (message.substr(sepPos + 1));
}


}

