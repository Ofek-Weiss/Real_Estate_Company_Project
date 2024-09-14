#ifndef __LISTINGAGENT__
#define __LISTINGAGENT__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListingAgent {
	char* name;
	int seniority;
	int salary;
} ListingAgent;


int isSameAgent(ListingAgent** agents, int numAgents, const char* name);
int chooseAgent(const ListingAgent** agents, int numAgents);
int compareAgentsBySeniority(const void* agent1, const void* agent2);
int compareAgentsBySalary(const void* agent1, const void* agent2);
int compareAgentsByName(const void* agent1, const void* agent2);
void printAgent(void* pAgentPtr);
void freeAgentPtr(void* pAgentPtr);

#endif // !__LISTINGAGENT__
