#include "IOTable.h"
#include "IOType.h"

int main()
{
    IOTable inputs( INPUT_TABLE );
    IOTable outputs( OUTPUT_TABLE );

    int x = 5;

    IOInt myint( &x );

    inputs.addElement( "test", (IOType *)&myint );
    outputs.addElement( "test", (IOType *)&myint );

    IOInt *testoutput = (IOInt *)outputs.getIO( "test" );
    IOInt *testinput = (IOInt *)inputs.getIO( "test" );
    IOType *typetest = inputs.getIO( "test" );

    if( is_io_valid( typetest, ioint_validator ) )
        std::cout << "Valid" << std::endl;
    else
        std::cout << "Invalid" << std::endl;

    x = 6;
    std::cout << "testinput is " << testinput->getValue() << std::endl;
    std::cout << "testoutput is " << testoutput->getValue() << std::endl;

    return 0;
}
