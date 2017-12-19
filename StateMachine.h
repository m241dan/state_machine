#ifndef statemachine_h
#define statemachine_h

#include <iostream>
#include <map>
#include "State.h"
#include "Error.h"
#include "Globals.h"
#include "IOTable.h"

//need to add inputs and outputs to states...
//mayhaps state machine will hold the physical stuff and any state added will
//get a reference to them?

class StateMachine
{
    public:
        StateMachine() : curr_state_identifier(INVALID_STATE_NAME) {}
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
            if( getCurrentIdentifier() != INVALID_STATE_NAME && curr_state != 0 )
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
        virtual bool addState( std::string identifier, State *new_state )
        {
            if( new_state->getIdentifier() == INVALID_STATE_NAME )
            {
                errorMsg( __func__, "Bad State Name: '" + INVALID_STATE_NAME + "'" );
                return false;
            }
            else if( new_state->getIdentifier() == "abstract" )
            {
                errorMsg( __func__, "Cannot add abstract states." );
                return false;
            }
            states.insert( std::pair<std::string,State*>( identifier, new_state ) );
            if( getCurrentIdentifier() == INVALID_STATE_NAME )
            {
               curr_state = new_state;
               curr_state->onEnter( curr_state_identifier );
               curr_state_identifier = new_state->getIdentifier();
            }
            return true;
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
                if( states.find( next_state ) != states.end() )
                {
                    curr_state->onExit( next_state );
                    curr_state = states[ next_state ];
                    curr_state->onEnter( curr_state_identifier );
                    curr_state_identifier = next_state;
                }
                else
                {
                    errorMsg( __func__, "StateMachine:TransitionError: Attemping to transition to state '" + next_state + "' but state map does not contain '" + next_state + ".'" );
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
