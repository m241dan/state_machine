#ifndef iotype_h
#define iotype_h

#include "Globals.h"

typedef struct validator
{
   const int type;
   const size_t size;
   const char checksum;
} VALIDATOR;

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
        IOInt( int *v ) : IOType( IOTYPE_INT, SUM_INT, sizeof( int ) ), data(v) {}
        int getValue() { return *data; }
    private:
        int *data;
};

class IOFloat : public IOType
{
    public:
        IOFloat( float *v ) : IOType( IOTYPE_FLT, SUM_FLT, sizeof( float ) ), data(v) {}
        float getValue() { return *data; }
    private:
        float *data;
};

/*
 * Validator Function
 */

extern VALIDATOR ioint_validator;
extern VALIDATOR ioflt_validator;

bool is_io_valid( const IOType *to_test, VALIDATOR params );

#endif
