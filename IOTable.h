#ifndef iotable_h
#define iotable_h

#include <iostream>
#include <map>
#include "IOType.h"
#include "Error.h"

typedef enum
{
    INPUT_TABLE, OUTPUT_TABLE
} IOTABLE_TYPE;

class IOTable
{
    public:
        IOTable( IOTABLE_TYPE iot ) : type(iot) {}
        IOTABLE_TYPE getType() { return type; }
        bool addElement( std::string key, IOType *element )
        {
            bool success = false;
            if( table.find( key ) == table.end() )
            {
                table.insert( std::pair<std::string,IOType*>( key, element ) );
                success = true;
            }
            else
            {
                errorMsg( __func__, "An element already exists at the key: " + key );
            }
            return success;
        }
        IOType *getIO( std::string input_key )
        {
            IOType *io = 0;

            if( table.find( input_key ) != table.end() )
                io = table[ input_key ];
            return input;
        }
    private:
        IOTABLE_TYPE type;
        std::map<std::string,IOType*> table;
};

#endif
