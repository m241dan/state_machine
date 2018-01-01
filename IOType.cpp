#include "IOType.h"

VALIDATOR ioint_validator = { IOTYPE_INT, sizeof( int ), SUM_INT };
VALIDATOR ioflt_validator = { IOTYPE_FLT, sizeof( float ), SUM_FLT };

bool is_io_valid( const IOType *to_test, VALIDATOR params ) {
    bool valid = false;

    if( to_test &&
        to_test->type == params.type &&
        to_test->size == params.size &&
        to_test->validating_checksum == params.checksum )
        valid = true;

    return valid;
}

