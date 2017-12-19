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
    protected:
        std::map<std::string,IOType*> table;
    private:
        IOTABLE_TYPE type;
};

class InputTable : public IOTable
{
    public:
        InputTable() : IOTable( INPUT_TABLE ) {}
        const IOType *getInput( std::string input_key )
        {
            if( table.find( input_key ) != table.end() )
                return (const IOType *)table[ input_key ];
            else
                return 0;
        }
};

class OutputTable : public IOTable
{
    public:
        OutputTable() : IOTable( OUTPUT_TABLE ) {}
        IOType *getOutput( std::string output_key )
        {
            if( table.find( output_key ) != table.end() )
                return table[ output_key ];
            else
                return 0;
        }
};

#endif
