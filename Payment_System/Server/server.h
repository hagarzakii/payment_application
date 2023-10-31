#ifndef PAYMENTAPPLICATION_SERVER_H
#define PAYMENTAPPLICATION_SERVER_H

#include"../../Libraries/data.h"
#include"../../Data_Structures/List/list.h"

typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND,LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

EN_transState_t recieveTransactionData(ST_transaction*transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence, List *pl);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_accountsDB_t* accountRefrence);
EN_serverError_t saveTransaction(ST_transaction *transData , List *pl);
void listSavedTransaction(ST_transaction *transData);

#endif