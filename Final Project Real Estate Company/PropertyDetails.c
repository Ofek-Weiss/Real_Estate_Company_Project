#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "GeneralFunctions.h"
#include "PropertyDetails.h"


void init_property_details(PropertyDetails* details)
{
	for (int i = 0; i < 10; i++)
	{
		details->history[i].price = -1;
	}
}

int get_property_history_count(PropertyDetails* details) // counts the history of the property
{
	for (int i = 0; i < 10; i++)
	{
		if (details->history[i].price == -1)
		{
			return i;
		}
	}
	return 10;
}

void printPropertyDetails(const void* val) // prints the property details
{
	const PropertyDetails* details = (const PropertyDetails*)val;
	printf("Property ID: %d\n", details->propertyId);
	printf("Available: %s\n", details->available ? "Yes" : "No");
	printf("Number of rooms: %d\n", details->numOfrooms);
	printf("Number of bathrooms: %d\n", details->numOfBathrooms);
	printf("Property area: %d\n", details->propertyArea);
	printf("Price: %d\n", details->price);
	printf("Property type: %s\n", PropertyTypeStrings[details->type]);
	printf("Property action: %s\n", PropertyActionStrings[details->action]);
	printf("Address: %s\n", details->address.street);
	printf("City: %s\n", details->address.city);
	printf("History:\n");
	for (int i = 0; i < 10; i++)
	{
		if (details->history[i].price != -1)
		{
			printf("Price: %d\n", details->history[i].price);
			printf("Date: %d\n", details->history[i].year);
		}
	}
	printf("\n");
}




// dumb function - there is no memory to free in PropertyDetails
// this functions is defined so it will be able to use L_free
void freePropertyDetails(PropertyDetails* propertyDetails)
{

}

