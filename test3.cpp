#include "IOTable.h"
#include "IOType.h"

int main()
{
    IOTable inputs( INPUT_TABLE );
    IOTable outputs( OUTPUT_TABLE );

    IOInt myint( 5 );

    inputs.addElement( "test", (IOType *)&myint );
    outputs.addElement( "test", (IOType *)&myint );

    const IOInt *testoutput = (const IOInt *)outputs.getIO( "test" );
    IOInt *testinput = (IOInt *)inputs.getIO( "test" );
    const IOType *typetest = inputs.getIO( "test" );

    if( is_io_valid( typetest, ioint_validator ) )
        std::cout << "Valid" << std::endl;
    else
        std::cout << "Invalid" << std::endl;

    testinput->data = 6;
    std::cout << "testinput is " << testinput->data << std::endl;
    std::cout << "testoutput is " << testoutput->data << std::endl;

    return 0;
}
