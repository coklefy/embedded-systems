#include "StartCoffeeTask.h"
#include "Arduino.h"

StartCoffeeTask::StartCoffeeTask(int pinT1, SharedSpace* sp): pinT1(pinT1) {
	this->sp = sp;
}

void StartCoffeeTask::init(int period) {
	Task::init(period);
	T1 = new ButtonImpl(pinT1);
	state = WAITING;
}

void StartCoffeeTask::tick() {
	
	CurrentCoffee = sp->getTotCoffee();
	switch(state) {
		case WAITING:
				if(sp->isAcceptCommands() && T1->isPressed()){
					sp->setPres(true);
					CurrentCoffee--;
					state = START_COFFEE;
				}
			break;
			
		case START_COFFEE:
				sp->setTotCoffee(CurrentCoffee);
				if(sp->isCoffeeFinished()){
					state = WAITING;
				}
			break;
	}
}
