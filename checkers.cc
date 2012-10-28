#include <cstdio>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>

#include "ppapi/cpp/input_event.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

#include "include/checkers.h"
#include "include/move_gen.h"
#include "include/helper.h"

namespace checkers { 

const char* const printBoardMethodId = "printBoard";
const char* const newGameMethodId = "newGame";



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
	if (!var_message.is_string()) {
		return;
	}
	
	std::string message = var_message.AsString();
  
	if (message == printBoardMethodId){
		PostMessage(pp::Var(helper::printBoard(Game::getInstance().state())));	
	}else if (message.find("setPlayers") == 0) {
		size_t sep_pos = message.find_first_of(",");
		std::string string_arg = message.substr(sep_pos + 1);
		size_t white_pos = string_arg.find_first_of("white");
		std::string player1 = string_arg.substr(0, white_pos -1);
		std::string player2 = string_arg.substr(white_pos, std::string::npos);

		Game::getInstance().setPlayers(player1, player2);
		PostMessage(pp::Var("gracz 1"));
		PostMessage(pp::Var("\n"));
		PostMessage(pp::Var(Game::getInstance().p1()->lang()));
		PostMessage(pp::Var("\n"));		
		PostMessage(pp::Var("gracz 2"));
		PostMessage(pp::Var("\n"));
		PostMessage(pp::Var(Game::getInstance().p2()->lang()));
		PostMessage(var_message);
//		Game::getInstance().newGame();
	}else{
		PostMessage(pp::Var("dupa"));
	}
}


void CheckersInstance::tooglePlayer(){
//	if(Game::getInstance().player() == black)
//		PostMessage(pp::Var("black"));
//	else
//		PostMessage(pp::Var("white"));
	
	PostMessage(pp::Var("\n"));
//	Game::getInstance().tooglePalyer();
}

}
