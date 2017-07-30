#ifndef statemachine_h
#define statemachine_h

#include "State.h"

class StateMachine
{
    public:
        StateMachine() : curr_state_identifier("none") {}
        virtual void run()
        {
            if( curr_state_identify != "none" && curr_state != 0 )
            {
                std::string next_state = "";

                curr_state->action();
                next_state = curr_state->transition();
                outputDebugString();
                switchState( next_state );
            }
        }
    protected:
        virtual void switchState( std::string next_state )
        {
            if( curr_state_identifier != next_state && states[ next_state ] )
            {
                curr_state->onExit( next_state );
                curr_state = states[ next_state ];
                curr_state->onEnter( curr_state_identifier );
                curr_state_identifier = next_state;
            }
        }
        virtual void outputDebugString()
        {
            std::cout << curr_state->debugString() << std::endl;
        }
    private:
        State 				*curr_state;
        std::string 	 		 curr_state_identifier;
        std::map<std::string,State> 	 states;

};

#endif
