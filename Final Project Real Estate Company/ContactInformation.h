#ifndef __CONTACT_INFORMATION_H__
#define __CONTACT_INFORMATION_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GeneralFunctions.h"


typedef struct {
	char email[MAX_STR_LEN];
	char phone[MAX_STR_LEN];
} ContactInformation;

void init_contact_information(ContactInformation* contactInformation);

#endif // __CONTACT_INFORMATION_H__