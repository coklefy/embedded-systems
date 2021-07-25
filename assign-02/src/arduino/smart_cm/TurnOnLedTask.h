#ifndef __TURN_ON_LED_TASK__
#define __TURN_ON_LED_TASK__

#include "ConcurrentTask.h"
#include "Led.h"

class TurnOnLedTask: public ConcurrentTask {
  
		public:
			TurnOnLedTask(int pin1, int pin2, int pin3, SharedSpace* sp);
			void init(int period);
			void tick();
		
		private:
			int pin1, pin2, pin3, t; // t = contatore tempo trascorso
			Light* L1;
			Light* L2;
			Light* L3;
			
		/*
		 *  STATES INFO:
		 *  NO_START: 		coffe not started
         *  TURN_ON_FIRST:  coffe started, turn on FIRST LED
         *  TURN_ON_SECOND: turn on SECOND LED
         *  TURN_ON_THIRD:  turn on THIRD LED
		 *  TURN_OFF_ALL:   turn off ALL LEDS
         */
     enum { NO_START, TURN_ON_FIRST, TURN_ON_SECOND, TURN_ON_THIRD, TURN_OFF_ALL} state;

};

#endif
