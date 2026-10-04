#ifndef BUDGET_H
#define BUDGET_H

#define MAX_BUDGETS 100

typedef struct {
    int id;
    char department[50];
    double allocatedBudget;
    double expenditure;
} Budget;

extern Budget budgets[MAX_BUDGETS];
extern int budgetCount;

double calculateRemainingBudget(const Budget *budget);
double calculateBudgetUtilization(const Budget *budget);
void budgetMenu(void);
void addBudget(void);
void displayBudgets(void);
void recordExpenditure(void);
void budgetSummary(void);

#endif
