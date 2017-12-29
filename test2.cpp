#include <iostream>

#include "State.h"

class BadState : public State
{
    public:
        BadState() : State( "test" ) {}
};

int main()
{
    const BadState *state = new BadState();
    const State *mystate = (const State *)state;
    const BadState *orig = (const BadState *)mystate;
    std::cout << "test..." << std::endl;
    return 0;
}

