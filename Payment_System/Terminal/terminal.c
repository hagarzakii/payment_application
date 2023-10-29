#include"terminal.h"
#include"../../Libraries/libraries.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	EN_terminalError_t terminalError;
	printf("Enter Transaction date (DD/MM/YYYY):\n");
	scanf("%s" , termData->transactionDate);
	if(strlen(termData->transactionDate) != 10 || termData->transactionDate == NULL)
	{
		terminalError = WRONG_DATE;
	}
	else if(termData->transactionDate[2] != '/' && termData->transactionDate[5] != '/' )
	{	
		terminalError = WRONG_DATE;
	}
	else
	{
		int day = (termData->transactionDate[0]-'0')*10 + termData->transactionDate[1]-'0';
		int month = (termData->transactionDate[3]-'0')*10 + termData->transactionDate[4]-'0';
		int year = (termData->transactionDate[6]-'0')*1000 + (termData->transactionDate[7]-'0')*100 +(termData->transactionDate[8]-'0')*10 + termData->transactionDate[9]-'0';
		if(day > 31 || day < 1 || month < 1 || month > 12 || year < 2023)
		{
			terminalError = WRONG_DATE;
		}
		else
		{
			terminalError = TERMINAL_OK;
		}
	}
	return terminalError;
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	EN_terminalError_t terminalError;
	int cardExpMonth = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
	int cardExyear =  (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
	int transMonth = (termData->transactionDate[3]-'0')*10 + termData->transactionDate[4]-'0';
	int transYear = (termData->transactionDate[8]-'0')*10 + termData->transactionDate[9]-'0';
	if(transYear > cardExyear)
	{
		terminalError = EXPIRED_CARD ;
	}
	else if(transYear == cardExyear && transMonth > cardExpMonth)
	{
		terminalError = EXPIRED_CARD ;
	}
	else
	{
		terminalError = TERMINAL_OK;
	}
	return terminalError;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	EN_terminalError_t terminalError;
	printf("Enter Transaction amount:\n");
	scanf("%f", &termData->transAmount);
	if(termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
        terminalError = TERMINAL_OK;		
	}
	return terminalError;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	setMaxAmount(termData);
	EN_terminalError_t terminalError;
	if(termData->transAmount > termData->maxTransAmount)
	{
		terminalError = EXCEED_MAX_AMOUNT;
	}
	else
	{
		terminalError = TERMINAL_OK;
	}
	return terminalError;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	EN_terminalError_t terminalError;
	termData->maxTransAmount = MAXTRANSACTION;
	if(termData->maxTransAmount <= 0)
	{
		terminalError = INVALID_MAX_AMOUNT;
	}
	else
	{
		terminalError = TERMINAL_OK;
	}
	return terminalError;
}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
	int length = strlen(cardData->primaryAccountNumber);
	int sum = 0;
	bool multiply = false;
	for(int i = length - 1 ; i>=0 ; i--)
	{
		int num = cardData->primaryAccountNumber[i] - '0';
		if(multiply)
		{
		num=num*2;
		if(num > 9)
		{
			num = num-9;
		}
		}
		multiply = !multiply;
		sum+=num;
	}
	if(sum%10 == 0)
	{
		return TERMINAL_OK;
	}
	else
	{
		return INVALID_CARD;
	}
}