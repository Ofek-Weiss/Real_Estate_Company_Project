#ifndef __CLIENT__
#define __CLIENT__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GeneralFunctions.h"


typedef struct {
	char* name;
	int budget;
} Client;

int isSameClient(Client** clients, int numClients, const char* name);
int chooseClient(const Client** clients, int numClients);
void printClient(void* pClinetPtr);
void freeClientPtr(void* pClientPtr);

#endif // !__CLIENT__
