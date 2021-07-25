#ifndef __COMMANDS_TASK__
#define __COMMANDS_TASK__

#include "ConcurrentTask.h"

class CommandsTask: public ConcurrentTask {
	
	public:
		CommandsTask(SharedSpace* sp);	
		void init(int period);
		void tick();
	
	private:
		int t, CurrentCoffee;
		
		/* BUTTON_NOT_PRESSED: button not pressed, no coffe 
		 * BUTTON_PRESSED:	   button pressed, start making coffe
		 * WAIT_TO_TAKE_COFFE: making coffee, turn ON LEDS
		 * COFFEE_FINISHED:    coffes is ready, u can take it
		 * COFFEE_TAKEN:		   check if user took the coffee
		 */
		 
		 enum { BUTTON_NOT_PRESSED, BP_START_COFFEE, WAIT_TO_TAKE_COFFEE, COFFEE_FINISHED, COFFEE_TAKEN} state;
};

#endif
