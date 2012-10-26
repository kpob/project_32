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
	//	virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);
		virtual void HandleMessage(const pp::Var& var_message);

	private:
		CheckersInstance(const CheckersInstance&);  // Disallow copy
		void resetBoard();
		void setPawns();
		void tooglePlayer();
};

}
