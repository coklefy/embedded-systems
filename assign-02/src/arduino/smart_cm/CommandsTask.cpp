#include "CommandsTask.h"
#include "Arduino.h"


#define DIST2 0.1
#define DT3 3000
#define DT4 5000

CommandsTask::CommandsTask(SharedSpace* sp) {
	this->sp = sp;
}

void CommandsTask::init(int period) {
	Task::init(period);
	state = BUTTON_NOT_PRESSED;
}

void CommandsTask::tick(){
	 
	 float dist;
	 
	 switch(state) {
		 
	     case BUTTON_NOT_PRESSED:						
				if( sp->isPres()){
					state = BP_START_COFFEE;					
				}
				break;
				
	     case BP_START_COFFEE:
				t = DT3/myPeriod;
				sp->setTurnOnLeds(true);
				state = COFFEE_FINISHED;
				break;	
				
	     case WAIT_TO_TAKE_COFFEE:
				if(sp->isCoffeeFinished()){
					t = DT4/myPeriod;
					state = COFFEE_TAKEN;
				}				
				break;
				
	     case COFFEE_TAKEN:				
				dist = 	dist = sp->getProxy()->getDistance();			
				if( t>0 && dist > DIST2){
					t--;
				}else if( t>0 && dist <= DIST2){
					sp->setTakeCoffee(true);
					//sp->setCoffeeFinished(true);
					state = BUTTON_NOT_PRESSED;					
					}
					else if ( t <= 0 && sp->isTakeCoffee() == false){
						sp->setTakeCoffee(false);
						state = BUTTON_NOT_PRESSED;					
					}			
				break;
		 
		 case COFFEE_FINISHED: 
				if(t>0){
					t--;
				}else if( t<= 0){
					sp->setTurnOnLeds(false);
					sp->setCoffeeFinished(true);
					state = WAIT_TO_TAKE_COFFEE;
				}				
				break;
		}	 
}
