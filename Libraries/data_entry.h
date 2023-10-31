#ifndef DATASTRUCTURES_DATA_ENTRY
#define DATASTRUCTURES_DATA_ENTRY

#include "../Payment_System/Server/server.h"

typedef struct Datatype {
    enum { TRANSACTION, ACCOUNT } type;
    union {
        ST_transaction transactionData;
        ST_accountsDB_t accountData;
    } data;
} dataType;

typedef dataType listEntry ;

#endif