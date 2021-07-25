#include "GetZuccheroTask.h"
#include "Potenziometro.h"
#define FIX_SUGAR 200

GetZuccheroTask::GetZuccheroTask(int pinNr, SharedSpace* sp): pin(pinNr) {
    this->sp = sp;
}

void GetZuccheroTask::init(int period) {
     Task::init(period);
     pot = new Potenziometro(pin);
     state = WAITING;
}

void GetZuccheroTask::tick(){
    switch (state) {
      
		case WAITING:
			if (sp->isAcceptCommands() && !sp->isPres()) {
				state = GET_SUGAR;
			}
			break;
      
		case GET_SUGAR:
				sp->setZucchero(pot->getValue()/FIX_SUGAR);
				state = WAITING;
			break;
      
		}
}
