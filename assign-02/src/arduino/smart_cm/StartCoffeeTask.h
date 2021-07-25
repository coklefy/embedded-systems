#ifndef _START_COFFEE_TASK_
#define _START_COFFEE_TASK_
#include "ButtonImpl.h"
#include "ConcurrentTask.h"

class StartCoffeeTask: public ConcurrentTask{
	
	public:
		StartCoffeeTask(int pinT1, SharedSpace* sp);
		void init(int period);
		void tick();
		
	private:
		int pinT1, CurrentCoffee;
		Button* T1;
		
	/*
        STATES INFO:

        START__COFFEE: T1 pressed, start making coffee
        WAITING: waiting for T1 to start making coffee

    */
	enum {START_COFFEE, WAITING } state;
	
};

#endif
