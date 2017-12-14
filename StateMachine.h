#ifndef statemachine_h
#define statemachine_h

#include <iostream>
#include <map>
#include "State.h"

//need to add inputs and outputs to states...
//mayhaps state machine will hold the physical stuff and any state added will
//get a reference to them?

class StateMachine
{
    public:
        StateMachine() : curr_state_identifier("*_none_*") {}
        /*
         * action()
         * debugMessaging()
         * transition()
         * transitionTo() -> perform the transition
         *     curr->onEnter()
         *     next->onExit()
         */
        virtual void run()
        {
            if( getCurrentIdentifier() != "*_none_*" && curr_state != 0 )
            {
                std::string next_state = "";

                curr_state->action();
                outputDebugString();
                next_state = curr_state->transition();
                transitionTo( next_state );
            }
        }
        /*
         * Could possible add a check to make sure two states don't have the same identifier.
         * Or, have it automatically overwrite and dequeue/delete the state that used to share
         * the same identifier.
         * Which is safer? Functional perspective? Memory management perspecftive?
         */
        virtual void addState( std::string identifier, State *new_state )
        {
            states[ identifier ] = new_state;
            if( getCurrentIdentifier() == "*_none_*" )
            {
               curr_state = new_state;
               curr_state->onEnter( curr_state_identifier );
               curr_state_identifier = new_state->getIdentifier();
            }
        }

        std::string getCurrentIdentifier()
        {
            return curr_state_identifier;
        }
    protected:
        virtual void transitionTo( std::string next_state )
        {
            if( curr_state_identifier != next_state )
            {
                if( states[ next_state ] )
                {
                    curr_state->onExit( next_state );
                    curr_state = states[ next_state ];
                    curr_state->onEnter( curr_state_identifier );
                    curr_state_identifier = next_state;
                }
                else
                {
                    std::cout << "StateMachine:TransitionError: Attemping to transition to state '" << next_state << "' but state map does not contain '" << next_state << ".'" << std::endl;
                }
            }
        }
        virtual void outputDebugString()
        {
            std::cout << curr_state->debugString() << std::endl;
        }
    private:
        State 				*curr_state;
        std::string 	 		 curr_state_identifier;
        std::map<std::string,State*> 	 states;

};

#endif
