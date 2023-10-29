#ifndef FILEHANDLING_FILES
#define FILEHANDLING_FILES

void DFILE_readtransactionData(List *pl);
void DFILE_writeTransactionData(ST_transaction *transData);
void DFILE_readAccountsData(List *pl);
void DFILE_updateAccountData(ST_terminalData_t *termData, ST_accountsDB_t *accountReference,List *pl);

#endif
