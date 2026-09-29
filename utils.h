#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void initConsole(void);
void clearScreen(void);
void pauseScreen(void);
void printHeader(const char *title);
void printSuccess(const char *message);
void printError(const char *message);
void printWarning(const char *message);
int readInt(const char *prompt, int min, int max);
double readDouble(const char *prompt, double min, double max);
void readString(const char *prompt, char *buffer, size_t size);
int containsIgnoreCase(const char *text, const char *keyword);

#endif
