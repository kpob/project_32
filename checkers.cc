#include <cstdio>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
	}else if (message == newGameMethodId) {
		Game::getInstance().newGame();
		PostMessage(pp::Var("start"));		
		PostMessage(pp::Var("black"));
		PostMessage(pp::Var("\n"));
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
