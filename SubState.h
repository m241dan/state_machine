#ifndef substate_h
#define substate_h

/*
 * A Sub State is employed by a HighState that it is friends with
 * so that it can control things within the HighState.
 */

#include "StateMachine.h"

class SubState : State
{
    public:
        SubState( std::string si "substate" ) : state_identifier(si) {}
};

#endif
