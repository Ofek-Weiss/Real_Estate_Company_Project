#include "RealEstateCompany.h"
#include "PropertyDetails.h"
#include "CompanyFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int saveRealEstateCompanyToTextFile(const char* filename, RealEstateCompany* company) { // write the system to text file
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Unable to open file for writing");
        return 0;
    }

    if (!company) {
        fclose(file);
        return 0;
    }

    fprintf(file, "%s\n%s\n%s\n", company->name,company->contactInformation->email,company->contactInformation->phone);

    int count = getPropertyCount(&(company->manager));
    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++)
    {
        PropertyDetails* details = getPropertyByIndex(&company->manager, i);
        fprintf(file, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", details->propertyId, details->available, details->numOfrooms, details->numOfBathrooms,
            details->propertyArea, details->price, details->type, details->action);
        fprintf(file, "%s\n%d\n%s\n", details->address.street, details->address.propertyNumber, details->address.city);
        int history_count = get_property_history_count(details);
        fprintf(file, "%d\n", history_count);
        for (int j = 0; j < history_count; j++)
        {
            fprintf(file, "%d\n%d\n", details->history[j].year, details->history[j].price);
        }
    }

    fprintf(file,"%d\n", company->numOfAgents);
    for (int i = 0; i < company->numOfAgents; i++)
	{
		fprintf(file, "%s\n%d\n%d\n", company->agents[i]->name, company->agents[i]->seniority, company->agents[i]->salary);
	}
    fprintf(file, "%d\n", company->numOfClients);
    for (int i = 0; i < company->numOfClients; i++)
    {
		fprintf(file, "%s\n%d\n", company->clients[i]->name, company->clients[i]->budget);
    }
    fprintf(file, "%d\n", company->numOfTransactions);
    for (int i = 0; i < company->numOfTransactions; i++)
	{
		fprintf(file, "%s\n%d\n%d/%d/%d\n%s\n%d\n", company->transactions[i].agentName, company->transactions[i].propertyId, 
            company->transactions[i].date.day, company->transactions[i].date.month, company->transactions[i].date.year, company->transactions[i].clientName, company->transactions[i].soldFor);
	}
    fclose(file);
    return 1;
}


