#ifndef iotype_h
#define iotype_h

#include "Globals.h"

class IOType
{
    public:
       IOType( IOTYPE t, char c, size_t s ) : type(t), checksum(c), size(s) {}

       IOTYPE getType() { return type; }
       size_t getSize() { return size; }
       char getCheckSum() { return validating_checksum; }
       template <class T>
       bool validate()
       {
       }

    private:
       IOTYPE type;
       size_t size;
       char checksum;
};

class IOInt : public IOType
{
    public:
        IOInt( int v ) : IOType( IO_INT, INT_SUM, sizeof( int ) ), data(v) {}
        int data;
        static const char checksum = INT_SUM;
};

class IOFloat : public IOType
{
    public:
        IOFloat( float v ) : IOType( IO_FLOAT, FLT_SUM, sizeof( float ) ), data(v) {}
        float data;
        static const char checksum = FLT_SUM;
};

#endif
