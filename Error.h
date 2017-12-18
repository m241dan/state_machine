#ifndef error_h
#define error_h

void errorMsg( std::string func, std::string msg )
{
    std::cout << "Function::" << func << ": " << msg << std::endl;
}

#endif
