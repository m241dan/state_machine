#ifndef error_h
#define error_h

#include <iostream>

namespace messaging
{
    void errorMsg( std::string func, std::string msg );
    void successMsg( std::string func, std::string msg );
};

#endif
