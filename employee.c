#include "employee.h"
#include "utils.h"
#include "file_storage.h"

#include <stdio.h>
#include <string.h>

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

/* Find an employee using their ID */
Employee *findEmployeeById(int id)
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (employees[i].id == id)
        {
            return &employees[i];
        }
    }

    return NULL;
}

/* Add a new employee */
void addEmployee(void)
{
    Employee e;
    char message[120];

    printHeader("EMPLOYEE MANAGEMENT > ADD EMPLOYEE");

    /* Check whether employee storage is full */
    if (employeeCount >= MAX_EMPLOYEES)
    {
        printError("Employee storage is full.");
        pauseScreen();
        return;
    }

    /* Get a unique employee ID */
    do
    {
        e.id = readInt("Employee ID: ", 1, 999999);

        if (findEmployeeById(e.id) != NULL)
        {
            printError("That Employee ID already exists.");
        }

    } while (findEmployeeById(e.id) != NULL);

    /* Get employee information */
    readString("Employee Name: ", e.name, sizeof(e.name));

    readString("Department: ", e.department, sizeof(e.department));

    e.basicSalary = readDouble(
        "Basic Salary (N$): ",
        0.0,
        1000000000.0
    );

    e.housingAllowance = readDouble(
        "Housing Allowance (N$): ",
        0.0,
        1000000000.0
    );

    e.transportAllowance = readDouble(
        "Transport Allowance (N$): ",
        0.0,
        1000000000.0
    );

    /* Store the employee */
    employees[employeeCount] = e;
    employeeCount++;

    /* Save data to file */
    saveAllData();

    /* Display success message */
    strcpy(message, "Employee added successfully: ");
    strcat(message, e.name);

    printSuccess(message);
    pauseScreen();
}

/* Display all employees */
void displayEmployees(void)
{
    int i;

    printHeader("EMPLOYEE MANAGEMENT > ALL EMPLOYEES");

    if (employeeCount == 0)
    {
        printWarning("No employees are registered.");
        pauseScreen();
        return;
    }

    printf("%-8s %-26s %-18s %15s\n",
           "ID",
           "NAME",
           "DEPARTMENT",
           "BASIC SALARY");

    printf("--------------------------------\n");

    for (i = 0; i < employeeCount; i++)
    {
        printf("%-8d %-26s %-18s N$%12.2f\n",
               employees[i].id,
               employees[i].name,
               employees[i].department,
               employees[i].basicSalary);
    }

    printf("\nTotal Employees: %d\n", employeeCount);

    pauseScreen();
}

/* Search for an employee */
void searchEmployee(void)
{
    char keyword[80];
    int i;
    int found = 0;

    printHeader("EMPLOYEE MANAGEMENT > SEARCH");

    readString(
        "Enter employee name or department: ",
        keyword,
        sizeof(keyword)
    );

    for (i = 0; i < employeeCount; i++)
    {
        if (containsIgnoreCase(employees[i].name, keyword) ||
            containsIgnoreCase(employees[i].department, keyword))
        {
            printf(
                "ID: %d | Name: %s | Department: %s | Basic Salary: N$%.2f\n",
                employees[i].id,
                employees[i].name,
                employees[i].department,
                employees[i].basicSalary
            );

            found = 1;
        }
    }

    if (!found)
    {
        printWarning("No matching employee found.");
    }

    pauseScreen();
}

/* Calculate an employee's total salary */
void calculateSalary(void)
{
    int id;
    Employee *e;
    double gross;

    printHeader("EMPLOYEE MANAGEMENT > SALARY CALCULATION");

    id = readInt("Employee ID: ", 1, 999999);

    e = findEmployeeById(id);

    if (e == NULL)
    {
        printError("Employee not found.");
        pauseScreen();
        return;
    }

    /* Calculate total salary */
    gross = e->basicSalary
          + e->housingAllowance
          + e->transportAllowance;

    printf("\n");
    printf("Employee          : %s\n", e->name);
    printf("Department        : %s\n", e->department);
    printf("Basic Salary      : N$%.2f\n", e->basicSalary);
    printf("Housing Allowance : N$%.2f\n", e->housingAllowance);
    printf("Transport Allow.  : N$%.2f\n", e->transportAllowance);

    printf("-----------------------\n");

    printf("Total Salary      : N$%.2f\n", gross);

    pauseScreen();
}

/* Employee management menu */
void employeeMenu(void)
{
    int choice;

    do
    {
        printHeader("EMPLOYEE MANAGEMENT");

        printf("[1] Add Employee\n");
        printf("[2] Display Employees\n");
        printf("[3] Search Employee\n");
        printf("[4] Calculate Salary\n");
        printf("[0] Back to Main Menu\n\n");

        choice = readInt(
            "Enter your choice: ",
            0,
            4
        );

        switch (choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                calculateSalary();
                break;

            case 0:
                break;
        }

    } while (choice != 0);
}