#ifndef iotype_h
#define iotype_h

#include "Globals.h"

typedef struct validator
{
   const IOTYPE type;
   const size_t size;
   const char checksum;
} VALIDATOR;

VALIDATOR ioint_validator = { IO_INT, sizeof( int ), INT_SUM };
VALIDATOR ioflt_validator = { IO_FLT, sizeof( float ), FLT_SUM };

class IOType
{
    public:
       IOType( IOTYPE t, char c, size_t s ) : type(t), validating_checksum(c), size(s) {}
       const IOTYPE type;
       const size_t size;
       const char validating_checksum;
};

/*
 * Wrapper Examples
 */
class IOInt : public IOType
{
    public:
        IOInt( int v ) : IOType( IO_INT, INT_SUM, sizeof( int ) ), data(v) {}
        int data;
};

class IOFloat : public IOType
{
    public:
        IOFloat( float v ) : IOType( IO_FLT, FLT_SUM, sizeof( float ) ), data(v) {}
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
