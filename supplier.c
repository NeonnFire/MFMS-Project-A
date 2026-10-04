#include "supplier.h"
#include "utils.h"
#include "file_storage.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int isBlank(const char *s)
{
    while (*s) {
        if (!isspace((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

static int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    if (at == NULL || at == email) return 0;      /* needs text before @ */
    const char *dot = strchr(at, '.');
    if (dot == NULL || dot == at + 1) return 0;   /* needs a dot after @ */
    if (dot[1] == '\0') return 0;                 /* needs text after dot */
    return 1;
}

static int isValidPhone(const char *phone)
{
    size_t i, len = strlen(phone);
    if (len < 7 || len > 15) return 0;
    for (i = 0; i < len; i++) {
        if (!isdigit((unsigned char)phone[i]) &&
            phone[i] != '+' && phone[i] != '-' && phone[i] != ' ')
            return 0;
    }
    return 1;
}
Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;

Supplier *findSupplierById(int id)
{
    int i;
    for (i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) return &suppliers[i];
    }
    return NULL;
}

void addSupplier(void)
{
    Supplier s;

    printHeader("SUPPLIER MANAGEMENT > ADD SUPPLIER");

    if (supplierCount >= MAX_SUPPLIERS) {
        printError("Supplier storage is full.");
        pauseScreen();
        return;
    }

       /* ID: keep asking until it is unique */
    while (1) {
        s.id = readInt("Supplier ID: ", 1, 999999);
        if (findSupplierById(s.id) == NULL) break;
        printError("That Supplier ID already exists.");
    }

    /* Name: must not be blank */
    do {
        readString("Supplier Name: ", s.name, sizeof(s.name));
        if (isBlank(s.name)) printError("Name cannot be empty.");
    } while (isBlank(s.name));

    /* Email: must look like an email */
    do {
        readString("Email: ", s.email, sizeof(s.email));
        if (!isValidEmail(s.email)) printError("Please enter a valid email (e.g. name@example.com).");
    } while (!isValidEmail(s.email));

    /* Telephone: digits, +, -, spaces only */
    do {
        readString("Telephone: ", s.telephone, sizeof(s.telephone));
        if (!isValidPhone(s.telephone)) printError("Please enter a valid phone number (7-15 characters).");
    } while (!isValidPhone(s.telephone));
    readString("Town/Location: ", s.location, sizeof(s.location));

    suppliers[supplierCount++] = s;
    saveAllData();
    printSuccess("Supplier added successfully.");
    pauseScreen();
}

void displaySuppliers(void)
{
    int i;

    printHeader("SUPPLIER MANAGEMENT > ALL SUPPLIERS");

    if (supplierCount == 0) {
        printWarning("No suppliers are registered.");
        pauseScreen();
        return;
    }

    printf("%-8s %-24s %-28s %-16s %-18s\n",
           "ID", "NAME", "EMAIL", "TELEPHONE", "LOCATION");
    printf("-----------------------------------------------------------------------------------------------\n");

    for (i = 0; i < supplierCount; i++) {
        printf("%-8d %-24s %-28s %-16s %-18s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].telephone,
               suppliers[i].location);
    }
    pauseScreen();
}

void searchSupplier(void)
{
    char keyword[80];
    int i, found = 0;

    printHeader("SUPPLIER MANAGEMENT > SEARCH");
    readString("Enter supplier name or location: ", keyword, sizeof(keyword));

    for (i = 0; i < supplierCount; i++) {
        if (containsIgnoreCase(suppliers[i].name, keyword) ||
            containsIgnoreCase(suppliers[i].location, keyword) ||
            containsIgnoreCase(suppliers[i].email, keyword)) {
            printf("ID: %d | Name: %s | Email: %s | Telephone: %s | Location: %s\n",
                   suppliers[i].id,
                   suppliers[i].name,
                   suppliers[i].email,
                   suppliers[i].telephone,
                   suppliers[i].location);
            found = 1;
        }
    }

    if (!found) printWarning("No matching supplier found.");
    pauseScreen();
}

void supplierMenu(void)
{
    int choice;

    do {
        printHeader("SUPPLIER MANAGEMENT");
        printf("[1] Add Supplier\n");
        printf("[2] Display Suppliers\n");
        printf("[3] Search Supplier\n");
        printf("[0] Back to Main Menu\n\n");

        choice = readInt("Enter your choice: ", 0, 3);
        switch (choice) {
            case 1: addSupplier(); break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier(); break;
            case 0: break;
        }
    } while (choice != 0);
}
