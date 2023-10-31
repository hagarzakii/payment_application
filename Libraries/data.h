#ifndef DATASTRUCTURES_DATA
#define DATASTRUCTURES_DATA

#include"../Payment_System/Card/card.h"
#include"../Payment_System/Terminal/terminal.h"

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD,FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
 
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	int transactionSequenceNumber;
}ST_transaction;

typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND,LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;
 
typedef enum EN_accountState_t
{
	RUNNING,BLOCKED
}EN_accountState_t;
 
typedef struct ST_accountsDB_t
{
	char accountName[25];
	float balance;
	EN_accountState_t state;
	char primaryAccountNumber[20];
	char cardExpirationDate[6];
}ST_accountsDB_t;

typedef struct Datatype {
    enum { TRANSACTION, ACCOUNT } type;
    union {
        ST_transaction transactionData;
        ST_accountsDB_t accountData;
    } data;
} dataType;

typedef dataType listEntry ;

#endif