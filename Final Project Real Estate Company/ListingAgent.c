
#include <ctype.h>
#include "GeneralFunctions.h"
#include "ListingAgent.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int isSameAgent(ListingAgent** agents, int numAgents, const char* name) { // check if the agent name is already exist
	for (int i = 0; i < numAgents; i++) {
		if (_stricmp(agents[i]->name, name) == 0) {
			return 0;//found an agent with the same name
		}
	}
	return 1;//no agent with the same name
}

int chooseAgent(const ListingAgent** agents, int numAgents) // get the agent from the user
{
	if(numAgents == 0)
	{
		printf("No agents available\n");
		return -1;
	}

	for (int i = 0; i < numAgents; i++)
	{
		printf("%d. %s\n", i + 1, agents[i]->name);
	}
	int choice;
	do
	{
		printf("Choose an agent: ");
		scanf("%d", &choice);
		CLEAR_INPUT_BUFFER();
		if(choice < 1 || choice > numAgents)
		{
			printf("Invalid choice. Please try again\n");
		}
	} while (choice < 1 || choice > numAgents);

	return choice - 1;
}

int compareAgentsBySeniority(const void* agent1, const void* agent2) // compare the agents by seniority
{
	const ListingAgent* a1 = *(ListingAgent**)agent1;
	const ListingAgent* a2 = *(ListingAgent**)agent2;
	return a1->seniority - a2->seniority;
}

int compareAgentsBySalary(const void* agent1, const void* agent2) // compare the agents by salary
{
	const ListingAgent* a1 = *(ListingAgent**)agent1;
	const ListingAgent* a2 = *(ListingAgent**)agent2;
	return a1->salary - a2->salary;
}

int compareAgentsByName(const void* agent1, const void* agent2) // compare the agents by name
{
	const ListingAgent* a1 = *(ListingAgent**)agent1;
	const ListingAgent* a2 = *(ListingAgent**)agent2;
	return strcmp(a1->name, a2->name);
}

void printAgent(void *pAgentPtr)
{
	const ListingAgent* temp = *(ListingAgent**)pAgentPtr;
	printf("Name: %s\n", temp->name);
	printf("Seniority: %d\n", temp->seniority);
	printf("Salary: %d\n", temp->salary);
	printf("\n");
}

void	freeAgentPtr(void* pAgentPtr)
{
	ListingAgent* temp = *(ListingAgent**)pAgentPtr;
	free(temp->name);
	free(temp);
}