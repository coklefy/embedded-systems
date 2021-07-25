#include "ControlStateTask.h"
#include "Arduino.h"
#include "Config.h"
#include <avr/sleep.h>
#include <avr/power.h>

ControlStateTask::ControlStateTask(SharedSpace* sp){
	this->sp = sp;
}

void ControlStateTask::init(int period){
	Task::init(period);
	state = TAKE_ME_TO_READY;
	nr_Reads = 0;
	flag = 0;
	NrTotReads = 1000 / period; //letture al secondo
}

void ControlStateTask::sleep1(){
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_mode(); 
	interrupts();
	sp->setMov(true);
	sleep_disable();
}


void ControlStateTask::tick(){
	float dist;

	switch(state){	
		
		case TAKE_ME_TO_READY:         
			if(sp->isAcceptCommands() && sp->isTakeCoffee()== false ){
				sp->setAcceptCommands(false);
				state = READY;
			} else if(sp->isAcceptCommands() && sp->isTakeCoffee()== true) {
				sp->setAcceptCommands(false);
				state = STANDBY;
			}
			else {
				state = STANDBY;
			}
			break;
			
		case STANDBY:
			if(sp->isMov() == false) 				// stay in standby if there is not movement
			{
				sleep1();
			}else if(sp->isMov() == true){
				state = ON;							// Movement verified			
			}	
			break;
			
		case ON:
			if(!sp->isMov()) {		// Check if there is any movement and change the state											
				t = DT2b/myPeriod;					// 5000milis / 500millis ( periodo dei tick task ) = 10 
				state = CHECK_TIME_1;				
			}else 
				if(sp->isMov()){
					state = FILTER;			
			}		
			break;
			
		case FILTER:
			dist = sp->getProxy()->getDistance();			
		    t = DT1/myPeriod;
			if(nr_Reads < NrTotReads){
				if(dist > DIST1){
					flag --;
				}else if(dist < DIST1){
					flag ++;
				}
				nr_Reads++;
			}
			if(nr_Reads >= NrTotReads && flag <= 0){
				state = STANDBY;
				nr_Reads = 0;
				flag = 0;
			} else if(nr_Reads >= NrTotReads && flag > 0){
				state = CHECK_TIME_2;
			}

			break;
			
		case READY:			
			if(!sp->isMov() ){
				t = DT2a/myPeriod;				
				state = CHECK_TIME_3;
			} else if(sp->isMov() && dist < DIST1){
				if(sp->thereIsCoffee() == false){
					state = MAINTENANCE;
					sp->setAcceptCommands(false);
				}
				sp->setAcceptCommands(true);
				// Entry in Accept Commands STATE
			}
			break;
				
		case CHECK_TIME_1:						// Check if passed DT2b sek and change state to STAND BY
			if(sp->isMov() == true ){
				state = ON;
			}
		
			if(!sp->isMov() && t>0){ 			
				t--;
			} else if ( !sp->isMov() && t <=0 ){
				state = STANDBY;
			}			
			break;
			
		case CHECK_TIME_2:								 // Check if passed DT1 sek and there is movement, change state to READY
			if( !sp->isMov() ){
				t = DT2b/myPeriod;					// 5000milis / 500millis ( periodo dei tick task ) = 10 
				state = CHECK_TIME_1;
			}else if(sp->isMov() && t>0){ 				
				t--;
				} else if (sp->isMov() && t <=0 ){
					state = READY;
					}			
			break;
			
		case CHECK_TIME_3:								 // Check if passed DT2a sek and there is not movement, or dist > DIST1, change state to ON
			if(sp->isMov() == true){
				state = READY;
			}
			if(!sp->isMov() && t>0){ 				
				t--;
			}else if (!sp->isMov() || dist>DIST1 && t <=0 ){
				state = ON;
			}	
			break;
		
		case MAINTENANCE: 
				if(sp->thereIsCoffee()){
					state = STANDBY;
				}
				break;

		default:
			break;
    }
}
