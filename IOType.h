#ifndef iotype_h
#define iotype_h

#include "Globals.h"

typedef struct validator
{
   const int type;
   const size_t size;
   const char checksum;
} VALIDATOR;

VALIDATOR ioint_validator = { IOTYPE_INT, sizeof( int ), SUM_INT };
VALIDATOR ioflt_validator = { IOTYPE_FLT, sizeof( float ), SUM_FLT };

class IOType
{
    public:
       IOType( const int t, const char c, const size_t s ) : type(t), validating_checksum(c), size(s) {}
       const int type;
       const size_t size;
       const char validating_checksum;
};

/*
 * Wrapper Examples
 */
class IOInt : public IOType
{
    public:
        IOInt( int v ) : IOType( IOTYPE_INT, SUM_INT, sizeof( int ) ), data(v) {}
        int data;
};

class InputFloat : public IOType
{
    public:
        InputFloat( float v ) : IOType( IOTYPE_FLT, SUM_FLT, sizeof( float ) ), data(v) {}
        const float data;
};

class OutputFloat : public IOType
{
    public:
        OutputFloat( float v ) : IOType( IOTYPE_FLT, SUM_FLT, sizeof( float ) ), data(v) {}
        float data;
};

/*
 * Validator Function
 */
bool is_io_valid( const IOType *to_test, VALIDATOR params ) {
    bool valid = false;

    if( to_test->type == params.type &&
        to_test->size == params.size &&
        to_test->validating_checksum == params.checksum )
        valid = true;

    return valid;
}


#endif
