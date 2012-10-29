/*
 * types.h
 *
 *  Created on: 19-10-2012
 *      Author: qwerty
 */

#ifndef TYPES_H_
#define TYPES_H_
#include <stdint.h>


typedef uint32_t BITBOARD;

enum directions {
	UP_LEFT = 7, UP_RIGHT = 9, DOWN_LEFT = -9, DOWN_RIGHT= -7
};


enum color {
	cBlack=1, cWhite=2, empty=3
};

enum player {
	 black=1, white=2
};


/*
 *  maski "4" sprawdzają zawsze przesunięcie o 4 bity
 *  maski "5_3 / 3_5" sprawdzają przesunięcie o 3 lub 5 bitów
 *  w zależności czy ruch odbywa się na górę bądź na dół.
 */

const BITBOARD whiteLastLine = 0xf0000000;
const BITBOARD blackLastLine = 0x0000000f;

const BITBOARD left3_5mask = 0x0e0e0e0e;
const BITBOARD left4mask = 0xf0f0f0f0;
const BITBOARD right5_3mask = 0x70707070;
const BITBOARD right4mask = 0x0f0f0f0f;


#endif /* TYPES_H_ */
