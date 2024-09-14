#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GeneralFunctions.h"
#include "PropertyManager.h"
#include "RealEstateCompany.h"
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define COMPANY_FILE_TEXT "REMAX.txt"
#define COMPANY_FILE_BINARY "REMAX.bin"



int main() {

#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


    int fileChoice;
    RealEstateCompany* company = NULL;
    do {
        printf("Please choose 0 to load the real estate company data from a text file or 1 to load it from a binary file\n");
        scanf("%d", &fileChoice);
        CLEAR_INPUT_BUFFER();
        
        if (fileChoice == 0)
        {
            company = loadRealEstateCompanyFromTextFile(COMPANY_FILE_TEXT);
            if (company == NULL) {
                fprintf(stderr, "Failed to load the real estate company data.\n");
                return 0;
            }
        }
        else if (fileChoice == 1)
        {
            company = loadRealEstateCompanyFromBinaryFile(COMPANY_FILE_BINARY);
            if (company == NULL) {
                fprintf(stderr, "Failed to load the real estate company data.\n");
                return 0;
            }
        }
        else
        {
            printf("Invalid choice\n");
        }
    }while(fileChoice != 0 && fileChoice != 1);
    if (company == NULL)
    {
        printf("Error\n");
        return;
    }
    
   int choice;
   int stop = 0;
   do
   {
       printf("Please choose an option:\n");
       printf("0 - Print Company\n");
       printf("1 - Print Properties\n");
       printf("2 - Add a new Agent\n");
       printf("3 - Add a new Client\n");
       printf("4 - Make a new Transaction\n");
       printf("5 - Add property\n");
       printf("6 - Sort Agents\n");
       printf("7 - Find Agent\n");
       printf("8 - Generate Summary Report\n");
       printf("9 - Update Property Status\n");
       printf("10 - Exit\n");
       scanf("%d", &choice);
       CLEAR_INPUT_BUFFER();
       switch (choice)
       {
       case 0:
            printCompany(company); // print company (agents,clients,transactions)
		    printf("\n");
		    break;
	   case 1:
		    printProperties(&(company->manager)); // print all properties
            printf("\n");
		    break;
        case 2:
            addAgent(company); // add a new agent
            printf("\n");
            break;
        case 3:
            addClient(company); // add a new client
			printf("\n");
			break;
        case 4:
            addTransaction(company);
            printf("\n");
            break;
        case 5:
            addProperty(&(company->manager));
            printf("\n");
            break;
        case 6:
			sortAgents(company);
			printf("\n");
			break;
        case 7: 
			findAgent(company);
            printf("\n");
            break;
        case 8:
            generateSummaryReport(company);
			printf("\n");
			break;
        case 9:
			updatePropertyStatus(company);
            printf("\n");
			break;
        case 10:
			stop = 1;
			break;
		default:
			printf("Invalid choice\n");
			break;
       }
   } while (!stop);

    saveRealEstateCompanyToTextFile(COMPANY_FILE_TEXT, company); // save company to text file
    saveRealEstateCompanyToBinaryFile(COMPANY_FILE_BINARY, company); // save company to binary file
   
    freeCompany(company); // free company memory before exit the program


#ifdef _DEBUG
    _CrtDumpMemoryLeaks(); // check for memory leaks
#endif
	
	return 1;
}



