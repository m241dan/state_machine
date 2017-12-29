#ifndef iotype_h
#define iotype_h

#include "Globals.h"

typedef struct validator
{
   const int type;
   const size_t size;
   const char checksum;
} VALIDATOR;

VALIDATOR ioint_validator = { IOTYPE.INT, sizeof( int ), SUM.INT };
VALIDATOR ioflt_validator = { IOTYPE.FLT, sizeof( float ), SUM.FLT };

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
        IOInt( int v ) : IOType( IOTYPE.INT, SUM.INT, sizeof( int ) ), data(v) {}
        int data;
};

class IOFloat : public IOType
{
    public:
        IOFloat( float v ) : IOType( IOTYPE.FLT, SUM.FLT, sizeof( float ) ), data(v) {}
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
