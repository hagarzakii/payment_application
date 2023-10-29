#include"../../Libraries/libraries.h"
#include"../../Data_Structures/List/list.h"
#include"server.h"
#include"../../Data_Bases/File_Handling/file_handling.h"

EN_transState_t recieveTransactionData(ST_transaction *transData)
{
	List l;
	createList(&l);
	
	DFILE_readtransactionData(&l);
	
    DFILE_readAccountsData(&l);
	
	EN_serverError_t status = APPROVED;
	transData->transState = status;
	ST_accountsDB_t accountReference;
	status = isValidAccount(&transData->cardHolderData , &accountReference,&l);
	if(status == ACCOUNT_NOT_FOUND)
	{
		transData->transState = FRAUD_CARD;
		saveTransaction(transData , &l);
		return FRAUD_CARD;
	}
	EN_cardError_t cardStatus;
	strcpy(transData->cardHolderData.cardExpirationDate , accountReference.cardExpirationDate);
	cardStatus = getCardExpiryDate(&transData->cardHolderData);
	if(cardStatus == WRONG_EXP_DATE)
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		saveTransaction(transData , &l);
		return INTERNAL_SERVER_ERROR;
	}
	
	EN_terminalError_t terminalStatus;
	terminalStatus = isCardExpired(&transData->cardHolderData, &transData->terminalData);
	if(terminalStatus == EXPIRED_CARD)
	{
		transData->transState = FRAUD_CARD;
		saveTransaction(transData , &l);
		return FRAUD_CARD;
	}
	
	status = isAmountAvailable(&transData->terminalData,&accountReference);
	if(status == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		saveTransaction(transData , &l);
		return DECLINED_INSUFFECIENT_FUND;
	}
	status = isBlockedAccount(&accountReference);
	if(status == BLOCKED_ACCOUNT)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		saveTransaction(transData , &l);
		return DECLINED_STOLEN_CARD;;
	}
	if(transData->transState == APPROVED)
	{
	  saveTransaction(transData , &l);
	  DFILE_updateAccountData(&transData->terminalData, &accountReference,&l);
	}
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference, List *pl)
{	
	ListNode *current = pl->head;

    while (current != NULL) {
        listEntry entry = current->entry;
		if (entry.type == ACCOUNT) {
        ST_accountsDB_t accountData = entry.data.accountData;
            int compareLength = (strlen(cardData->primaryAccountNumber) < strlen(accountData.primaryAccountNumber))? strlen(cardData->primaryAccountNumber): strlen(accountData.primaryAccountNumber);
            if ((strncmp(cardData->primaryAccountNumber, accountData.primaryAccountNumber,compareLength) == 0) && (strcmp(cardData->cardHolderName , accountData.accountName)== 0)) {
                *accountReference = accountData;
                return SERVER_OK;
            }
		}
			current = current->next;
        }
    accountReference = NULL;
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference)
{
	return (accountReference->state == BLOCKED) ? BLOCKED_ACCOUNT : SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_accountsDB_t* accountReference)
{
	return (termData->transAmount <= accountReference->balance) ? SERVER_OK : LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction *transData, List *pl)
{
	int lastTransSeq;
	ListNode *current = pl->head;
    while (current != NULL) {
        listEntry entry = current->entry;
		if (entry.type == TRANSACTION) {
        ST_transaction transactionData = entry.data.transactionData;
            if (strcmp(transData->cardHolderData.primaryAccountNumber, transactionData.cardHolderData.primaryAccountNumber) == 0) {
                lastTransSeq = transactionData.transactionSequenceNumber;
            }
		}
			current = current->next;
        }
		transData->transactionSequenceNumber = ++lastTransSeq;
    DFILE_writeTransactionData(transData);
	listSavedTransaction(transData);
	return SERVER_OK;	
}
void listSavedTransaction(ST_transaction *transData)
{	
	char state[30];
	if (transData->transState == APPROVED) {
            strcpy(state , "APPROVED");
        }else if (transData->transState == DECLINED_INSUFFECIENT_FUND) {
            strcpy(state , "DECLINED_INSUFFECIENT_FUND");
        }else if (transData->transState == DECLINED_STOLEN_CARD) {
            strcpy(state , "DECLINED_STOLEN_CARD");
        }else if (transData->transState == FRAUD_CARD) {
            strcpy(state , "FRAUD_CARD");
        }else if (transData->transState == INTERNAL_SERVER_ERROR) {
           strcpy(state , "INTERNAL_SERVER_ERROR");
		}
    printf("#########################\n");
    printf("Cardholder Name: %s\n", transData->cardHolderData.cardHolderName);
    printf("Primary Account Number: %s\n", transData->cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date: %5s\n", transData->cardHolderData.cardExpirationDate);
    printf("Transaction Amount: %.2f\n", transData->terminalData.transAmount);
    printf("Max Transaction Amount: %.2f\n", transData->terminalData.maxTransAmount);
    printf("Transaction Date: %s\n", transData->terminalData.transactionDate);
	printf("Transaction State: %s\n", state);
    printf("Transaction Sequence Number: %d\n", transData->transactionSequenceNumber);
    printf("#########################\n");
}