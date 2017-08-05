#ifndef timedqueuesubstate_h
#define timedqueuesubstate_h

#include "TimedQueueState.h"

class TimedQueueSubState : public TimedQueueState
{
    public:
        TimedQueueSubState( std::string id "timed queue substate", unsigned long long &t ) : TimedQueueState( id, t ) {}
};

#endif
