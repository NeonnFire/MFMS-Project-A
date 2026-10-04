#include "search.h"
#include "employee.h"
#include "budget.h"
#include "supplier.h"
#include "asset.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

void searchMenu(void)
{
    char keyword[80];
    int i, matches;
    char idText[30];

    printHeader("GLOBAL SEARCH");
    readString("Enter a name, department, supplier, asset or ID keyword: ", keyword, sizeof(keyword));

    matches = 0;

    printf("\n--- EMPLOYEES ---\n");
    for (i = 0; i < employeeCount; i++) {
        snprintf(idText, sizeof(idText), "%d", employees[i].id);
        if (containsIgnoreCase(employees[i].name, keyword) ||
            containsIgnoreCase(employees[i].department, keyword) ||
            containsIgnoreCase(idText, keyword)) {
            printf("Employee %d: %s | %s\n", employees[i].id, employees[i].name, employees[i].department);
            matches++;
        }
    }

    printf("\n--- BUDGETS ---\n");
    for (i = 0; i < budgetCount; i++) {
        snprintf(idText, sizeof(idText), "%d", budgets[i].id);
        if (containsIgnoreCase(budgets[i].department, keyword) ||
            containsIgnoreCase(idText, keyword)) {
            printf("Budget %d: %s | Allocated N$%.2f | Spent N$%.2f\n",
                   budgets[i].id, budgets[i].department, budgets[i].allocatedBudget, budgets[i].expenditure);
            matches++;
        }
    }

    printf("\n--- SUPPLIERS ---\n");
    for (i = 0; i < supplierCount; i++) {
        snprintf(idText, sizeof(idText), "%d", suppliers[i].id);
        if (containsIgnoreCase(suppliers[i].name, keyword) ||
            containsIgnoreCase(suppliers[i].location, keyword) ||
            containsIgnoreCase(suppliers[i].email, keyword) ||
            containsIgnoreCase(suppliers[i].telephone, keyword) ||
            containsIgnoreCase(idText, keyword)) {
            printf("Supplier %d: %s | %s | %s | %s\n", suppliers[i].id, suppliers[i].name, suppliers[i].email, suppliers[i].telephone, suppliers[i].location);
            matches++;
        }
    }

    printf("\n--- ASSETS ---\n");
    for (i = 0; i < assetCount; i++) {
        snprintf(idText, sizeof(idText), "%d", assets[i].id);
        if (containsIgnoreCase(assets[i].name, keyword) ||
            containsIgnoreCase(assets[i].type, keyword) ||
            containsIgnoreCase(assets[i].department, keyword) ||
            containsIgnoreCase(assets[i].condition, keyword) ||
            containsIgnoreCase(idText, keyword)) {
            printf("Asset %d: %s | %s | %s | Condition: %s\n", assets[i].id, assets[i].name, assets[i].type, assets[i].department, assets[i].condition);
            matches++;
        }
    }

    if (matches == 0) {
        printWarning("No records matched your search.");
    } else {
        printf("\n%d matching record(s) found.\n", matches);
    }
    pauseScreen();
}
