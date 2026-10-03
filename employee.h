#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX_EMPLOYEES 100

typedef struct
{
    int id;
    char name[80];
    char department[50];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
} Employee;

extern Employee employees[MAX_EMPLOYEES];
extern int employeeCount;

void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void calculateSalary(void);

Employee *findEmployeeById(int id);

#endif