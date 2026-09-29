#ifndef ASSET_H
#define ASSET_H

#define MAX_ASSETS 100

typedef struct {
    int id;
    char name[80];
    char type[40];
    double purchaseValue;
    char department[50];
    char condition[30];
} Asset;

extern Asset assets[MAX_ASSETS];
extern int assetCount;

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);
Asset *findAssetById(int id);

#endif
