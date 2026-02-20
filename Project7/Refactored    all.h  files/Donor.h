#ifndef DONOR_H
#define DONOR_H

#include "Utils.h"

class Donor {
private:
    char name[100];
    char donorID[20];
    double amount;
    char date[20];

public:
    Donor(const char* n, const char* id, double amt, const char* d) {
        strcpy(name, n);
        strcpy(donorID, id);
        amount = amt;
        strcpy(date, d);
    }

    void display() const {
        cout << "Donor ID: " << donorID << " | Name: " << name
            << " | Amount: $" << amount << " | Date: " << date << endl;
    }

    void saveToFile(ofstream& file) {
        char buffer[500];
        sprintf(buffer, "%s|%s|%f|%s", name, donorID, amount, date);
        encryptDecrypt(buffer);
        file << buffer << endl;
    }
};

#endif
