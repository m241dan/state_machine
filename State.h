#ifndef state_h
#define state_h

/*************************************************************************
 * This is the base State that all states should inherit from to be used *
 * inside of the D State Machine library implementation.                 *
 *                                                                       *
 * Written by Daniel R. Koris                                            *
 *************************************************************************/

#include <iostream>
#include "Error.h"
#include "Globals.h"
#include "IOTable.h"

class StateMachine; //a little forward declaration to handle order of include problems

class State
{
    public:
        State( std::string si = "abstract" ) : state_identifier(si)
        {
            if( si == "abstract" )
                messaging::errorMsg( __func__, "created an instance of an abstract state." );
            if( si == INVALID_STATE_NAME )
                messaging::errorMsg( __func__, "created a state with an invalid state name." );
            owner = 0;
        }

        //virtual functions
        virtual void 		action( void ) {}
        virtual std::string 	transition( void ) { return state_identifier; }	//it will always transition to itself by default
        virtual void 		onEnter( std::string prev_state ) {}
        virtual void 		onExit( std::string next_state ) {}
        virtual std::string 	debugString() { return ""; }
        virtual std::string	getIdentifier() { return state_identifier; }
        virtual bool		setOwner( StateMachine *sm )
        {
            bool success = false;

            if( !owner )
            {
                owner = sm;
                success = true;
            }
            return success;
        }

        IOTable &getInputs();
        IOTable &getOutputs();

    protected:
        StateMachine *owner;
    private:
        bool valid_state;
        std::string state_identifier;

};

#endif
