#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int valid_number(AddressBook *addressBook, char *str1) {
    if (strlen(str1) != 10) {
        printf("Please enter 10 digits.\n ");
        return 0;
    }
    for (int i = 0; i < strlen(str1); i++) {
        if (!isdigit(str1[i])) {
            printf("Invalid number. \n");
            return 0;
        }
    }
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, str1) == 0) {
            printf("Number already exists.\n ");
            return 0;
        }
    }
    return 1;
}

int valid_email(AddressBook *addressBook, char *str2) {
    for (int i = 0; i < strlen(str2); i++) {
        if (str2[i] >= 'A' && str2[i] <= 'Z') {
            printf("Invalid email. Capital letters are not allowed.\n");
            return 0;
        }
    }

    if (strstr(str2, "@") == NULL || strstr(str2, ".com") == NULL) {
        printf("Invalid email.\n");
        return 0;
    }

    if (strchr(str2, ' ') != NULL) {
        printf("Invalid email. No spaces are allowed.\n");
        return 0;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, str2) == 0) {
            printf("Email already exists.\n");
            return 0;
        }
    }

    return 1;  // Return 1 after successful validation
}



// Define a comparison function for sorting contacts by name
int compareByName(const void * a, const void * b) {
  return strcmp(((Contact * ) a) -> name, ((Contact * ) b) -> name);
}

// Define a comparison function for sorting contacts by phone number
int compareByPhone(const void * a, const void * b) {
  return strcmp(((Contact * ) a) -> phone, ((Contact * ) b) -> phone);
}

// Define a comparison function for sorting contacts by email
int compareByEmail(const void * a, const void * b) {
  return strcmp(((Contact * ) a) -> email, ((Contact * ) b) -> email);
}

void listContacts(AddressBook * addressBook, int sortCriteria) {
  if (addressBook -> contactCount == 0)
    printf("No contacts in address book.\n");
  else {
    switch (sortCriteria) {
      case 1:
      qsort(addressBook->contacts, addressBook->contactCount, sizeof(Contact), compareByName);
      case 2:
      qsort(addressBook->contacts, addressBook->contactCount, sizeof(Contact), compareByPhone);
      case 3:
      qsort(addressBook->contacts, addressBook->contactCount, sizeof(Contact), compareByEmail);
    }

    // Sort contacts based on the chosen criteria
    for (int i = 0; i < addressBook -> contactCount; i++) {
      printf("Name: %s,phone: %s,Email: %s\n",(addressBook -> contacts[i].name),(addressBook -> contacts[i].phone),( addressBook -> contacts[i].email));
    }
  }
}

void initialize(AddressBook * addressBook) {
  addressBook->contacts=malloc(MAX_CONTACTS * sizeof(Contact));
  addressBook -> contactCount = 0;
  populateAddressBook(addressBook);
  // Load contacts from file during initialization (After files)
  loadContactsFromFile(addressBook);
  //printf("%d", addressBook->contactCount);
}

void saveAndExit(AddressBook * addressBook) {
  saveContactsToFile(addressBook); // Save contacts to file
  exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook * addressBook) {
  if (addressBook -> contactCount >= MAX_CONTACTS) {
    printf("Address book is full. Cannot add more contacts.\n");
    return;
  }
  
  printf("Enter the name of the contact: ");
  scanf(" %[^\n]", addressBook -> contacts[addressBook -> contactCount].name);

  while(1)
  {
  printf("Enter the phone number of the contact: ");
  scanf(" %[^\n]", addressBook -> contacts[addressBook -> contactCount].phone);
  char str1[11];
  strcpy(str1, addressBook -> contacts[addressBook -> contactCount].phone);

if(valid_number(addressBook, addressBook -> contacts[addressBook -> contactCount].phone))
 break;
}
  while(1)
  {
    printf("Enter the email of the contact: ");
  scanf(" %[^\n]", addressBook -> contacts[addressBook -> contactCount].email);
  if(valid_email(addressBook, addressBook -> contacts[addressBook -> contactCount].email))
  break;
  }
  addressBook -> contactCount++;
  printf("Contact saved successfully\n");
  }

void searchContact(AddressBook * addressBook) {
  /* Define the logic for search */
  printf("Enter the name of the contact: ");
  char searchName[50];
  int contactFound = 0;
  scanf(" %[^\n]", searchName);
  for (int i = 0; i < addressBook -> contactCount; i++) {
    if (strcmp(searchName, addressBook -> contacts[i].name) == 0) {
      contactFound = 1;
      printf("%s %s %s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone,
        addressBook -> contacts[i].email);
    }
  }
  if (!contactFound) {
        printf("Contact not found. Please try again.\n");
    }
}

void editContact(AddressBook * addressBook) {
    printf("Enter the name of the contact: ");
    char searchName[50];
    scanf(" %[^\n]", searchName);
    int contactFound = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(searchName, addressBook->contacts[i].name) == 0) {
            contactFound = 1;

            while (1) {
                printf("Select the editing mode\n");
                printf("1. Edit by name\n");
                printf("2. Edit by phone\n");
                printf("3. Edit by email\n");
                printf("Enter your choice: ");
                int choice;
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        printf("Enter the new name: ");
                        scanf(" %[^\n]", addressBook->contacts[i].name);
                        printf("Contact edited successfully\n");
                        return;
                    case 2:
                        while (1) {
                            printf("Enter the new phone number: ");
                            scanf(" %[^\n]", addressBook->contacts[i].phone);
                            
                            if (valid_number(addressBook, addressBook->contacts[i].phone)) {
                                printf("Contact edited successfully\n");
                                return;
                            }
                        }
                    case 3:
                        while (1) {
                            printf("Enter the new email: ");
                            scanf(" %[^\n]", addressBook->contacts[i].email);
                            if (valid_email(addressBook, addressBook->contacts[i].email)) {
                                printf("Contact edited successfully\n");
                                return;
                            }
                        }
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            }
        }
    }

    if (!contactFound) {
        printf("Contact not found. Please try again.\n");
    }
}

void deleteContact(AddressBook * addressBook) {
  /* Define the logic for deletecontact */
  printf("Enter the name of the contact: ");
  char deleteName[50];
  scanf(" %[^\n]", deleteName);
  for (int i = 0; i < addressBook -> contactCount; i++) {
    if (strcmp(deleteName, addressBook -> contacts[i].name) == 0) {
      for (i = i; i < addressBook -> contactCount; i++) {
        addressBook -> contacts[i] = addressBook -> contacts[i + 1];
      }
      addressBook -> contactCount--;
    }
  }
  printf("Contact deleted successfully\n");
}
