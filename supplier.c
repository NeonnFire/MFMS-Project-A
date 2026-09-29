#include "supplier.h"
#include "utils.h"
#include "file_storage.h"
#include <stdio.h>

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

    do {
        s.id = readInt("Supplier ID: ", 1, 999999);
        if (findSupplierById(s.id) != NULL) printError("That Supplier ID already exists.");
    } while (findSupplierById(s.id) != NULL);

    readString("Supplier Name: ", s.name, sizeof(s.name));
    readString("Email: ", s.email, sizeof(s.email));
    readString("Telephone: ", s.telephone, sizeof(s.telephone));
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
