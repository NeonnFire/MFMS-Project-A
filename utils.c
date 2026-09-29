#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define RESET "\033[0m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

static void trimNewline(char *text)
{
    size_t len = strlen(text);
    while (len > 0 && (text[len - 1] == '\n' || text[len - 1] == '\r')) {
        text[--len] = '\0';
    }
}

#ifdef _WIN32
void initConsole(void)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &mode)) {
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, mode);
    }
}
#else
void initConsole(void) { }
#endif

void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen(void)
{
    char buffer[8];
    printf("\nPress ENTER to continue...");
    fgets(buffer, sizeof(buffer), stdin);
}

void printHeader(const char *title)
{
    clearScreen();
    printf(CYAN "============================================================\n" RESET);
    printf(CYAN "                 MUNICIPAL FINANCIAL\n" RESET);
    printf(CYAN "                   MANAGEMENT SYSTEM\n" RESET);
    printf(CYAN "============================================================\n" RESET);
    printf(BLUE "  %s\n" RESET, title);
    printf(CYAN "------------------------------------------------------------\n" RESET);
}

void printSuccess(const char *message)
{
    printf(GREEN "[SUCCESS] %s\n" RESET, message);
}

void printError(const char *message)
{
    printf(RED "[ERROR] %s\n" RESET, message);
}

void printWarning(const char *message)
{
    printf(YELLOW "[WARNING] %s\n" RESET, message);
}

int readInt(const char *prompt, int min, int max)
{
    char buffer[100];
    char *end;
    long value;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        trimNewline(buffer);
        errno = 0;
        end = NULL;
        value = strtol(buffer, &end, 10);

        while (end && isspace((unsigned char)*end)) {
            end++;
        }

        if (buffer[0] == '\0' || end == buffer || *end != '\0' ||
            errno == ERANGE || value < min || value > max || value < INT_MIN || value > INT_MAX) {
            printError("Enter a valid whole number within the allowed range.");
            continue;
        }

        return (int)value;
    }
}

double readDouble(const char *prompt, double min, double max)
{
    char buffer[100];
    char *end;
    double value;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        trimNewline(buffer);
        errno = 0;
        end = NULL;
        value = strtod(buffer, &end);

        while (end && isspace((unsigned char)*end)) {
            end++;
        }

        if (buffer[0] == '\0' || end == buffer || *end != '\0' ||
            errno == ERANGE || value != value || value < min || value > max || value > DBL_MAX) {
            printError("Enter a valid number within the allowed range.");
            continue;
        }

        return value;
    }
}

void readString(const char *prompt, char *buffer, size_t size)
{
    if (size == 0) return;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        if (strchr(buffer, '\n') == NULL) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { }
        }

        trimNewline(buffer);

        if (strlen(buffer) == 0) {
            printError("This field cannot be empty.");
            continue;
        }
        return;
    }
}

int containsIgnoreCase(const char *text, const char *keyword)
{
    size_t textLen, keyLen, i, j;

    if (text == NULL || keyword == NULL) return 0;
    textLen = strlen(text);
    keyLen = strlen(keyword);
    if (keyLen == 0) return 1;
    if (keyLen > textLen) return 0;

    for (i = 0; i <= textLen - keyLen; i++) {
        for (j = 0; j < keyLen; j++) {
            if (tolower((unsigned char)text[i + j]) != tolower((unsigned char)keyword[j])) {
                break;
            }
        }
        if (j == keyLen) return 1;
    }
    return 0;
}
