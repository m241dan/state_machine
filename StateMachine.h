#ifndef statemachine_h
#define statemachine_h

#include <iostream>
#include <map>
#include "State.h"
#include "Error.h"
#include "Globals.h"

class StateMachine
{
    friend class State;
    public:
        StateMachine() : curr_state_identifier(INVALID_STATE_NAME) {}

        /*
         * 1.) action()
         * 2.) debugMessaging()
         * 3.) transition()
         * 4.) transitionTo() -> perform the transition
         *         curr->onEnter()
         *         next->onExit()
         */

        virtual void run()
        {
            if( getCurrentIdentifier() != INVALID_STATE_NAME && curr_state != 0 )
            {
                if( curr_state && curr_state->validOwner() )
                {
                    runAddonsPre();
                    std::string next_state = INVALID_STATE_NAME;	//assume nothing
                    next_state = curr_state->transition();		//1
                    transitionTo( next_state );				//2
                    curr_state->action();				//3
                    outputDebugString();				//4
                    runAddonsPost();
                }
                else
                    messaging::errorMsg( __func__, "attempting to run null state or a state without an owner." );
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
            bool success = false;

            if( new_state->getIdentifier() == INVALID_STATE_NAME )
            {
                messaging::errorMsg( __func__, "Bad State Name: '" + INVALID_STATE_NAME + "'" );
            }
            else if( new_state->getIdentifier() == "abstract" )
            {
                messaging::errorMsg( __func__, "Cannot add abstract states." );
            }

            states.insert( std::pair<std::string,State*>( identifier, new_state ) );
            new_state->setOwner( this );
            success = true;

            if( getCurrentIdentifier() == INVALID_STATE_NAME )
            {
               curr_state = new_state;
               curr_state->onEnter( curr_state_identifier );
               curr_state_identifier = new_state->getIdentifier();
            }
            return success;
        }


        std::string getCurrentIdentifier()
        {
            return curr_state_identifier;
        }

    protected:
        virtual void runAddonsPre() {}
        virtual void runAddonsPost() {}
        virtual void transitionTo( std::string next_state )
        {
            if( curr_state_identifier != next_state )
            {
                if( next_state == INVALID_STATE_NAME )
                {
                    messaging::errorMsg( __func__, "TransitionError: Attemping to transition to INVALID_STATE_NAME." );
                }
                else if( states.find( next_state ) != states.end() ) /*successful transition here */
                {
                    curr_state->onExit( next_state );
                    curr_state = states[ next_state ];
                    curr_state->onEnter( curr_state_identifier );
                    curr_state_identifier = next_state;
                }
                else
                {
                    messaging::errorMsg( __func__, "TransitionError: Attemping to transition to state '" + next_state + "' but state map does not contain '" + next_state + ".'" );
                }
            }
        }
        virtual void outputDebugString()
        {
            if( curr_state->debugString() != "" )
                std::cout << curr_state->debugString() << std::endl;
        }

    private:
        State 				*curr_state;
        std::string 	 		 curr_state_identifier;
        std::map<std::string,State*> 	 states;
};

#endif
