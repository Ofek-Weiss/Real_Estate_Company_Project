
#include <stdio.h>
#include <string.h>
#include "Address.h"
#include <stdlib.h>
#include "GeneralFunctions.h"

void init_addres(Address* address)
{
	address->city = NULL;
	address->propertyNumber = -1;
	address->street = NULL;
}