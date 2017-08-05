#ifndef timedqueuestate_h
#define timedqueuestate_h

#include "State.h"

class TimedQueueState : public State
{
    public:
        TimedQueueState( std::string id = "timed queued state", unsigned long long &t ) : timer(t), State( id ) {}
        /*
         * Either onEnter or onExit should most likely reset any events remaining
         * in the queue. Events should be initialized with an offset based on a
         * current time.
         */
        virtual void onEnter( std::string prev_state ) {}
        virtual void onExit( std::string next_state ) {}
        /*
         * should likely transition out if its queue is empty
         */
        virtual std::transition( void ) { return state_identifier; }
        /*
         * Action will not be a virtual function because it should handle events,
         * ie, function calls, in a single uniform manner. 
         */
        void action()
        {
        }
    private:
        //event queue
        unsigned long long &timer;
};

#endif
