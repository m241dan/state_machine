#ifndef statemachine_h
#define statemachine_h

#include "State.h"

class StateMachine
{
    std::map<std::string,State> states;
};

#endif
