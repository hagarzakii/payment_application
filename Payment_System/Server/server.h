#ifndef PAYMENTAPPLICATION_SERVER_H
#define PAYMENTAPPLICATION_SERVER_H

#include"../Card/card.h"
#include"../Terminal/terminal.h"

typedef struct List List;

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

EN_transState_t recieveTransactionData(ST_transaction*transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence, List *pl);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_accountsDB_t* accountRefrence);
EN_serverError_t saveTransaction(ST_transaction *transData , List *pl);
void listSavedTransaction(ST_transaction *transData);

#endif