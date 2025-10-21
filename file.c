#include <stdio.h>
#include "contact.h"
#include "file.h"

    
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    addressBook->contactCount = 0;

    while (fscanf(file, "%[^,],%[^,],%s\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3) {
        addressBook->contactCount++;

        // Ensure you don't exceed the array bounds
        if (addressBook->contactCount >= MAX_CONTACTS) {
            break;
        }
    }

    fclose(file);
}


void saveContactsToFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file);
}
