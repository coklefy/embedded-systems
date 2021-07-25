#include "Arduino.h"
#include "ConcurrentTask.h"
#include "Potenziometro.h"


/* Class which manages movement detection */
class GetZuccheroTask: public ConcurrentTask {

    public:
        GetZuccheroTask(int pin, SharedSpace* sp);
        void init(int period);
        void tick();

    protected:
        int pin;
        Potenziometro* pot;

    /*
        STATES INFO:

        WAITING: 	machine isn't in a state to accept the sugar
        GET_SUGAR:  set the sugar
    */
    enum { WAITING, GET_SUGAR } state;

};
