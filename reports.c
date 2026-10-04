#include "reports.h"
#include "employee.h"
#include "budget.h"
#include "supplier.h"
#include "asset.h"
#include "utils.h"
#include <stdio.h>

/* Employee Report */
void employeeReport(void)
{
    int i;
    int highestIndex = 0;
    int lowestIndex = 0;

    double totalSalary = 0.0;
    double average = 0.0;

    printHeader("REPORTS > EMPLOYEE REPORT");

    if (employeeCount == 0) {
        printWarning("No employee data available.");
        pauseScreen();
        return;
    }

    for (i = 0; i < employeeCount; i++) {
        double salary = employees[i].basicSalary
                      + employees[i].housingAllowance
                      + employees[i].transportAllowance;

        double highestSalary = employees[highestIndex].basicSalary
                             + employees[highestIndex].housingAllowance
                             + employees[highestIndex].transportAllowance;

        double lowestSalary = employees[lowestIndex].basicSalary
                            + employees[lowestIndex].housingAllowance
                            + employees[lowestIndex].transportAllowance;

        totalSalary += salary;

        if (salary > highestSalary) {
            highestIndex = i;
        }

        if (salary < lowestSalary) {
            lowestIndex = i;
        }
    }

    average = totalSalary / employeeCount;

    printf("Total Employees : %d\n", employeeCount);
    printf("Average Salary  : N$%.2f\n", average);

    printf("Highest Salary  : N$%.2f (%s)\n",
           employees[highestIndex].basicSalary
           + employees[highestIndex].housingAllowance
           + employees[highestIndex].transportAllowance,
           employees[highestIndex].name);

    printf("Lowest Salary   : N$%.2f (%s)\n",
           employees[lowestIndex].basicSalary
           + employees[lowestIndex].housingAllowance
           + employees[lowestIndex].transportAllowance,
           employees[lowestIndex].name);

    pauseScreen();
}

/* Budget Report */
void budgetReport(void)
{
    int i;
    int exceeded = 0;

    double allocated = 0.0;
    double expenditure = 0.0;

    printHeader("REPORTS > BUDGET REPORT");

    if (budgetCount == 0) {
        printWarning("No budget data available.");
        pauseScreen();
        return;
    }

    for (i = 0; i < budgetCount; i++) {
        allocated += budgets[i].allocatedBudget;
        expenditure += budgets[i].expenditure;

        if (budgets[i].expenditure > budgets[i].allocatedBudget) {
            exceeded++;
        }
    }

    printf("Total Allocated Budget : N$%.2f\n", allocated);
    printf("Total Expenditure      : N$%.2f\n", expenditure);
    printf("Remaining Budget       : N$%.2f\n", allocated - expenditure);
    printf("Departments Over Budget: %d\n\n", exceeded);

    if (exceeded > 0) {
        printf("Departments exceeding budget:\n");

        for (i = 0; i < budgetCount; i++) {
            if (budgets[i].expenditure > budgets[i].allocatedBudget) {
                printf("- %s (Over by N$%.2f)\n",
                       budgets[i].department,
                       budgets[i].expenditure
                       - budgets[i].allocatedBudget);
            }
        }
    }

    pauseScreen();
}

/* Supplier Report */
void supplierReport(void)
{
    int i;

    printHeader("REPORTS > SUPPLIER REPORT");

    if (supplierCount == 0) {
        printWarning("No supplier data available.");
        pauseScreen();
        return;
    }

    printf("Registered Suppliers: %d\n\n", supplierCount);

    for (i = 0; i < supplierCount; i++) {
        printf("%d. %s | %s | %s | %s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].telephone,
               suppliers[i].location);
    }

    pauseScreen();
}

/* Asset Report */
void assetReport(void)
{
    int i;
    double totalValue = 0.0;

    printHeader("REPORTS > ASSET REPORT");

    if (assetCount == 0) {
        printWarning("No asset data available.");
        pauseScreen();
        return;
    }

    for (i = 0; i < assetCount; i++) {
        totalValue += assets[i].purchaseValue;
    }

    printf("Registered Assets: %d\n", assetCount);
    printf("Total Asset Value: N$%.2f\n\n", totalValue);

    for (i = 0; i < assetCount; i++) {
        printf("%d. %s | %s | N$%.2f | %s | %s\n",
               assets[i].id,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }

    pauseScreen();
}

/* Municipal Summary Report */
void displayAllReports(void)
{
    int i;

    double totalSalary = 0.0;
    double totalAllocated = 0.0;
    double totalExpenditure = 0.0;
    double totalAssets = 0.0;

    printHeader("REPORTS > MUNICIPAL SUMMARY");

    for (i = 0; i < employeeCount; i++) {
        totalSalary += employees[i].basicSalary
                     + employees[i].housingAllowance
                     + employees[i].transportAllowance;
    }

    for (i = 0; i < budgetCount; i++) {
        totalAllocated += budgets[i].allocatedBudget;
        totalExpenditure += budgets[i].expenditure;
    }

    for (i = 0; i < assetCount; i++) {
        totalAssets += assets[i].purchaseValue;
    }

    printf("EMPLOYEES\n");
    printf("  Total Employees        : %d\n", employeeCount);
    printf("  Total Salary Value     : N$%.2f\n\n", totalSalary);

    printf("BUDGETS\n");
    printf("  Total Allocated        : N$%.2f\n", totalAllocated);
    printf("  Total Expenditure      : N$%.2f\n", totalExpenditure);
    printf("  Total Remaining        : N$%.2f\n\n",
           totalAllocated - totalExpenditure);

    printf("SUPPLIERS\n");
    printf("  Registered Suppliers   : %d\n\n", supplierCount);

    printf("ASSETS\n");
    printf("  Registered Assets      : %d\n", assetCount);
    printf("  Total Asset Value      : N$%.2f\n", totalAssets);

    pauseScreen();
}

/* Reports Menu */
void reportsMenu(void)
{
    int choice;

    do {
        printHeader("REPORTS");

        printf("[1] Employee Report\n");
        printf("[2] Budget Report\n");
        printf("[3] Supplier Report\n");
        printf("[4] Asset Report\n");
        printf("[5] Municipal Summary Report\n");
        printf("[0] Back to Main Menu\n\n");

        choice = readInt("Enter your choice: ", 0, 5);

        switch (choice) {
            case 1:
                employeeReport();
                break;

            case 2:
                budgetReport();
                break;

            case 3:
                supplierReport();
                break;

            case 4:
                assetReport();
                break;

            case 5:
                displayAllReports();
                break;

            case 0:
                break;
        }

    } while (choice != 0);
}