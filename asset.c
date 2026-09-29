#include "asset.h"
#include "utils.h"
#include "file_storage.h"
#include <stdio.h>

Asset assets[MAX_ASSETS];
int assetCount = 0;

Asset *findAssetById(int id)
{
    int i;
    for (i = 0; i < assetCount; i++) {
        if (assets[i].id == id) return &assets[i];
    }
    return NULL;
}

void addAsset(void)
{
    Asset a;

    printHeader("ASSET MANAGEMENT > ADD ASSET");

    if (assetCount >= MAX_ASSETS) {
        printError("Asset storage is full.");
        pauseScreen();
        return;
    }

    do {
        a.id = readInt("Asset ID: ", 1, 999999);
        if (findAssetById(a.id) != NULL) printError("That Asset ID already exists.");
    } while (findAssetById(a.id) != NULL);

    readString("Asset Name: ", a.name, sizeof(a.name));
    readString("Asset Type: ", a.type, sizeof(a.type));
    a.purchaseValue = readDouble("Purchase Value (N$): ", 0.0, 100000000000.0);
    readString("Department: ", a.department, sizeof(a.department));
    readString("Condition: ", a.condition, sizeof(a.condition));

    assets[assetCount++] = a;
    saveAllData();
    printSuccess("Asset registered successfully.");
    pauseScreen();
}

void displayAssets(void)
{
    int i;

    printHeader("ASSET MANAGEMENT > ASSET REGISTER");

    if (assetCount == 0) {
        printWarning("No assets are registered.");
        pauseScreen();
        return;
    }

    printf("%-7s %-20s %-14s %15s %-16s %-14s\n",
           "ID", "NAME", "TYPE", "VALUE", "DEPARTMENT", "CONDITION");
    printf("--------------------------------------------------------------------------------------\n");

    for (i = 0; i < assetCount; i++) {
        printf("%-7d %-20s %-14s N$%11.2f %-16s %-14s\n",
               assets[i].id,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }
    pauseScreen();
}

void searchAsset(void)
{
    char keyword[80];
    int i, found = 0;

    printHeader("ASSET MANAGEMENT > SEARCH");
    readString("Enter asset name, type or department: ", keyword, sizeof(keyword));

    for (i = 0; i < assetCount; i++) {
        if (containsIgnoreCase(assets[i].name, keyword) ||
            containsIgnoreCase(assets[i].type, keyword) ||
            containsIgnoreCase(assets[i].department, keyword)) {
            printf("ID: %d | %s | Type: %s | Value: N$%.2f | Department: %s | Condition: %s\n",
                   assets[i].id,
                   assets[i].name,
                   assets[i].type,
                   assets[i].purchaseValue,
                   assets[i].department,
                   assets[i].condition);
            found = 1;
        }
    }

    if (!found) printWarning("No matching asset found.");
    pauseScreen();
}

void assetMenu(void)
{
    int choice;

    do {
        printHeader("ASSET MANAGEMENT");
        printf("[1] Add Asset\n");
        printf("[2] Display Assets\n");
        printf("[3] Search Asset\n");
        printf("[0] Back to Main Menu\n\n");

        choice = readInt("Enter your choice: ", 0, 3);
        switch (choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 0: break;
        }
    } while (choice != 0);
}
