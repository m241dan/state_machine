#ifndef iotype_h
#define iotype_h

#include "Globals.h"

class IOType
{
    public:
       IOType( IOTYPE t, const char *si, const char *st ) : type(t)
       {
           sum_one[0] = *si;
           sum_one[1] = *si+1;
           sum_two[0] = *st;
           sum_two[1] = *st+1;
       }
       IOTYPE getType() { return type; }
       char *getSumOne() { return sum_one; }
       char *getSumTwo() { return sum_two; }
    private:
       IOTYPE type;
       char sum_one[2];
       char sum_two[2];
};

class IOInt : public IOType
{
    public:
        IOInt( int v ) : IOType( 0, "33", "34" ), value(v) {}
        int value;
};

#endif
