#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "GeneralFunctions.h"
#include "Client.h"


int isSameClient(Client** clients, int numClients, const char* name) {
	for (int i = 0; i < numClients; i++) {
		if (strcmp(clients[i]->name, name) == 0) {
			return 0;//found a client with the same name
		}
	}
	return 1;//no client with the same name
}

int chooseClient(const Client** clients, int numClients)
{
	if(numClients == 0)
	{
		printf("No clients available\n");
		return -1;
	}

	for (int i = 0; i < numClients; i++)
	{
		printf("%d. %s\n", i + 1, clients[i]->name);
	}
	int choice;
	do
	{
		printf("Choose a client: ");
		scanf("%d", &choice);
		CLEAR_INPUT_BUFFER();
		if(choice < 1 || choice > numClients)
		{
			printf("Invalid choice. Please try again\n");
		}
	} while (choice < 1 || choice > numClients);

	return choice - 1;
}

void printClient(void* pClientPtr)
{
	const Client* temp = *(Client**)pClientPtr;
	printf("Client name: %s\n", temp->name);
	printf("Client budget: %d\n", temp->budget);
	printf("\n");
}

void	freeClientPtr(void* pClientPtr)
{
	Client* temp = *(Client**)pClientPtr;
	free(temp->name);
	free(temp);
}