RealEstateCompany* loadRealEstateCompanyFromBinaryFile(const char* filename) // read the system from binary file
{
    FILE* fp;
    fp = fopen(filename, "rb");
    if (!fp)
    {
        printf("Error open company file\n");
        return 0;
    }
    RealEstateCompany* company = (RealEstateCompany*)malloc(sizeof(RealEstateCompany));

    if (!company) {
        fclose(fp);
        return NULL;
    }

    company->name = readStringFromFile(fp, "Error reading string\n");
    if (!company->name)
    {
        fclose(fp);
        return 0;
    }
    company->contactInformation = (ContactInformation*)malloc(sizeof(ContactInformation));
    if (!company->contactInformation)
    {
        free(company->name);
        fclose(fp);
        return 0;
    }
    strcpy(company->contactInformation->email, readStringFromFile(fp, "Error reading string\n"));
    if (!company->contactInformation->email)
    {
        free(company->name);
        fclose(fp);
        return 0;
    }
    strcpy(company->contactInformation->phone, readStringFromFile(fp, "Error reading string\n"));
    if (!company->contactInformation->phone)
    {
		free(company->name);
		fclose(fp);
		return 0;
    }


    company->type = NotSorted;
    int properties_count;
    if (!readIntFromFile(&properties_count, fp, "Error reading int\n"))
    {
        free(company->name);
        fclose(fp);
        return 0;
    }
    if (!L_init(&(company->manager.propertiesDetails)))
    {
        free(company->name);
        fclose(fp);
        return 0;
    }
    for (int i = 0; i < properties_count; i++)
    {

        PropertyDetails* details = (PropertyDetails*)malloc(sizeof(PropertyDetails));
        if (!readIntFromFile(&details->propertyId, fp, "Error reading int\n"))
        {
            free(company->name);
            fclose(fp);
            return 0;
        }
        if (!readIntFromFile(&details->available, fp, "Error reading int\n"))
        {
            free(company->name);
            fclose(fp);
            return 0;
        }
        if (!readIntFromFile(&details->numOfrooms, fp, "Error reading int\n"))
        {
            free(company->name);
            fclose(fp);
            return 0;
        }
        if (!readIntFromFile(&details->numOfBathrooms, fp, "Error reading int\n"))
        {
            free(company->name);
            fclose(fp);
            return 0;
        }
        if (!readIntFromFile(&details->propertyArea, fp, "Error reading int\n"))
        {
            free(company->name);
            fclose(fp);
            return 0;
        }

        if (!readIntFromFile(&details->price, fp, "Error reading int\n"))
        {
            free(company->name);
            fclose(fp);
            return 0;
        }
        if (!readIntFromFile((int*)&details->type, fp, "Error reading int\n"))
        {
            free(company->name);
            fclose(fp);
            return 0;
        }
        if (!readIntFromFile((int*)&details->action, fp, "Error reading int\n"))
        {
            free(company->name);
            fclose(fp);
            return 0;
        }

        Address address;
        init_addres(&address);

        address.street = readStringFromFile(fp, "Error reading string\n");
        if (!address.street)
        {
            fclose(fp);
            return 0;
        }
        if (!readIntFromFile(&address.propertyNumber, fp, "Error reading int\n"))
        {
            free(company->name);
            free(address.street);
            fclose(fp);
            return 0;
        }
        address.city = readStringFromFile(fp, "Error reading string\n");
        if (!address.city)
        {
            free(company->name);
            free(address.street);
            fclose(fp);
            return 0;
        }

        details->address = address;

        int historyCount;
        if (!readIntFromFile(&historyCount, fp, "Error reading int\n"))
        {
            free(company->name);
            free(address.street);
            free(address.city);
            fclose(fp);
            return 0;
        }
        init_property_details(details);

        for (int j = 0; j < historyCount; j++)
        {
            if (!readIntFromFile(&details->history[j].year, fp, "Error reading int\n"))
            {
                free(company->name);
                free(address.street);
                free(address.city);
                fclose(fp);
                return 0;
            }
            if (!readIntFromFile(&details->history[j].price, fp, "Error reading int\n"))
            {
                free(company->name);
                free(address.street);
                free(address.city);
                fclose(fp);
                return 0;
            }
        }
        L_insert((NODE*)&company->manager.propertiesDetails, details);//insert property
    }

    int agents_counts;
    if (!readIntFromFile(&agents_counts, fp, "Error reading int\n"))
    {
        free(company->name);
        fclose(fp);
        return 0;
    }
    company->agents = NULL;
    ListingAgent** LTemp = (ListingAgent**)realloc(company->agents, (agents_counts) * sizeof(ListingAgent*));
    if (LTemp == NULL)
    {
        free(company->name);
		fclose(fp);
		return 0;
    }
    company->agents = LTemp;
    for (int i = 0; i < agents_counts; i++)
    {
        company->agents[i] = (ListingAgent*)malloc(sizeof(ListingAgent));
        company->agents[i]->name = readStringFromFile(fp, "Error reading string\n");
        if (!company->agents[i]->name)
        {
            free(company->name);
            fclose(fp);
            return 0;
        }

        if (!readIntFromFile(&company->agents[i]->seniority, fp, "Error reading int\n") ||
            !readIntFromFile(&company->agents[i]->salary, fp, "Error reading int\n"))
        {
            free(company->name);
            fclose(fp);
            return 0;
        }
    }
    company->numOfAgents = agents_counts;

    int clients_count;
    if (!readIntFromFile(&clients_count, fp, "Error reading int\n"))
    {
        free(company->name);
        fclose(fp);
        return 0;
    }

    company->clients = NULL;
    Client** cTemp = (Client**)realloc(company->clients, (clients_count) * sizeof(Client*));
    if (cTemp == NULL)
	{
		free(company->name);
		fclose(fp);
		return 0;
	}
    company->clients = cTemp;
    for (int i = 0; i < clients_count; i++)
    {
        company->clients[i] = (Client*)malloc(sizeof(Client));
        if (company->clients[i] == NULL)
        {
            fclose(fp);
            return 0;
        }
        company->clients[i]->name = readStringFromFile(fp, "Error reading string\n");
        if (!company->clients[i]->name)
        {
            //TODO 
            fclose(fp);
            return 0;
        }
        if (!readIntFromFile(&company->clients[i]->budget, fp, "Error reading int\n"))
        {
            fclose(fp);
            return 0;
        }
    }

    company->numOfClients = clients_count;

    int transactions_counter;
    if (!readIntFromFile(&transactions_counter ,fp, "Error reading int\n"))
    {
        fclose(fp);
        return 0;
    }
    company->transactions = (Transaction*)malloc(sizeof(Transaction) * transactions_counter);
    if (company->transactions == NULL)
    {
        fclose(fp);
        return 0;
    }
    for (int i = 0; i < transactions_counter; i++)
    {
        strcpy(company->transactions[i].agentName, readStringFromFile(fp, "Error reading string\n"));
        if (!company->transactions[i].agentName)
        {
            //TODO 
            fclose(fp);
            return 0;
        }


        if (!readIntFromFile(&company->transactions[i].propertyId, fp, "Error reading int\n"))
        {
            fclose(fp);
            return 0;
        }
        unsigned int compressed_date;
        if (!readIntFromFile(&compressed_date, fp, "Error reading int\n"))
        {
            fclose(fp);
            return 0;
        }
        
        extract_date(compressed_date, &company->transactions[i].date.day, &company->transactions[i].date.month, &company->transactions[i].date.year);

        strcpy(company->transactions[i].clientName, readStringFromFile(fp, "Error reading string\n"));
        if (!company->transactions[i].clientName)
        {
            //TODO 
            fclose(fp);
            return 0;
        }
        if (!readIntFromFile(&company->transactions[i].soldFor, fp, "Error reading int\n"))
        {
            fclose(fp);
            return 0;
        }
    }
    company->numOfTransactions = transactions_counter;

    return company;
}


