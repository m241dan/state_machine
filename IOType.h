#ifndef iotype_h
#define iotype_h

#include "Globals.h"

class IOType
{
    public:
       IOType( IOTYPE t, char c, size_t s ) : type(t), checksum(c), size(s) {}
       IOTYPE getType() { return type; }
       size_t getSize() { return size; }
       char getCheckSum() { return checksum; }
    private:
       IOTYPE type;
       size_t size;
       char checksum;
};

class IOInt : public IOType
{
    public:
        IOInt( int v ) : IOType( IO_INT, 'i', sizeof( int ) ), value(v) {}
        int value;
};

#endif
