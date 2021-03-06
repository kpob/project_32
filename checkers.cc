#include <cstdio>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>

#include "ppapi/cpp/input_event.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

#include "includes/checkers.h"
#include "includes/move_gen.h"
#include "includes/helper.h"

namespace checkers { 

const char* const printBoardMethodId = "printBoard";
const char* const newGameMethodId = "newGame";
const char* const setPlayersString = "setPlayers";
const char* const moveMethodId = "move:";

const char* const moveJsMethodId = "jsMove";

const char* const methodSeparator = ":";
const char* const argsSeparator = ",";


/*
*	INSTANCE CLASS IMPLEMENTATION
*/

CheckersInstance::CheckersInstance(PP_Instance instance) : 	pp::Instance(instance) {
	RequestInputEvents(PP_INPUTEVENT_CLASS_MOUSE | PP_INPUTEVENT_CLASS_WHEEL);
}

CheckersInstance::~CheckersInstance(){
}


/*
*	HANDLING MESSAGES FROM JAVASCRIPT
*/

void CheckersInstance::HandleMessage(const pp::Var& var_message) {
	if (!var_message.is_string())
		return;
	std::string message = var_message.AsString();
  	helper::logmsg("--handle--");
	if (message == printBoardMethodId)
		handlePrintBoard();
	else if (message.find(setPlayersString) == 0) 
		handleSetPlayers(message);
	else if(message == newGameMethodId)
		handleNewGame(message);
	else if(message.find(moveMethodId) == 0)
		handleMove(message);
	else if(message.find("naclMove") == 0)
		makeNaclMove();
}

void CheckersInstance::handlePrintBoard(){
	PostMessage(pp::Var(helper::printBoard(Game::getInstance().state())));	
}

void CheckersInstance::handleSetPlayers(const std::string& message){
	//format otrzymanej wiadomosci [metoda]:[kolor],[algorytm],[js/nacl],[kolor],[algorytm],[js/nacl]
	size_t sepPos = message.find_first_of(methodSeparator);
	std::string stringArgs = message.substr(sepPos + 1);
	
	size_t whitePos = stringArgs.find("white");
	
	std::string player1 = stringArgs.substr(0, whitePos-1);
	std::string player2 = stringArgs.substr(whitePos, std::string::npos);
	Game::getInstance().setPlayers(player1, player2);
	std::vector<std::string> pWhiteArgs = helper::args2vector(player2);
	PostMessage(pp::Var(message)); // javascript musi rowniez ustawic playerow
}

void CheckersInstance::handleNewGame(const std::string& message){
	if(Game::getInstance().arePlayersSet()){
		Game::getInstance().newGame();
		PostMessage(pp::Var(message));
		if(Game::getInstance().currentPlayer()->lang() == "js")
			sendMovePrompt();
		else
			makeNaclMove();
	}else{
		PostMessage(pp::Var("error:unsettedPlayers"));
	}
	
}

void CheckersInstance::handleMove(const std::string& message){
	//format otrzymanej wiadomosci [metoda]:[z],[do]
	std::string stringArgs = helper::message2stringArgs(message);
	std::vector<std::string> argsVector = helper::args2vector(stringArgs);
		
	makeMovesFromVector(argsVector);
}

void CheckersInstance::makeMovesFromVector(const std::vector<std::string> movesVector){
	MoveGen &gen = MoveGen::getInstance();
	for(unsigned i=0; i<movesVector.size(); i+=2){
		int from = atoi(movesVector.at(i).c_str());
		int to = atoi(movesVector.at(i+1).c_str());
		gen.nextMove(from, to);
	}
	Game::getInstance().state()->tooglePlayer();
	PostMessage(pp::Var("zmiana"));
	if(!(gen.getJumpers(Game::getInstance().state()) || gen.getMovers(Game::getInstance().state())))	
		PostMessage(pp::Var("endGame"));
}

void CheckersInstance::makeNaclMove(){
	srand(time(NULL));
	clock_t cl;
	cl = clock();
	pthread_create(&computeMoveThread, NULL, computeMove, this);
	(void) pthread_join(computeMoveThread, NULL);
	cl = clock() - cl;
	
	std::stringstream log;
	std::cout << "log: czas " << ((float) cl) / CLOCKS_PER_SEC;
	log << "czas " << ((float) cl) / CLOCKS_PER_SEC;
	PostMessage(pp::Var(log.str()));
	
	PostMessage(pp::Var(naclMoveResult));
	
	MoveGen &gen  = MoveGen::getInstance();
	if(gen.getJumpers(Game::getInstance().state()) || gen.getMovers(Game::getInstance().state()))
		sendMovePrompt();
	else
		PostMessage(pp::Var("endGame"));
	
}

void* CheckersInstance::computeMove(void* param) {
	std::stringstream ss;

	ss << moveMethodId;	
	CheckersInstance* ci = static_cast<CheckersInstance*>(param);
	Game::getInstance().currentPlayer()->nextMove();
	uint32_t move = Game::getInstance().lastMoveBitboard();
	for(int i=0; i<32;i++)
		if((move & Game::getInstance().prevState()->whites()) & (1<<i))
			ss << i << ",";
	for(int i=0; i<32;i++)
		if((move & Game::getInstance().state()->whites()) & (1<<i))
			ss << i << ",";

	Game::getInstance().state()->tooglePlayer();
	uint32_t opponentPawnsDiff = Game::getInstance().opponentPawnsDiffBitboard();
	helper::bitboard2stream(ss, opponentPawnsDiff);
	size_t lastComma = ss.str().find_last_of(argsSeparator);
	
	ci->naclMoveResult = ss.str().substr(0, lastComma);

	return 0;
}

void CheckersInstance::sendMovePrompt(){
	PostMessage(pp::Var(moveJsMethodId));
}

}
