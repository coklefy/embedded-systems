#include "Scheduler.h"
#include "Timer.h"
#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>


void Scheduler::init(int basePeriod) {
    this->basePeriod = basePeriod;
    this->timer = new Timer();
    this->timer->setupPeriod(basePeriod);
    this->nTasks = 0;
}

bool Scheduler::addTask(Task* task){
    if(nTasks < MAX_TASKS-1){
        taskList[nTasks] = task;
        nTasks++;
        return true;
    } else {
    return false;
    }
}

/* Check if is the right time to make tick */
void Scheduler::schedule(){
    for(int i=0; i<nTasks; i++){
        if(taskList[i]->updateAndCheckTime(basePeriod)){
            taskList[i]->tick();
        }
    }
}

/* Force to wait the tick */
void Scheduler::run(){
    this->timer->waitForNextTick();
    this->schedule();
}
