#include "MotionDetectorTask.h"
#include "Pir.h"

MotionDetectorTask::MotionDetectorTask(int pinNr, SharedSpace* sp): pin(pinNr) {
    this->sp = sp;
}

void MotionDetectorTask::init(int period) {
     Task::init(period);
     pir = new Pir(pin);
     state = NO_MOVEMENT;
}

void MotionDetectorTask::tick(){
  
    switch (state) {
      
      case NO_MOVEMENT:
          if (pir->motionDetected()) {
              sp->setMov(true);
              state = MOVEMENT;
           }
          break;
          
      case MOVEMENT:
          if (!pir->motionDetected()) {
              sp->setMov(false);
              state = NO_MOVEMENT;
          }
        break;
    }
}
