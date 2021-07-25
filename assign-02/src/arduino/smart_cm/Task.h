#ifndef ___TASK__
#define ___TASK__

/* Implement Task */
class Task {

    int timeElapsed;

  public:
    virtual void init(int period) {
      myPeriod = period;
      timeElapsed = 0;
    }

    virtual void tick() = 0;

    bool updateAndCheckTime(int basePeriod) {
      timeElapsed += basePeriod;
      if (timeElapsed >= myPeriod) {
        timeElapsed = 0;
        return true;
      } else {
        return false;
      }
    }

  protected:
    int myPeriod;
};

#endif


