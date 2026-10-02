# MUNICIPAL FINANCIAL MANAGEMENT SYSTEM (MFMS)

## PAP521S – Programming in Practice
### Project A: Municipal Financial Management System

**Programming Language:** ANSI C (C99)  
**Development Environment:** Visual Studio Code + GCC  
**Version Control:** Git & GitHub  
**Project Type:** Group Project  
**Project Stage:** Project A – Foundation System  
**Due Date:** 02 October 2026

---

## 1. Project Description

The Municipal Financial Management System (MFMS) is a menu-driven C application developed for a municipality. The purpose of Project A is to create a functional foundation system that demonstrates the C programming concepts covered during the first part of the PAP521S course.

The system focuses on employee management, basic municipal budget management, supplier management, asset management, searching and reports. The system uses arrays, strings, functions, conditions, loops and input validation to solve a realistic municipal management problem.

Project A is the foundation version of the system and can be extended and improved in Project B.

---

## 2. System Objectives

The system aims to:

- Provide a clear menu-driven municipal management application.
- Store and process employee information.
- Calculate employee salary information.
- Manage departmental budgets and expenditure.
- Maintain supplier information.
- Maintain a basic municipal asset register.
- Search for stored information.
- Produce basic management reports.
- Validate user input and prevent obviously invalid values.
- Demonstrate modular programming using multiple C source and header files.

---

## 3. System Features

### Employee Management

- Add an employee.
- Display all employees.
- Search for an employee.
- Calculate salary information.
- Store employee ID, name, department and salary information.
- Store housing and transport allowances.

### Budget Management

- Enter departmental budgets.
- Enter expenditure.
- Calculate remaining budget.
- Determine whether expenditure is within budget.
- Identify departments that have exceeded their allocated budget.
- Display budget information.

### Supplier Management

- Add suppliers.
- Display registered suppliers.
- Search for suppliers.
- Store supplier ID, name, email, telephone number and location.

### Asset Management

- Register municipal assets.
- Display assets.
- Search for assets.
- Store asset ID, asset name, type, purchase value, department and condition.

### Reports

- Employee report.
- Budget report.
- Supplier report.
- Asset report.
- Summary calculations such as employee counts, salary statistics, budget totals and expenditure.

### Global Search

The system provides a search facility for locating information across the main modules using text or IDs where applicable.

### File Storage

The application stores records in binary `.dat` files inside the `data` folder so that information can be loaded and used again when the program is restarted.

---

## 4. Project Structure

```text
MFMS_Project_A/
│
├── main.c
├── utils.c
├── utils.h
│
├── employee.c
├── employee.h
│
├── budget.c
├── budget.h
│
├── supplier.c
├── supplier.h
│
├── asset.c
├── asset.h
│
├── reports.c
├── reports.h
│
├── search.c
├── search.h
│
├── file_storage.c
├── file_storage.h
│
├── README.md
│
└── data/
    ├── employees.dat
    ├── budgets.dat
    ├── suppliers.dat
    └── assets.dat
```

---

## 5. Requirements

Before compiling the program, install:

- Windows 10/11
- Visual Studio Code
- GCC / MinGW-w64 (MSYS2 UCRT64 recommended)
- Git (for version control and GitHub collaboration)

Verify GCC in the VS Code terminal with:

```powershell
gcc --version
```

---

## 6. Compilation

Open the MFMS project folder in Visual Studio Code.

Open **Terminal → New Terminal** and compile all source files using:

```powershell
gcc -std=c99 -Wall -Wextra -pedantic main.c utils.c employee.c budget.c supplier.c asset.c reports.c search.c file_storage.c -o mfms.exe
```

If compilation is successful, `mfms.exe` will be created in the project folder.

---

## 7. Running the Program

Run the executable from the VS Code terminal:

```powershell
.\mfms.exe
```

The main menu will appear and allow the user to navigate through the system.

---

## 8. Input Validation

The system validates user input to reduce invalid data entry. Examples include:

- Negative salaries are rejected.
- Negative budgets are rejected.
- Invalid menu choices are handled.
- Empty names are handled appropriately.
- Invalid numerical input is detected where applicable.

---

## 9. C Programming Concepts Demonstrated

Project A demonstrates the following concepts from the PAP521S course:

- Variables and appropriate data types.
- Input and output.
- Arithmetic, relational and logical operators.
- `if`, `if-else` and `switch` statements.
- `for`, `while` and other appropriate loops.
- Arrays.
- Strings.
- Functions.
- Function parameters and return values.
- Modular program organisation.
- File handling.
- String functions such as `strlen()`, `strcmp()`, `strcpy()` and `strcat()` where appropriate.

---

## 10. Group Information

**Group Number:** [ENTER GROUP NUMBER]

### Group Members

| No. | Student Name | Student Number | Primary Responsibility |
|---|---|---|---|
| 1 | Omalu Chibuike | 223119059 | Employee Management |
| 2 | Peyelao Shafashike | 226167461 | Budget Management |
| 3 | Annacky Munyangalala | 226075028| Supplier Management |
| 4 | Roderick Dausab | 224031279 | Asset Management |
| 5 | [Student 5] | [Number] | Reports |
| 6 | [Student 6] | [Number] | Functions, Integration & Validation |
| 7 | Osakwe Nelson | 223119024 | Testing, Documentation & Git Coordination |


---

## 11. Individual Contribution

Each group member should maintain evidence of their own contribution, including:

- Code developed.
- Functions or modules developed.
- Testing performed.
- GitHub commits and other repository activity.
- Participation in the final demonstration.

---

## 12. GitHub

Initialise the repository from the MFMS project folder:

```bash
git init
git add .
git commit -m "Initial MFMS Project A"
git branch -M main
git remote add origin YOUR_GITHUB_REPOSITORY_URL
git push -u origin main
```

Each group member should make identifiable contributions to the repository rather than uploading the entire project through one final commit.

---

## 13. Basic Demonstration Checklist

During the demonstration, the group should be able to show:

1. Main menu navigation.
2. Employee management.
3. Budget management.
4. Supplier management.
5. Asset management.
6. Searching.
7. Reports.
8. Input validation.
9. Use of functions and modular source files.
10. GitHub repository and individual contributions.

---

## 14. Conclusion

The MFMS Project A provides a functional foundation for municipal financial management using ANSI C. It demonstrates the programming concepts covered during the first part of PAP521S while organising the application into logical modules. The system can be extended, refactored and improved in Project B.
