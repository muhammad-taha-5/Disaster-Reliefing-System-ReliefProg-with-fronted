#ifndef UTILS_H
#define UTILS_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <windows.h>

using namespace std;

// Color Constants
const int C_DEFAULT = 7;
const int C_TITLE = 11;   // Cyan
const int C_MENU = 14;    // Yellow
const int C_SUCCESS = 10; // Light Green
const int C_ERROR = 12;   // Light Red
const int C_INFO = 13;    // Pink/Purple
const int C_PROMPT = 9;   // Bright Blue
const int C_WARNING = 6;  // Dark Yellow/Brown for warnings

inline void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline void showStartScreen() {
    system("cls");
    setColor(C_TITLE);
    cout << "==================================================" << endl;
    cout << "||   SMART DISASTER RELIEF RESPONSE SYSTEM      ||" << endl;
    cout << "==================================================" << endl;
    setColor(C_DEFAULT);
    cout << "\n[+] Initializing modules...\n[+] Loading regional data...\n[+] System Ready." << endl;
    cout << "\nPress Enter to enter Admin Portal...";
    cin.ignore(); cin.get();
    system("cls");
}

inline int stringToInt(const char* str) {
    if (!str) return 0;
    int res = 0;
    int sign = 1;
    int i = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n') i++;
    if (str[i] == '-') { sign = -1; i++; }
    for (; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + (str[i] - '0');
        else break;
    }
    return sign * res;
}

inline double stringToDouble(const char* str) {
    if (!str) return 0.0;
    double res = 0.0;
    int sign = 1;
    int i = 0;
    if (str[0] == '-') { sign = -1; i++; }
    for (; str[i] != '\0' && str[i] != '.'; ++i) {
        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + (str[i] - '0');
    }
    if (str[i] == '.') {
        double fraction = 0.1;
        i++;
        for (; str[i] != '\0'; ++i) {
            if (str[i] >= '0' && str[i] <= '9') {
                res += (str[i] - '0') * fraction;
                fraction *= 0.1;
            }
        }
    }
    return sign * res;
}

inline void encryptDecrypt(char* str) {
    if (!str) return;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 32 && str[i] <= 126) {
            str[i] = 158 - str[i];
        }
    }
}

#endif
