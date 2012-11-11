/*
 * moveTests.h
 *
 *  Created on: 15-10-2012
 *      Author: qwerty
 */

#ifndef MOVETESTS_H_
#define MOVETESTS_H_
#include <iostream>
#include "board.h"

//namespace moveTest{

//logic::Board *b;
//int tests = 0;
//int passed = 0;
//
//void initTests(){
//	b = new logic::Board();
//}
//
//void assertSingleMove(int from, int to, bool expectedResult){
//	tests++;
//	int32_t res = b->move(from, to);
//	bool result;
//	if(expectedResult == true){
//		result = (res > 0 ? (true) : (false));
//	}else
//		result = (res > 0 ? (false) : (true));
//	if(result){
//		passed++;
//		std::cout << "passed" << std::endl;
//	}else{
//		std::cout << "failed" << std::endl;
//	}
//	b = new logic::Board();
//}
//
//void assertSequenceMove(int moves[], int movesLength, bool expectedResult){
//	b = new logic::Board();
//	tests++;
//	int32_t res;
//	if(sizeof(moves) % 2 != 0){
//		std::cout << "failed" << std::endl;
//	}else{
//		for(int i=0; i<movesLength; i+=2){
//			res = b->move(moves[i], moves[i+1]);
//
//			if(expectedResult == false && res == 0){
//				passed++;
//				std::cout << "passed" << std::endl;
//				return;
//			}else if(expectedResult == true && res == 0){
//				std::cout << "failed" << std::endl;
//				return;
//			}
//		}
//		if(expectedResult == false && res > 0)
//			std::cout << "failed" << std::endl;
//		else{
//			std::cout << "passed" << std::endl;
//			passed++;
//		}
//		return;
//	}
//}
//
//
//void runTest(){
//	initTests();
//	std::cout << "start" << std::endl;
//	//white
//	assertSingleMove(10,14, true);
//	assertSingleMove(10,1, false);
//	assertSingleMove(-1,4, false);
//	assertSingleMove(0, 4, false);
//	assertSingleMove(8,17, false);
//	assertSingleMove(11,14, true);
//
//	//empty
//	assertSingleMove(14,15, false);
//	assertSingleMove(14,18, false);
//	assertSingleMove(13,18, false);
//	//black
//	assertSingleMove(20,16, true);
//	assertSingleMove(20,17, true);
//	assertSingleMove(23,19, true);
//
//	assertSingleMove(66,19, false);
//	assertSingleMove(31,27, false);
//	assertSingleMove(27,22, false);
//	assertSingleMove(27,23, false);
////
//	int moves[] = {22, 18, 27, 22};
//	assertSequenceMove(moves,sizeof(moves)/sizeof(int), true);
//
//	int moves2[] = {27, 22, 22, 18};
//	assertSequenceMove(moves2,sizeof(moves2)/sizeof(int), false);
//
//	int moves3[] = {8, 12, 12, 17};
//	assertSequenceMove(moves3,sizeof(moves3)/sizeof(int), true);
//
//	int moves4[] = {8, 12, 12, 17, 17, 21};
//	assertSequenceMove(moves4,sizeof(moves4)/sizeof(int), false);
////
//	int moves5[] = {8, 12, 9, 13, 12, 16};
//	assertSequenceMove(moves5,sizeof(moves5)/sizeof(int) ,true);
//
//	std::cout << "passed " << passed << "/" << tests << std::endl;
//	std::cout << "END" << std::endl;
//}
//
//}



#endif /* MOVETESTS_H_ */
