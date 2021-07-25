#ifndef __COFFEE_MACHINE_SERVICE_TASK__
#define __COFFEE_MACHINE_SERVICE_TASK__

#include "Task.h"
#include "SharedSpace.h"
#include "MsgService.h"

class CoffeeMachineServiceTask: public Task {

public:

  CoffeeMachineServiceTask(SharedSpace* sp, MsgService* msgService);
  void init(int period);  
  void tick();

private:
  MsgService* msgService;
  SharedSpace* sp;
};

#endif
