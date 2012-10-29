#include <string>
#include <vector>
#include <time.h>

#include "ppapi/cpp/instance.h"

#include "game.h"

namespace checkers{

class CheckersInstance : public pp::Instance {
	
	public:
  		explicit CheckersInstance(PP_Instance instance);
  		virtual ~CheckersInstance();
		virtual void HandleMessage(const pp::Var& var_message);

	private:
		CheckersInstance(const CheckersInstance&);  // Disallow copy

		void makeNaclMove();

		void handlePrintBoard();
		void handleMove(const std::string& message);
		void handleNewGame(const std::string& message);
		void handleSetPlayers(const std::string& message);

		void makeMovesFromVector(const std::vector<std::string> movesVector);

		void sendMovePrompt();
};

}
