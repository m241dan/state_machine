#include "StateMachine.h"

class TestState : public State
{
    public:
        TestState( ) : State( "hello" ) {}
        virtual void action( void )
        {
            std::cout << "Hellooooo" << std::endl;
        }
        virtual std::string transition( void )
        {
            return "how";
        }
        virtual void onEnter( std::string prev_state )
        {
            if( prev_state != "none" )
            {
                std::cout << "\t\tReturning to 'hello'" << std::endl;
            }
        }
        virtual void onExit( std::string next_state )
        {
           std::cout << "\t\thello is transitioning to '" << next_state << "'" << std::endl;
        }
        virtual std::string debugString()
        {
            return "DEBUG STRING: 'hello'";
        }

};

class TestStateTwo : public State
{
    public:
        TestStateTwo( ) : State( "how" ) {}
        virtual void action( void )
        {
            std::cout << "How are you?" << std::endl;
        }
        virtual std::string transition( void )
        {
            return "hello";
        }
        virtual void onEnter( std::string prev_state )
        {
            std::cout << "\t\tEntering 'how' from '" << prev_state << "'" << std::endl;
        }
        virtual void onExit( std::string next_state )
        {
            std::cout << "\t\thow is transitioning to '" << next_state << "'" << std::endl;
        }
        virtual std::string debugString()
        {
            return "DEBUG STRING: 'how'";
        }
};

int main()
{
    StateMachine machine;
    TestState test;
    TestStateTwo test_two;

    machine.addState( test.getIdentifier(), (State *)&test );
    machine.addState( test_two.getIdentifier(), (State *)&test_two );
    while( 1 )
    {
        machine.run();
        for( int x = 0; x < 90000000; x++ );
    }
    return 0;
}
