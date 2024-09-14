#ifndef __GENERALFUNCTIONS__
#define __GENERALFUNCTIONS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256
#define CLEAR_INPUT_BUFFER() do { \
    int c; \
    while ((c = getchar()) != '\n' && c != EOF); \
} while (0)


char* getStrExactName(const char* msg); // get input from the user with msg
char* myGets(char* buffer, int size, FILE* source); // 
char* getDynStr(char* str);
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);

void generalArrayFunction(void* arr, int size, int typeSize, void (*func)(void* element));



#endif
