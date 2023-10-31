#include"../Libraries/libraries.h"
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
	
	for(int counter = 1 ; counter <=3 ; counter++)
	{
		cardStatus = getCardHolderName(&cardData);
		if(cardStatus == WRONG_NAME)
		{
			printf("The name should be from 20 to 24 characters\n");
			cardStatus = getCardHolderName(&cardData);
		}
		else{
			break;
		}
	}

    for(int counter = 1 ; counter <=3 ; counter++)
	{
		cardStatus = getCardPAN(&cardData);
		if(cardStatus == WRONG_PAN)
		{
			printf("The PAN should range from 16 to 19 digits\n");
			cardStatus = getCardPAN(&cardData);
		}
		else{
			break;
		}
	}
	
	terminalStatus = isValidCardPAN(&cardData);
	if(terminalStatus == INVALID_CARD)
	{
		printf("Invalid PAN\n");
		return 0;
	}

    for(int counter = 1 ; counter <=3 ; counter++)
	{
		terminalStatus = getTransactionDate(&termData);
		if(terminalStatus == WRONG_DATE)
		{
			printf("Wrong Date\n");
			terminalStatus = getTransactionDate(&termData);
		}
		else{
			break;
		}
	}
	
	for(int counter = 1 ; counter <=3 ; counter++)
	{
		terminalStatus = getTransactionAmount(&termData);
		if(terminalStatus == INVALID_AMOUNT)
		{
			printf("Invalid amount\n");
			terminalStatus = getTransactionAmount(&termData);
		}
		else{
			break;
		}
	}
	
	terminalStatus = isBelowMaxAmount(&termData);
	if(terminalStatus == EXCEED_MAX_AMOUNT)
	{
		printf("Exceeded max amount\n");
		return 0;
	}
	
	ST_transaction transactionData;
    transactionData.cardHolderData = cardData;
    transactionData.terminalData = termData;
    
	EN_transState_t state;
	recieveTransactionData(&transactionData);
	
	return 0;
}