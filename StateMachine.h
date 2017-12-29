#ifndef statemachine_h
#define statemachine_h

#include <iostream>
#include <map>
#include "State.h"
#include "Error.h"
#include "Globals.h"
#include "IOTable.h"

class StateMachine
{
    public:
        StateMachine() : curr_state_identifier(INVALID_STATE_NAME),
                         inputs(IOTable( INPUT_TABLE )),
                         outputs(IOTable( OUTPUT_TABLE )) {}
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
                std::string next_state = INVALID_STATE_NAME;	//assume nothing

                curr_state->action();				//1
                outputDebugString();				//2
                next_state = curr_state->transition();		//3
                transitionTo( next_state );			//4
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
                errorMsg( __func__, "Bad State Name: '" + INVALID_STATE_NAME + "'" );
            }
            else if( new_state->getIdentifier() == "abstract" )
            {
                errorMsg( __func__, "Cannot add abstract states." );
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

        virtual bool addInput( std::string key, IOType *input )
        {
            bool success = false;

            if( inputs.addElement( key, input ) )
                success = true;
            return success;
        }

        IOType *getOutput( std::string key )
        {
            IOType *output_to_return = 0;

            output_to_return = outputs.getIO( key );

            return output_to_return;
        }


        std::string getCurrentIdentifier()
        {
            return curr_state_identifier;
        }
        friend IOTable &State::getInputs();
        friend IOTable &State::getOutputs();

    protected:
        virtual void transitionTo( std::string next_state )
        {
            if( curr_state_identifier != next_state )
            {
                if( next_state == INVALID_STATE_NAME )
                {
                    errorMsg( __func__, "TransitionError: Attemping to transition to INVALID_STATE_NAME." );
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
                    errorMsg( __func__, "TransitionError: Attemping to transition to state '" + next_state + "' but state map does not contain '" + next_state + ".'" );
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

        IOTable				 inputs;
        IOTable				 outputs;
};

IOTable &State::getInputs() { return owner->inputs; }
IOTable &State::getOutputs() { return owner->outputs; }


#endif
