#ifndef __REALESTATECOMPANY__
#define __REALESTATECOMPANY__
#include "Address.h"
#include "Date.h"
#include "PropertyManager.h"
#include "GeneralFunctions.h"
#include "ListingAgent.h"
#include "Client.h"
#include "Transaction.h"
#include "ContactInformation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define isBudgetEnough(clientBudget, price) ((clientBudget) >= (price) ? 1 : 0)
#define isPropertySold(property) ((property)->available == 0)

#define DAY_MASK 0x1F         // 0000 0001 1111
#define MONTH_MASK 0x1E0      // 0001 1110 0000
#define YEAR_MASK 0x1FFE00    // 1 1111 1111 1110 0000 0000
#define DAY_SHIFT 0
#define MONTH_SHIFT 5
#define YEAR_SHIFT 9

typedef enum {

	SortBySeniority,
	SortBySalary,
	SortByName,
	NotSorted, 
	NumOfSortAgentTypes
}SortAgentType;

static const char* sortAgentTypeStr[NumOfSortAgentTypes] = {
	"Seniority",
	"Salary",
	"Name",
	"NotSorted"
};

typedef struct RealEstateCompany {
	char* name; //bullet 1.4 from the task
	ContactInformation* contactInformation; //bullet 1.7 from the task
	PropertyManager manager; //bullet 1.6 from the task
	ListingAgent** agents;//bullet 1.2 from the task
	int numOfAgents;
	Client** clients; //bullet 1.2 from the task
	int numOfClients;
	Transaction* transactions;
	int numOfTransactions;
	SortAgentType type;
} RealEstateCompany; //bullet 1.1 from the task

RealEstateCompany* loadRealEstateCompanyFromTextFile(const char* filename);
RealEstateCompany* loadRealEstateCompanyFromBinaryFile(const char* filename);
int saveRealEstateCompanyToTextFile(const char* filename, RealEstateCompany* company);
int saveRealEstateCompanyToBinaryFile(const char* filename, RealEstateCompany* company);
int addAgent(RealEstateCompany* company);
int addClient(RealEstateCompany* company);
int addTransaction(RealEstateCompany* company);
void sortAgents(RealEstateCompany* company);
void findAgent(RealEstateCompany* company);
void printCompany(const RealEstateCompany* company);
void freeCompany(RealEstateCompany* company);
void freeAgentArr(ListingAgent** arr, int size);
void freeClientArr(Client** arr, int size);
void extract_date(unsigned int compressed_date, int* day, int* month, int* year);
unsigned int compress_date(int day, int month, int year);
//creative methods...
void generateSummaryReport(RealEstateCompany* company);
void updatePropertyStatus(RealEstateCompany* company);

SortAgentType showSortMenu();


#endif // !__REALESTATECOMPANY__
