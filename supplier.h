#ifndef SUPPLIER_H
#define SUPPLIER_H

#define MAX_SUPPLIERS 100

typedef struct {
    int id;
    char name[80];
    char email[80];
    char telephone[30];
    char location[50];
} Supplier;

extern Supplier suppliers[MAX_SUPPLIERS];
extern int supplierCount;

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
Supplier *findSupplierById(int id);

#endif
