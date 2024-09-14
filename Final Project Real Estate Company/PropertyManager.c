#include "PropertyManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int choosePropertyIndex(PropertyManager* manager) // get property index from the user
{
	if(!manager->propertiesDetails.head.next)
	{
		printf("No properties to choose from.\n");
		return 0;
	}
	int choice;
	int count = 1;
	NODE* current = manager->propertiesDetails.head.next;
	PropertyDetails* propertyTemp;
	do {
		printf("Choose a property:\n");
		//////////maybe change to do while
		while (current) {
			propertyTemp = (PropertyDetails*)current->key;
			printf("%d: %s %d, %s, Price: $%d\n", count, propertyTemp->address.street, propertyTemp->address.propertyNumber, propertyTemp->address.city, propertyTemp->price);
			current = current->next;
			count++;
		}
		scanf("%d", &choice);
		while (getchar() != '\n');//////clear buffer
		if (choice < 1 || choice >= count)
		{
			printf("Invalid choice.\n");
		}
	} while (choice < 1 || choice >= count);
	
	return choice - 1;

}

PropertyDetails* getPropertyByIndex(PropertyManager* manager, int index) // get property from the user
{
	NODE* current = manager->propertiesDetails.head.next;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}
	if (current == NULL)
	{
		printf("Index out of bounds: No such property exists.\n");
		return NULL; 
	}
	return (PropertyDetails*)current->key;
}

int getPropertyCount(const PropertyManager* manager) // counts the properties
{
	int count = 0;
	NODE* pN = manager->propertiesDetails.head.next; //first Node

	while (pN != NULL)
	{
		count++;
		pN = pN->next;
	}
	return count;
}

void printProperties(const PropertyManager* manager)
{
	int count = getPropertyCount(manager);
	printf("There are %d properties: \n", count);
	L_print((LIST*)&manager->propertiesDetails, printPropertyDetails);
}

int addProperty(PropertyManager* manager)
{
	PropertyDetails* newProperty = (PropertyDetails*)calloc(1,sizeof(PropertyDetails));
	if(!newProperty)
	{
		printf("Memory allocation failed.\n");
		return 0;
	}
	printf("Enter the property ID (number): \n");//check if ID already exists/////////////
	scanf("%d", &newProperty->propertyId);
	CLEAR_INPUT_BUFFER();
	int idExists = checkPropertyId(&manager->propertiesDetails, newProperty->propertyId);///is the & needed?
	if(idExists == 0)
	{
		printf("Property ID already exists.\n");
		free(newProperty);
		return 0;
	}
	newProperty->available = 1;//available
	printf("Enter the number of rooms: \n");
	scanf("%d", &newProperty->numOfrooms);
	CLEAR_INPUT_BUFFER();
	printf("Enter the number of bathrooms: \n");
	scanf("%d", &newProperty->numOfBathrooms);
	CLEAR_INPUT_BUFFER();
	printf("Enter the property area: \n");
	scanf("%d", &newProperty->propertyArea);
	CLEAR_INPUT_BUFFER();
	printf("Enter the price: \n");
	scanf("%d", &newProperty->price);
	CLEAR_INPUT_BUFFER();
	printf("Enter the property type (0 - House, 1 - Apartment): \n");
	scanf("%d", &newProperty->type);
	CLEAR_INPUT_BUFFER();
	printf("Enter the property action (0 - Sale, 1 - Rent): \n");
	scanf("%d", &newProperty->action);
	CLEAR_INPUT_BUFFER();
	printf("Enter the property address: \n");
	newProperty->address.street = getStrExactName("Enter the street name: \n");
	printf("Enter the property number: \n");
	scanf("%d", &newProperty->address.propertyNumber);
	CLEAR_INPUT_BUFFER();
	newProperty->address.city = getStrExactName("Enter the city name: \n"); 
	init_property_details(newProperty);
	L_insert((NODE*)&manager->propertiesDetails, newProperty);
	return 1;

}

int checkPropertyId(LIST* properties, int id)
{
	NODE* current = properties->head.next;
	PropertyDetails* propertyTemp;
	while (current)
	{
		propertyTemp = (PropertyDetails*)current->key;
		if (propertyTemp->propertyId == id)
		{
			return 0;
		}
		current = current->next;
	}
	return 1;
}


