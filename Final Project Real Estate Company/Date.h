#ifndef __MYDATE__
#define __MYDATE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GeneralFunctions.h"
	

typedef struct {
	int day;
	int month;
	int year;
} Date;


void printDate(const Date* date);
void	getCorrectDate(Date* pDate);
int		checkDate(char* date, Date* pDate);
int		loadDateFromFile(Date* pDate, FILE* fp);

   
#endif // __MYDATE__