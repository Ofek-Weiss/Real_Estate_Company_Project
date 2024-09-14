#ifndef __TRANSACTION__
#define __TRANSACTION__


#include "ListingAgent.h"
#include "Date.h"
#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Transaction {
	char agentName[MAX_STR_LEN];//bullet 1.5 from the task
	int propertyId;
	Date date;
	char clientName[MAX_STR_LEN];
	int soldFor;
} Transaction;

void printTransaction(const Transaction* transaction);


#endif // __TRANSACTION__
