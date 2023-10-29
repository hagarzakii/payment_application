#include"../Libraries/libraries.h"
#include"application.h"
#include"../Payment_System/Card/card.h"
#include"../Payment_System/Terminal/terminal.h"
#include"../Payment_System/Server/server.h"

int main(void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardStatus;
	
	ST_terminalData_t termData;
	EN_terminalError_t terminalStatus;
	
	
	printf("Welcome to our payment application\n");
	
	
	cardStatus = getCardHolderName(&cardData);
	while(cardStatus == WRONG_NAME)
	{
		printf("The name should be from 20 to 24 characters\n");
		cardStatus = getCardHolderName(&cardData);
	}

	cardStatus = getCardPAN(&cardData);
	while(cardStatus == WRONG_PAN)
	{
		printf("The PAN should range from 16 to 19 digits\n");
		cardStatus = getCardPAN(&cardData);
	}
	terminalStatus = isValidCardPAN(&cardData);
	if(terminalStatus == INVALID_CARD)
	{
		printf("PAN should be a Luhn Number\n");
		return 0;
	}

	terminalStatus = getTransactionDate(&termData);
	while(terminalStatus == WRONG_DATE)
	{
		printf("Wrong Date\n");
		terminalStatus = getTransactionDate(&termData);
	}
	
	terminalStatus = getTransactionAmount(&termData);
	while(terminalStatus == INVALID_AMOUNT)
	{
		printf("Invalid amount\n");
		terminalStatus = getTransactionAmount(&termData);
	}
	terminalStatus = isBelowMaxAmount(&termData);
	while(terminalStatus == EXCEED_MAX_AMOUNT)
	{
		printf("Exceeded max amount\n");
		terminalStatus = isBelowMaxAmount(&termData);
	}
	
	ST_transaction transactionData;
    transactionData.cardHolderData = cardData;
    transactionData.terminalData = termData;
    
	EN_transState_t state;
	recieveTransactionData(&transactionData);
	
	return 0;
}