#include "Scheduler.h"
#include "MotionDetectorTask.h"
#include "ConcurrentTask.h"
#include "ControlStateTask.h"
#include "CommandsTask.h"
#include "TurnOnLedTask.h"
#include "CoffeeMachineServiceTask.h"
#include "GetZuccheroTask.h"
#include "StartCoffeeTask.h"
#include "MsgService.h"
#include "Config.h"
#include "SharedSpace.h"

#include <avr/sleep.h>
Scheduler sched;
SharedSpace* sp;
MsgService* msgService;

void changeStatus(){
	noInterrupts();
	sp->setMov(true);
	interrupts();
}


void setup() {
  
    msgService = new MsgService();
    sp = new SharedSpace(L1_PIN, L2_PIN, L3_PIN, ECHO_PIN, TRIG_PIN, POT_PIN, PIR_PIN, T1_PIN);
    sp->init();
    schedInit();
    Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(PIR_PIN),changeStatus, RISING);
}

void loop() {

    sched.run();
}

void schedInit() {
    sched.init(PERIOD);

    Task* t0 = new MotionDetectorTask(PIR_PIN, sp);
    t0->init(100);
    sched.addTask(t0);
	
	  Task* t1 = new ControlStateTask(sp);
    t1->init(100);
    sched.addTask(t1);
	
	  Task* t2 = new CommandsTask(sp);
    t2->init(20);
    sched.addTask(t2);
	
	  Task* t3 = new GetZuccheroTask(POT_PIN, sp);
    t3->init(100);
    sched.addTask(t3);
	
	  Task* t4 = new TurnOnLedTask(L1_PIN, L2_PIN, L3_PIN, sp);
    t4->init(100);
    sched.addTask(t4);

	  Task* t5 = new CoffeeMachineServiceTask(sp, msgService);
    t5->init(100);
    sched.addTask(t5);

    Task* t6 = new StartCoffeeTask(T1_PIN, sp);
    t6->init(100);
    sched.addTask(t6);
}
