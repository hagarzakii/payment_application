#include"../../Libraries/libraries.h"
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	EN_cardError_t cardError;
    printf("Enter Card holder Name:\n");
    scanf("%[^\n]",cardData->cardHolderName);
	if(strlen(cardData->cardHolderName) > CARDHOLDERMAX || strlen(cardData->cardHolderName) < CARDHOLDERMIN || cardData->cardHolderName == NULL)
	{
		cardError = WRONG_NAME;
	}
	else{
		cardError = CARD_OK;
	}
	return cardError;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	EN_cardError_t cardError;
	if(strlen(cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate == NULL)
	{
		cardError = WRONG_EXP_DATE;
	}
	else if(cardData->cardExpirationDate[2] != '/')
	{
		cardError = WRONG_EXP_DATE;
	}
	else
	{
		int month = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
		int year =  (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
		if(year < 0 || year > 99 || month < 1 || month > 12)
		{
			cardError = WRONG_EXP_DATE;
		}
		else{
			cardError = CARD_OK;
		}
	}
	return cardError;
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	EN_cardError_t cardError;
	printf("Enter your Primary Account Number:\n");
	scanf("%s",cardData->primaryAccountNumber);
	int length = strlen(cardData->primaryAccountNumber);
	if(length > PANMAX || length< PANMIN || cardData->primaryAccountNumber == NULL)
	{
		cardError = WRONG_PAN;
	}
	else
	{
		for(int i = 0 ; i < length ; i ++)
		{
			if(cardData->primaryAccountNumber[i] < '0' || cardData->primaryAccountNumber[i] > '9')
			{
				return WRONG_PAN;
			}
		}
	}
	return cardError;
}