unsigned int compress_date(int day, int month, int year) { // compress the date
    return ((day) | (month << MONTH_SHIFT) | (year << YEAR_SHIFT)); 
}

void extract_date(unsigned int compressed_date, int* day, int* month, int* year) {
    *day = (compressed_date) & DAY_MASK;
    *month = (compressed_date >> MONTH_SHIFT) & 0b1111;
    *year = (compressed_date >> YEAR_SHIFT) & 0b1111111111111; // Extract 13 bits
}

int saveRealEstateCompanyToBinaryFile(const char* filename, RealEstateCompany* company) { // write the system to binary file
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Unable to open file for writing");
        return 0;
    }

    if (!company) {
        fclose(file);
        return 0;
    }

    if (!writeStringToFile(company->name, file, "Error write company name\n"))
    {
        fclose(file);
        return 0;
    }
    if (!writeStringToFile(company->contactInformation->email, file, "Error write email\n"))
	{
		fclose(file);
		return 0;
	}
    if (!writeStringToFile(company->contactInformation->phone, file, "Error write phone\n"))
    {
		fclose(file);
		return 0;
    }
    int count = getPropertyCount(&(company->manager));
    if (!writeIntToFile(count, file, "Error write int\n"))
    {
        fclose(file);
        return 0;
    }
    //PROPERTIES
    for (int i = 0; i < count; i++)
    {
        PropertyDetails* details = getPropertyByIndex(&company->manager, i);
        if (!writeIntToFile(details->propertyId, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(details->available, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(details->numOfrooms, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(details->numOfBathrooms, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(details->propertyArea, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(details->price, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(details->type, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(details->action, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeStringToFile(details->address.street, file, "Error write string\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(details->address.propertyNumber, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeStringToFile(details->address.city, file, "Error write string\n"))
        {
            fclose(file);
            return 0;
        }
        //HISTORY
        int history_count = get_property_history_count(details);
        if (!writeIntToFile(history_count, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }

        for (int j = 0; j < history_count; j++)
        {
            if (!writeIntToFile(details->history[j].year, file, "Error write int\n"))
            {
                fclose(file);
                return 0;
            }

            if (!writeIntToFile(details->history[j].price, file, "Error write int\n"))
            {
                fclose(file);
                return 0;
            }
        }
    }

    //AGENTS
    if (!writeIntToFile(company->numOfAgents, file, "Error write int\n"))
    {
        fclose(file);
        return 0;
    }
    for (int i = 0; i < company->numOfAgents; i++)
    {
        if (!writeStringToFile(company->agents[i]->name, file, "Error write string\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(company->agents[i]->seniority, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(company->agents[i]->salary, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
    }
    //CLIENTS
    if (!writeIntToFile(company->numOfClients, file, "Error write int\n"))
    {
        fclose(file);
        return 0;
    }
    
    for (int i = 0; i < company->numOfClients; i++)
    {
        if (!writeStringToFile(company->clients[i]->name, file, "Error write string\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(company->clients[i]->budget, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
    }
    if (!writeIntToFile(company->numOfTransactions, file, "Error write int\n"))
    {
        fclose(file);
        return 0;
    }
    //TRANSACTIONS
    for (int i = 0; i < company->numOfTransactions; i++)
    {
        if (!writeStringToFile(company->transactions[i].agentName, file, "Error write string\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(company->transactions[i].propertyId, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }

        unsigned int compressed_date = compress_date(company->transactions[i].date.day, company->transactions[i].date.month, company->transactions[i].date.year);
        if (!writeIntToFile(compressed_date, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeStringToFile(company->transactions[i].clientName, file, "Error write string\n"))
        {
            fclose(file);
            return 0;
        }
        if (!writeIntToFile(company->transactions[i].soldFor, file, "Error write int\n"))
        {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}


RealEstateCompany* loadRealEstateCompanyFromTextFile(const char* filename) { // read the system from text file
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file for reading");
        return NULL;
    }
    RealEstateCompany* company = (RealEstateCompany*)malloc(sizeof(RealEstateCompany));
    if (!company) {
        fclose(file);
        return NULL;
    }
    company->type = NotSorted;
    char buffer[MAX_STR_LEN];
    myGets(buffer, MAX_STR_LEN, file);
    company->name = _strdup(buffer);//company name
    
    company->contactInformation = (ContactInformation*)malloc(sizeof(ContactInformation));
    if (!company->contactInformation)
    {
        fclose(file);
        return NULL;
    }

    myGets(buffer, MAX_STR_LEN, file);
    strcpy(company->contactInformation->email, buffer);
    myGets(buffer, MAX_STR_LEN, file);
    strcpy(company->contactInformation->phone, buffer);
    myGets(buffer, MAX_STR_LEN, file);
    int properties_count = atoi(buffer);//properties count
    if (!L_init(&(company->manager.propertiesDetails)))
    {
        fclose(file);
        return NULL;
    }
    for (int i = 0; i < properties_count; i++)//read properties
    {
        PropertyDetails* details= (PropertyDetails*)malloc(sizeof(PropertyDetails));
        myGets(buffer, MAX_STR_LEN, file);
        details->propertyId = atoi(buffer);//property id
        myGets(buffer, MAX_STR_LEN, file);
        details->available = atoi(buffer);//available
        myGets(buffer, MAX_STR_LEN, file);
        details->numOfrooms = atoi(buffer);//num of rooms
        myGets(buffer, MAX_STR_LEN, file);
        details->numOfBathrooms = atoi(buffer);//num of bathrooms
        myGets(buffer, MAX_STR_LEN, file);
        details->propertyArea = atoi(buffer);//property area
        myGets(buffer, MAX_STR_LEN, file);
        details->price = atoi(buffer);//price
        myGets(buffer, MAX_STR_LEN, file);
        details->type = atoi(buffer);//type
        myGets(buffer, MAX_STR_LEN, file);
        details->action = atoi(buffer);//action
        
        Address address;
        init_addres(&address);

        myGets(buffer, MAX_STR_LEN, file);
        address.street = _strdup(buffer);//street
        myGets(buffer, MAX_STR_LEN, file);
        address.propertyNumber = atoi(buffer);//property number
        myGets(buffer, MAX_STR_LEN, file);
        address.city = _strdup(buffer);//city
        details->address = address;

        myGets(buffer, MAX_STR_LEN, file);
        int historyCount = atoi(buffer);//history count
        init_property_details(details);
        for (int j = 0; j < historyCount; j++)
        {
            myGets(buffer, MAX_STR_LEN, file);
            int year = atoi(buffer);//history year
            details->history[j].year = year;
            myGets(buffer, MAX_STR_LEN, file);
            int price = atoi(buffer);//history price
            details->history[j].price = price;
        }

        L_insert((NODE*)&company->manager.propertiesDetails, details);//insert property
        
    }

    //AGENTS , might do a function for this
    myGets(buffer, MAX_STR_LEN, file);
    int agents_counts = atoi(buffer);
    //company->agents = (ListingAgent**)malloc(sizeof(ListingAgent*)* agents_counts);
    company->agents = NULL;
    ListingAgent** tempA = (ListingAgent**)realloc(company->agents, (agents_counts) * sizeof(ListingAgent*));
    if (tempA == NULL)
    {
        fclose(file);
        return 0;
    }
    company->agents = tempA;
    for (int i = 0; i < agents_counts; i++)
    {
        company->agents[i] = (ListingAgent*)malloc(sizeof(ListingAgent));
        myGets(buffer, MAX_STR_LEN, file);
        company->agents[i]->name = _strdup(buffer);
        myGets(buffer, MAX_STR_LEN, file);
        company->agents[i]->seniority = atoi(buffer);
        myGets(buffer, MAX_STR_LEN, file);
        company->agents[i]->salary = atoi(buffer);
    }
    company->numOfAgents = agents_counts;

    //CLIENTS
    myGets(buffer, MAX_STR_LEN, file);
    int clients_count  = atoi(buffer);
    company->clients = NULL;
    Client** temp = realloc(company->clients, clients_count * sizeof(Client*));
    if (temp == NULL)
    {
        fclose(file);
        return 0;
    }
    company->clients = temp;
    for (int i = 0; i < clients_count; i++)
    {
        company->clients[i] = (Client*)malloc(sizeof(Client));
        if (company->clients[i] == NULL)
        {
            fclose(file);
            return 0;
        }
        myGets(buffer, MAX_STR_LEN, file);
        company->clients[i]->name = _strdup(buffer);
        myGets(buffer, MAX_STR_LEN, file);
        company->clients[i]->budget = atoi(buffer);
    }
    company->numOfClients = clients_count;

    //TRANSCTIONS 
    myGets(buffer, MAX_STR_LEN, file);
    int transactions_counter = atoi(buffer);
    company->transactions = (Transaction*)malloc(sizeof(Transaction) * transactions_counter);

    if (company->transactions == NULL)
    {
		fclose(file);
		return NULL;
    }

    for (int i = 0; i < transactions_counter; i++)
    {
        //read agent name
        myGets(buffer, MAX_STR_LEN, file);
        strcpy(company->transactions[i].agentName, buffer);
        //read property id
        myGets(buffer, MAX_STR_LEN, file);
        company->transactions[i].propertyId = atoi(buffer);
        //read date
        myGets(buffer, MAX_STR_LEN, file);
        sscanf(buffer, "%d/%d/%d", &(company->transactions[i].date.day), &(company->transactions[i].date.month), &(company->transactions[i].date.year));
        //read client name
        myGets(buffer, MAX_STR_LEN, file);
        strcpy(company->transactions[i].clientName, buffer);

        myGets(buffer, MAX_STR_LEN, file);
        company->transactions[i].soldFor = atoi(buffer);
    }
    company->numOfTransactions = transactions_counter;

    return company;
}


int addAgent(RealEstateCompany* company) // add agent to the company
{
	ListingAgent* agent = (ListingAgent*)malloc(sizeof(ListingAgent));
    if (!agent)
    {
        return 0;
    }
	agent->name = getStrExactName("Enter agent name: \n");
    if (!agent->name)
    {
        printf("No memory.\n");
        return 0;

    }
    if(isSameAgent(company->agents, company->numOfAgents, agent->name) == 0)
	{
        printf("Agent already exists.\n");
		free(agent);
		return 0;
	}
    printf("Enter agent seniority: \n");
    scanf("%d", &(agent->seniority));
    printf("Enter agent salary: \n");
	scanf("%d", &(agent->salary));////////////////clear input buffer???/
    CLEAR_INPUT_BUFFER();


    ListingAgent** temp = (ListingAgent**)realloc(company->agents, (company->numOfAgents + 1) * sizeof(ListingAgent*));
	if (!temp)
	{
		free(agent);
		return 0;
	}
    company->agents = temp;
	company->agents[company->numOfAgents] = agent;
	company->numOfAgents++;
    company->type = NotSorted;
	return 1;
    
}


int addClient(RealEstateCompany* company) // add client to the company
{
	Client* client = (Client*)malloc(sizeof(Client));
	if (!client)
	{
		return 0;
	}
	client->name = getStrExactName("Enter client name: \n");
	if(!client->name || isSameClient(company->clients, company->numOfClients, client->name) == 0)
	{
		free(client);
		return 0;
	}
	printf("Enter client budget: \n");
	scanf("%d", &client->budget);
    CLEAR_INPUT_BUFFER();

	Client** temp = (Client**)realloc(company->clients, (company->numOfClients + 1) * sizeof(Client*));
	if (!temp)
	{
		free(client);
		return 0;
	}
	company->clients = temp;
	company->clients[company->numOfClients] = client;
	company->numOfClients++;
	company->type = NotSorted;
	return 1;
}


int addTransaction(RealEstateCompany* company) // add transaction to the company
{
    if (company->numOfAgents == 0 || company->numOfClients == 0) {
        printf("No agents or clients available to make a transaction.\n");
        return 0;
    }
    if (company->manager.propertiesDetails.head.next == NULL) {
		printf("No properties available to make a transaction.\n");
		return 0;
	}
    company->transactions = NULL;
    Transaction* tTemp = (Transaction*)realloc(company->transactions, (company->numOfTransactions + 1) * sizeof(Transaction));
    if (!tTemp) {
		printf("Failed to allocate memory for the new transaction.\n");
		return 0;
	}
    company->transactions = tTemp;

    int agentIndex = chooseAgent(company->agents, company->numOfAgents);
    int clientIndex = chooseClient(company->clients, company->numOfClients);    
    int propertyIndex = choosePropertyIndex(&(company->manager));
    if (agentIndex == -1 || clientIndex == -1 || propertyIndex == -1) {
        // TODO ERROR
        printf("Failed to retrieve agent, client or property index.\n");
		return 0;
	}
    //Retrieve property and client details
    PropertyDetails* selectedProperty = getPropertyByIndex(&company->manager, propertyIndex);
    Client* selectedClient = company->clients[clientIndex];

    if (selectedProperty == NULL || selectedClient == NULL) {
        printf("Failed to retrieve property or client details.\n");
        return 0;
    }
    if (isPropertySold(selectedProperty))
	{
		printf("The property is not available.\n");
		return 0;
	}
    selectedProperty->available = 0;// the property is not available anymore
    // Check if the client can afford the property selectedClient->budget < selectedProperty->price
    if (!isBudgetEnough(selectedClient->budget, selectedProperty->price)) {
		printf("The client cannot afford the property.\n");
		return 0;
	}
    strcpy(company->transactions[company->numOfTransactions].agentName, company->agents[agentIndex]->name);//agent's name for the new transaction
    strcpy(company->transactions[company->numOfTransactions].clientName, selectedClient->name);//client's name for the new transaction
    company->transactions[company->numOfTransactions].propertyId = selectedProperty->propertyId;//property id for the new transaction
    company->transactions[company->numOfTransactions].soldFor = selectedProperty->price;//price that the house was sold for
    
    getCorrectDate(&company->transactions[company->numOfTransactions].date);
    
    company->numOfTransactions++;

    printf("Transaction added successfully.\n");
    return 1;
	
}

void sortAgents(RealEstateCompany* company) // sort agents by seniority, salary or name
{
    company->type = showSortMenu();
    int (*compareFunc)(const void* a1, const void* a2) = NULL;
    switch (company->type)
    {
        case SortBySeniority:
			compareFunc = compareAgentsBySeniority;
			break;
        case SortBySalary:
            compareFunc = compareAgentsBySalary;
            break;
        case SortByName:
            compareFunc = compareAgentsByName;
			break;
    }

    if (compareFunc != NULL)
	{
		qsort(company->agents, company->numOfAgents, sizeof(ListingAgent*), compareFunc);
	}
    printf("Agents sorted successfully.\n");

}

SortAgentType showSortMenu() // show the sort menu
{
	int choice;
	do
	{
		printf("Sort agents by:\n");
		for (int i = 0; i < NumOfSortAgentTypes - 1; i++)
		{
			printf("%d. %s\n", i + 1, sortAgentTypeStr[i]);
		}
		printf("Enter your choice: ");
		scanf("%d", &choice);
        CLEAR_INPUT_BUFFER();
		if (choice < 1 || choice > NumOfSortAgentTypes)
		{
			printf("Invalid choice. Please try again.\n");
		}
	} while (choice < 1 || choice > NumOfSortAgentTypes);
	return (SortAgentType)(choice - 1);
}

void findAgent(RealEstateCompany* company) // find agent by the sort type
{
    int (*compareFunc)(const void* a1, const void* a2) = NULL;
    switch(company->type)
	{
		case SortBySeniority:
			compareFunc = compareAgentsBySeniority;
			break;
		case SortBySalary:
			compareFunc = compareAgentsBySalary;
			break;
		case SortByName:
			compareFunc = compareAgentsByName;
			break;
	}

    if (compareFunc == NULL)
	{
		printf("Agents are not sorted, the search cannot be performed.\n");
		return;
	}
    else {
        ListingAgent key;
        ListingAgent* agent = &key;
        
        if (company->type == SortByName)
        {
            key.name = getStrExactName("Enter agent's name to search: \n");
        }
        else if(company->type == SortBySeniority)
        {
            printf("Enter agent's seniority to search: \n");
            scanf("%d", &key.seniority);
            CLEAR_INPUT_BUFFER();
        }
        else if (company->type == SortBySalary)
        {
            printf("Enter agent's salary to search: \n");
            scanf("%d", &key.salary);
            CLEAR_INPUT_BUFFER();
        }

        ListingAgent** pAgent = bsearch(&agent, company->agents, company->numOfAgents, sizeof(ListingAgent*), compareFunc);
        if (pAgent == NULL)
        {
            printf("Agent not found.\n");
        }
        else
        {
            printf("Agent found.\n");
            printAgent(pAgent);
        }

    }
}

void generateSummaryReport(RealEstateCompany* company) // generate a summary report for the company
{
    int totalProperties = 0, soldProperties = 0;
    double totalRevenue = 0, averagePrice = 0;

    NODE* current = company->manager.propertiesDetails.head.next;
    while (current != NULL)
    {
        PropertyDetails* pd = (PropertyDetails*)current->key;
        totalProperties++;
        totalRevenue += pd->price;
        if (isPropertySold(pd))
		{
			soldProperties++;
		}
		current = current->next;
    }
    if (totalProperties > 0)
    {
		averagePrice = totalRevenue / totalProperties;
    }
    printf("Summary Report:\n");
    printf("Total Properties: %d\n", totalProperties);
    printf("Sold Properties: %d\n", soldProperties);
    printf("Available Properties: %d\n", totalProperties - soldProperties);
    printf("Total Revenue from Sold Properties: $%.2f\n", totalRevenue);
    printf("Average Property Price: $%.2f\n", averagePrice);
}

void updatePropertyStatus(RealEstateCompany* company) // update the property status (cost and availability)
{
    int propertyIndex, newStatus, newPrice;
	propertyIndex = choosePropertyIndex(&(company->manager));
	if (propertyIndex == -1)
	{
		printf("Failed to retrieve property index.\n");
		return;
	}
	PropertyDetails* selectedProperty = getPropertyByIndex(&company->manager, propertyIndex);
	if (selectedProperty == NULL)
	{
		printf("Failed to retrieve property details.\n");
		return;
	}
	
    printf("Enter new status (1 - available, 0 - sold): ");
    scanf("%d", &newStatus);
    printf("Enter new listing price: ");
    scanf("%d", &newPrice);
    CLEAR_INPUT_BUFFER();
    selectedProperty->available = newStatus;
    selectedProperty->price = newPrice;
    printf("Property status updated successfully.\n");

}


void printCompany(const RealEstateCompany* company)
{
    printf("Company name: %s\n", company->name);
    printf("\n");
    printf("Contact Information:\n");
    printf("Email: %s\n", company->contactInformation->email);
    printf("Phone: %s\n", company->contactInformation->phone);
    printf("\n");
    printf("Number of agents: %d\n", company->numOfAgents);
    generalArrayFunction(company->agents, company->numOfAgents, sizeof(ListingAgent*), printAgent);
	printf("Number of clients: %d\n", company->numOfClients);
	generalArrayFunction(company->clients, company->numOfClients, sizeof(Client*), printClient);
	printf("Number of transactions: %d\n", company->numOfTransactions);
	generalArrayFunction(company->transactions, company->numOfTransactions, sizeof(Transaction), printTransaction); 
}

void freeCompany(RealEstateCompany* company)
{
	free(company->name);
    free(company->contactInformation);
	freeAgentArr(company->agents, company->numOfAgents);
	freeClientArr(company->clients, company->numOfClients);
    L_free(&company->manager.propertiesDetails, freePropertyDetails);
	free(company->transactions);
	free(company);
}

void	freeAgentArr(ListingAgent** arr, int size)
{
    generalArrayFunction(arr, size, sizeof(ListingAgent*), freeAgentPtr);
}

void	freeClientArr(Client** arr, int size)
{
    generalArrayFunction(arr, size, sizeof(Client*), freeClientPtr);
}