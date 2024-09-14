#include <stdio.h>
#include <string.h>
#include "ContactInformation.h"
#include <stdlib.h>
#include "GeneralFunctions.h"

void init_contact_information(ContactInformation* contactInformation)
{
	contactInformation->email[0] = '\0';
	contactInformation->phone[0] = '\0';
}