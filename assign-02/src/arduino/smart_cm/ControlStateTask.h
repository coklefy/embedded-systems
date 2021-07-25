#ifndef _CONTROL_STATE_TASK_
#define _CONTROL_STATE_TASK_

#include "ConcurrentTask.h"


class ControlStateTask : public ConcurrentTask {
	
	public:
		ControlStateTask(SharedSpace* sp);
		void init(int period);
		void tick();
		void sleep1();	
		
	private:
		int t, nr_Reads, flag, NrTotReads;
		/*
			STANDBY: 		 no presence detected
			ON:      		 presence detected
			READY:  		 presence detected within DIST1
			CHECK_TIME_1:	 check time
			CHECK_TIME_2:	 check time
			CHECK_TIME_3:	 check time
			FILTER :		 filters the "spurie" misures
		*/
		
		
		enum {STANDBY, ON, READY, MAINTENANCE, CHECK_TIME_1, CHECK_TIME_2, CHECK_TIME_3, TAKE_ME_TO_READY, FILTER} state;		
		
};
#endif
