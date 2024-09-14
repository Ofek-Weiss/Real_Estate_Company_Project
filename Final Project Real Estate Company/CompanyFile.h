#ifndef __COMPANY_FILE__
#define __COMPANY_FILE__


#include "RealEstateCompany.h"
#include "GeneralFunctions.h"
#include "PropertyManager.h"
#include <stdio.h>


int	 writeStringToFile(const char* str, FILE* fp, const char* msg);
int	 writeCharsToFile(const char* arr, int size, FILE* fp, const char* msg);
int	 writeIntToFile(int val, FILE* fp, const char* msg);


char* readStringFromFile(FILE* fp, const char* msg);
char* readDynStringFromTextFile(FILE* fp);
int		readFixSizeStrFromFile(char* arr, FILE* fp, const char* msg);
int		readCharsFromFile(char* arr, int size, FILE* fp, const char* msg);
int		readIntFromFile(int* val, FILE* fp, const char* msg);

#endif