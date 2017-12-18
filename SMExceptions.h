#ifndef smexceptions_h
#define smexceptions_h

#include <iostream>
#include <exception>

class BadStateType : public std::exception {
    public:
        BadStateType( std::string gn ) : given_name(gn) {}
        ~BadStateType() throw() {}

        const std::string msg() const throw()
        {
            return "Exception Caught: " + given_name;
        }

    private:
        std::string given_name;
};

#endif
