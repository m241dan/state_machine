#ifndef timedqueuestate_h
#define timedqueuestate_h

#include "State.h"

class TimedQueueState : public State
{
    public:
        TimedQueueState( std::string id = "timed queued state", unsigned long long &t ) : timer(t), State( id ) {}
        virtual void onEnter( std::string prev_state ) {}
        virtual void onExit( std::string next_state ) {}
        virtual std::transition( void ) { return state_identifier; }
        void action()
        {
        }
    private:
        unsigned long long &timer;
};

#endif
