#ifndef __ADDRESS_H__
#define __ADDRESS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GeneralFunctions.h"


typedef struct {
	char* street;
	int propertyNumber;
	char* city;
} Address;

void init_addres(Address* address);

#endif // __ADDRESS_H__