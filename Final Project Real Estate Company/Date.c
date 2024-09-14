#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Date.h"

const int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; // days in 12 months of the year
#define SPECIAL_CHAR '/'

void printDate(const Date* date)
{
	printf("%d%c%d%c%d\n", date->day, SPECIAL_CHAR, date->month, SPECIAL_CHAR, date->year);
}

void getCorrectDate(Date* pDate)
{
	char date[256];
	int ok = 1;

	do {
		printf("Enter Transaction Date dd%cmm%cyyyy\t",
			SPECIAL_CHAR, SPECIAL_CHAR);
		myGets(date, MAX_STR_LEN, stdin);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}

int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 10)
		return 0;
	if ((date[2] != SPECIAL_CHAR) || (date[5] != SPECIAL_CHAR))
		return 0;
	sscanf(date, "%d%*c%d%*c%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12)
		return 0;

	if (day > daysInMonth[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

int		loadDateFromFile(Date* pDate, FILE* fp)
{
	if (fread(pDate, sizeof(Date), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}

	return 1;

}


