#include "budget.h"
#include "utils.h"
#include "file_storage.h"
#include <stdio.h>

Budget budgets[MAX_BUDGETS];
int budgetCount = 0;

static Budget *findBudgetById(int id)
{
    int i;
    for (i = 0; i < budgetCount; i++) {
        if (budgets[i].id == id) return &budgets[i];
    }
    return NULL;
}

double calculateRemainingBudget(const Budget *budget)
{
    if (budget == NULL) return 0.0;
    return budget->allocatedBudget - budget->expenditure;
}

void addBudget(void)
{
    Budget b;

    printHeader("BUDGET MANAGEMENT > ENTER DEPARTMENTAL BUDGET");

    if (budgetCount >= MAX_BUDGETS) {
        printError("Budget storage is full.");
        pauseScreen();
        return;
    }

    do {
        b.id = readInt("Budget ID: ", 1, 999999);
        if (findBudgetById(b.id) != NULL) printError("That Budget ID already exists.");
    } while (findBudgetById(b.id) != NULL);

    readString("Department: ", b.department, sizeof(b.department));
    b.allocatedBudget = readDouble("Allocated Budget (N$): ", 0.0, 100000000000.0);
    b.expenditure = 0.0;

    budgets[budgetCount++] = b;
    saveAllData();
    printSuccess("Departmental budget added successfully.");
    pauseScreen();
}

void displayBudgets(void)
{
    int i;
    double remaining;

    printHeader("BUDGET MANAGEMENT > ALL BUDGETS");

    if (budgetCount == 0) {
        printWarning("No budgets have been entered.");
        pauseScreen();
        return;
    }

    printf("%-8s %-20s %16s %16s %16s %-14s\n",
           "ID", "DEPARTMENT", "ALLOCATED", "EXPENDITURE", "REMAINING", "STATUS");
    printf("-------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < budgetCount; i++) {
        remaining = calculateRemainingBudget(&budgets[i]);
        printf("%-8d %-20s N$%13.2f N$%13.2f N$%13.2f %-14s\n",
               budgets[i].id,
               budgets[i].department,
               budgets[i].allocatedBudget,
               budgets[i].expenditure,
               remaining,
               budgets[i].expenditure <= budgets[i].allocatedBudget ? "WITHIN BUDGET" : "OVER BUDGET");
    }
    pauseScreen();
}

void recordExpenditure(void)
{
    int id;
    double amount;
    Budget *b;

    printHeader("BUDGET MANAGEMENT > RECORD EXPENDITURE");
    id = readInt("Budget ID: ", 1, 999999);
    b = findBudgetById(id);

    if (b == NULL) {
        printError("Budget not found.");
        pauseScreen();
        return;
    }

    amount = readDouble("Expenditure Amount (N$): ", 0.0, 100000000000.0);
    b->expenditure += amount;
    saveAllData();

    printf("\nDepartment: %s\n", b->department);
    printf("Total Expenditure: N$%.2f\n", b->expenditure);
    printf("Remaining Budget: N$%.2f\n", calculateRemainingBudget(b));

    if (b->expenditure <= b->allocatedBudget) {
        printSuccess("Expenditure is WITHIN BUDGET.");
    } else {
        printWarning("This department has EXCEEDED its allocated budget.");
    }
    pauseScreen();
}

void budgetSummary(void)
{
    int i, exceeded = 0;
    double totalAllocated = 0.0, totalExpenditure = 0.0;

    printHeader("BUDGET MANAGEMENT > SUMMARY");

    for (i = 0; i < budgetCount; i++) {
        totalAllocated += budgets[i].allocatedBudget;
        totalExpenditure += budgets[i].expenditure;
        if (budgets[i].expenditure > budgets[i].allocatedBudget) exceeded++;
    }

    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalExpenditure);
    printf("Total Remaining        : N$%.2f\n", totalAllocated - totalExpenditure);
    printf("Departments Over Budget: %d\n", exceeded);
    pauseScreen();
}

void budgetMenu(void)
{
    int choice;

    do {
        printHeader("BUDGET MANAGEMENT");
        printf("[1] Enter Departmental Budget\n");
        printf("[2] Display Budgets\n");
        printf("[3] Enter Expenditure\n");
        printf("[4] Budget Summary\n");
        printf("[0] Back to Main Menu\n\n");

        choice = readInt("Enter your choice: ", 0, 4);
        switch (choice) {
            case 1: addBudget(); break;
            case 2: displayBudgets(); break;
            case 3: recordExpenditure(); break;
            case 4: budgetSummary(); break;
            case 0: break;
        }
    } while (choice != 0);
}
