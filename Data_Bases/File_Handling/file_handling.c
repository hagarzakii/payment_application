#include "../../Libraries/libraries.h"
#include "../../Data_Structures/List/list.h"
#include"file_handling.h"

void DFILE_readtransactionData(List *pl) {
    FILE *fileRead;
    fileRead = fopen("C:/Users/User/OneDrive/Documents/paymentApplication/Data_Bases/Data/transactionData.txt", "r");

    if (fileRead == NULL) {
        perror("Error opening file");
        return;
    }
	
	listEntry entry;
	
	char readState[30];

    while (fscanf(fileRead, "%25[^,],%20[^,],%6[^,],%f,%f,%11[^,],%30[^,],%d",
                  entry.data.transactionData.cardHolderData.cardHolderName,
				  entry.data.transactionData.cardHolderData.primaryAccountNumber,
                  entry.data.transactionData.cardHolderData.cardExpirationDate,
                  &entry.data.transactionData.terminalData.transAmount,
                  &entry.data.transactionData.terminalData.maxTransAmount,
                  entry.data.transactionData.terminalData.transactionDate,
				  readState,
                  &entry.data.transactionData.transactionSequenceNumber) == 8) 
	{
		if (strcmp(readState, "APPROVED") == 0) {
            entry.data.transactionData.transState = APPROVED;
        }else if (strcmp(readState, "DECLINED_INSUFFECIENT_FUND") == 0) {
            entry.data.transactionData.transState = DECLINED_INSUFFECIENT_FUND;
        }else if (strcmp(readState, "DECLINED_STOLEN_CARD") == 0) {
            entry.data.transactionData.transState = DECLINED_STOLEN_CARD;
        }else if (strcmp(readState, "FRAUD_CARD") == 0) {
            entry.data.transactionData.transState = FRAUD_CARD;
        }else if (strcmp(readState, "INTERNAL_SERVER_ERROR") == 0) {
           entry.data.transactionData.transState = INTERNAL_SERVER_ERROR;
        }
		entry.type = TRANSACTION;
        insertList(entry, pl);
	}
    fclose(fileRead);
}

void DFILE_writeTransactionData(ST_transaction *transData) {
    FILE *fileWrite;
    fileWrite = fopen("C:/Users/User/OneDrive/Documents/paymentApplication/Data_Bases/Data/transactionData.txt", "a");

    if (fileWrite == NULL) {
        perror("Error opening file for writing");
        return;
    }
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
        fprintf(fileWrite, "%s,%s,%s,%.2f,%.2f,%s,%s,%d\n",
                transData->cardHolderData.cardHolderName,
                transData->cardHolderData.primaryAccountNumber,
                transData->cardHolderData.cardExpirationDate,
                transData->terminalData.transAmount,
                transData->terminalData.maxTransAmount,
                transData->terminalData.transactionDate,
				state,
                transData->transactionSequenceNumber);
        fclose(fileWrite);
}


void DFILE_readAccountsData(List *pl) {
    FILE *fileRead;
    fileRead = fopen("C:/Users/User/OneDrive/Documents/paymentApplication/Data_Bases/Data/accountsData.txt", "r");

    if (fileRead == NULL) {
        perror("Error opening file");
        return;
    }
	
	listEntry entry;
	char readState[7];
	
    while (fscanf(fileRead, "%25[^,],%f,%19[^,],%19[^,],%6[^,]", 
	              entry.data.accountData.accountName,
                  &entry.data.accountData.balance,
                  readState,
                  entry.data.accountData.primaryAccountNumber,
				  entry.data.accountData.cardExpirationDate) == 5) { 
				  int len = strcspn(entry.data.accountData.cardExpirationDate, "\n");
					if (len < 6) {
						entry.data.accountData.cardExpirationDate[len] = '\0';
					}
        if (strcmp(readState, "RUNNING") == 0) {
            entry.data.accountData.state = RUNNING;
        } else if (strcmp(readState, "BLOCKED") == 0) {
            entry.data.accountData.state = BLOCKED;
        }
		entry.type = ACCOUNT;
        insertList(entry, pl);
		}
    fclose(fileRead);
}

void DFILE_updateAccountData(ST_terminalData_t *termData, ST_accountsDB_t *accountReference,List *pl)
{
	FILE *fileWrite;
    fileWrite = fopen("C:/Users/User/OneDrive/Documents/paymentApplication/Data_Bases/Data/accountsData.txt", "w");

    if (fileWrite == NULL) {
        perror("Error opening file for writing");
        return;
    }
	ListNode *current = pl->head;
	
	float newBalance = (accountReference->balance) - (termData->transAmount);
	
    while (current != NULL) {
        listEntry entry = current->entry;
		if (entry.type == ACCOUNT) {
        ST_accountsDB_t accountData = entry.data.accountData;
		
		if (strcmp(accountReference->primaryAccountNumber, accountData.primaryAccountNumber) == 0) {
                accountData.balance = newBalance;
            }
		
		char stat[10];
	if (accountData.state == BLOCKED) {
            strcpy(stat , "BLOCKED");
        }else if (accountData.state == RUNNING) {
            strcpy(stat , "RUNNING");
        }
		
        fprintf(fileWrite, "%s,%.2f,%s,%s,%s\n",
		        accountData.accountName,
                accountData.balance,
                stat,
                accountData.primaryAccountNumber,
				accountData.cardExpirationDate);
            }
			current = current->next;
}
   
    fclose(fileWrite);
}