#include "CoffeeMachineServiceTask.h"
#include "MsgService.h"
#include "Config.h"

CoffeeMachineServiceTask::CoffeeMachineServiceTask(SharedSpace* sp, MsgService* msgService){
  this->sp = sp;
  this->msgService = msgService;
}
  
void CoffeeMachineServiceTask::init(int period){
  Task::init(period);
}
  
void CoffeeMachineServiceTask::tick(){
	
	if(sp->isMov() && !sp->isAcceptCommands()){
		msgService->sendMsg("display:Welcome");
	}
	
	msgService->sendMsg("req_zucchero:"+ String(sp->getZucchero()));
	
	if(sp->getL1()->isSwitchedOn() && !sp->isCoffeeFinished()){
		msgService->sendMsg("display:Making coffee");	
	} else if( sp->isCoffeeFinished()){
		msgService->sendMsg("display:Coffee finished");		
	}

	
	
	if (msgService->isMsgAvailable()) {
		
		Msg* msg = msgService->receiveMsg(); 

		if (msg->getContent() == "req_coffeeQ" && sp->thereIsCoffee()){
			  msgService->sendMsg("req_coffeeQ:"+String(sp->getTotCoffee()));
		}else if (msg->getContent() == "req_coffeeQ" && !sp->thereIsCoffee()) {
			  msgService->sendMsg("no_coffee");
		} else if (msg->getContent() == "refill_coffee" && !sp->thereIsCoffee()){
				sp->setTotCoffee(MAX_COFFEE);
		}else {
			  msgService->sendMsg("not understood.");  
		}
	
    delete msg;
  }  
}
