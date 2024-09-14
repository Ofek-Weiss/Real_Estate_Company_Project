#include "Transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void printTransaction(const Transaction* transaction)
{
	printf("Agent name: %s\n", transaction->agentName);
	printf("Property id: %d\n", transaction->propertyId);
	printf("Date: ");
	printDate(&transaction->date);
	printf("Client name: %s\n", transaction->clientName);
	printf("Sold for: %d\n", transaction->soldFor);
	printf("\n");
}
