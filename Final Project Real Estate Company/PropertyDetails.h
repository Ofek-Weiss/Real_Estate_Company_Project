#ifndef __PROPERTY_DETAILS__
#define __PROPERTY_DETAILS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Address.h"
#include "GeneralFunctions.h"
#include "PropertyHistory.h"


typedef enum {
	ePrivateHouse, eApartment, eNumberOfPropertyTypes
}PropertyType;

static const char* PropertyTypeStrings[] = {
	"Private House","Apartment"
};

typedef enum {
	eSale, eRent, eNumberOfPropertyActions
}PropertyAction;

static const char* PropertyActionStrings[] = {
	"Sale","Rent"
};

typedef struct PropertyDetails {
	int propertyId;
	int available;
	int numOfrooms;
	int numOfBathrooms;
	int propertyArea;
	int price;
	PropertyType type;
	PropertyAction action;
	Address address;
	PropertyHistory history[10];
} PropertyDetails;

void init_property_details(PropertyDetails* details);
int get_property_history_count(PropertyDetails* details);
void freePropertyDetails(PropertyDetails* propertyDetails);
void printPropertyDetails(const void* val);


#endif // !__PROPERTY_DETAILS__