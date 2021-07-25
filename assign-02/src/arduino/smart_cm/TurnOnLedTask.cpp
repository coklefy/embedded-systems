#include "TurnOnLedTask.h"
#include "Arduino.h"

#define REQUIRED_TIME 1000

TurnOnLedTask::TurnOnLedTask(int pin1Nr, int pin2Nr, int pin3Nr, SharedSpace* sp): pin1(pin1Nr), pin2(pin2Nr), pin3(pin3Nr) {
  this->sp = sp;
}

void TurnOnLedTask::init(int period) {
  Task::init(period);
  L1 = new Led(pin1);
  L1->switchOff();
  
  L2 = new Led(pin2);
  L2->switchOff();
  
  L3 = new Led(pin3);
  L3->switchOff();
  
  state = NO_START;
}

void TurnOnLedTask::tick() {
  
	switch(state) {
   
		case NO_START:
			  if( sp->isTurnOnLeds()){
				  state = TURN_ON_FIRST;
			  }
			  break;
			
		case TURN_ON_FIRST:
			  if(L1->isSwitchedOn() == false){
				  L1->switchOn();
				  t = REQUIRED_TIME / myPeriod;
				  state = TURN_ON_SECOND;
			  }	
			  break;
			
		case TURN_ON_SECOND:
			  if(t>0 && L1->isSwitchedOn()){
				  t--;
			  } else if(t<=0 && L2->isSwitchedOn() == false) {
				      L2->switchOn();
				      t = REQUIRED_TIME / myPeriod;
				      state = TURN_ON_THIRD;
			    }
			  break;

		case TURN_ON_THIRD:
			  if(t>0 && L2->isSwitchedOn()){
				  t--;
			  } else if ( t<=0 && L2->isSwitchedOn()){
				      L3->switchOn();
				      t = REQUIRED_TIME / myPeriod;
				      state = TURN_OFF_ALL;
			    }
			break;
			
		case TURN_OFF_ALL: 
			if(t > 0 && L1->isSwitchedOn() && L2->isSwitchedOn() && L3->isSwitchedOn() ) {
					t--;
			} else if(t<=0){
				L1->switchOff();
				L2->switchOff();
				L3->switchOff();
        state = NO_START;
        sp->setTurnOnLeds(false);
			}
			break;
      
	  }
}
