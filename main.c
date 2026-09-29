#include <stdio.h>
#include "utils.h"
#include "employee.h"
#include "budget.h"
#include "supplier.h"
#include "asset.h"
#include "reports.h"
#include "search.h"
#include "file_storage.h"

static void displayMainMenu(void)
{
    printHeader("MAIN MENU");
    printf("  [1] Employee Management\n");
    printf("  [2] Budget Management\n");
    printf("  [3] Supplier Management\n");
    printf("  [4] Asset Management\n");
    printf("  [5] Reports\n");
    printf("  [6] Global Search\n");
    printf("  [0] Exit\n\n");
}

int main(void)
{
    int choice;

    initConsole();
    loadAllData();

    do {
        displayMainMenu();
        choice = readInt("Enter your choice: ", 0, 6);

        switch (choice) {
            case 1: employeeMenu(); break;
            case 2: budgetMenu(); break;
            case 3: supplierMenu(); break;
            case 4: assetMenu(); break;
            case 5: reportsMenu(); break;
            case 6: searchMenu(); break;
            case 0:
                saveAllData();
                printSuccess("Data saved. Thank you for using MFMS.");
                break;
        }
    } while (choice != 0);

    return 0;
}
