#include "file_storage.h"
#include "employee.h"
#include "budget.h"
#include "supplier.h"
#include "asset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define MAKE_DIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#define MAKE_DIR(path) mkdir(path, 0777)
#endif

static void ensureDataDirectory(void)
{
    FILE *test = fopen("data", "rb");
    if (test != NULL) {
        fclose(test);
        return;
    }
    MAKE_DIR("data");
}

static void saveRecords(const char *filename, const void *data, int count, size_t recordSize)
{
    FILE *file;

    file = fopen(filename, "wb");
    if (file == NULL) return;

    fwrite(&count, sizeof(count), 1, file);
    if (count > 0) fwrite(data, recordSize, (size_t)count, file);
    fclose(file);
}

static int loadRecords(const char *filename, void *data, int maxCount, size_t recordSize)
{
    FILE *file;
    int count = 0;

    file = fopen(filename, "rb");
    if (file == NULL) return 0;

    if (fread(&count, sizeof(count), 1, file) != 1 || count < 0 || count > maxCount) {
        fclose(file);
        return 0;
    }

    if (count > 0 && fread(data, recordSize, (size_t)count, file) != (size_t)count) {
        fclose(file);
        return 0;
    }

    fclose(file);
    return count;
}

void saveAllData(void)
{
    ensureDataDirectory();
    saveRecords("data/employees.dat", employees, employeeCount, sizeof(Employee));
    saveRecords("data/budgets.dat", budgets, budgetCount, sizeof(Budget));
    saveRecords("data/suppliers.dat", suppliers, supplierCount, sizeof(Supplier));
    saveRecords("data/assets.dat", assets, assetCount, sizeof(Asset));
}

void loadAllData(void)
{
    ensureDataDirectory();
    employeeCount = loadRecords("data/employees.dat", employees, MAX_EMPLOYEES, sizeof(Employee));
    budgetCount = loadRecords("data/budgets.dat", budgets, MAX_BUDGETS, sizeof(Budget));
    supplierCount = loadRecords("data/suppliers.dat", suppliers, MAX_SUPPLIERS, sizeof(Supplier));
    assetCount = loadRecords("data/assets.dat", assets, MAX_ASSETS, sizeof(Asset));
}
