#include "Error.h"

void messaging::errorMsg( std::string func, std::string msg )
{
    std::cout << "Function::" << func << ": " << msg << std::endl;
}

