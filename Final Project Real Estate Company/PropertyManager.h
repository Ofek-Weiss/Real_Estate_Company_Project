#ifndef __PROPERTY_MANAGER__
#define __PROPERTY_MANAGER__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "PropertyDetails.h"
#include "GeneralFunctions.h"
#include "def.h"


typedef enum {

	SortByPrice,
	SortByArea,
	SortByRooms,
	NofTypes
}PropertySortType;

static const char* PropertySortTypeStrings[] = {
	"Price",
	"Area",
	"Rooms"
};

typedef struct PropertyManager {
	LIST propertiesDetails;//bullet 1.8 from the task
} PropertyManager;

int choosePropertyIndex(PropertyManager* manager);
PropertyDetails* getPropertyByIndex(PropertyManager* manager, int index);
int getPropertyCount(const PropertyManager* manager);
void printProperties(const PropertyManager* manager);
int addProperty(PropertyManager* manager);
int checkPropertyId(LIST* properties, int id);

#endif // !__PROPERTY_MANAGER__