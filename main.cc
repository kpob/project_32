#include <ppapi/cpp/module.h>
#include "include/checkers.h"

namespace checkers {


/*
*	MODULE CLASS
*/

class CheckersModule : public pp::Module {
	public:
  		CheckersModule() : pp::Module() {}
		virtual ~CheckersModule() {}
		
		virtual pp::Instance* CreateInstance(PP_Instance instance) {
    		return new CheckersInstance(instance);
  		}
};

}  // namespace checkers

/*
*	FACTORY METHOD
*/

namespace pp {

Module* CreateModule() {
	return new checkers::CheckersModule();
}

}  // namespace pp
