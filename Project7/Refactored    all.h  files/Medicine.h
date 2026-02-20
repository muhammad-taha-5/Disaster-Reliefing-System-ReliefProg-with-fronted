#ifndef MEDICINE_H
#define MEDICINE_H

#include "Resource.h"

class Medicine : public Resource {
private:
    char* medicineType;

public:
    Medicine() : Resource() {
        medicineType = nullptr;
        deepCopy(medicineType, "");
    }

    Medicine(const char* name, int qty, const char* expiry, const char* type)
        : Resource(name, qty, "Medicine", expiry) {
        medicineType = nullptr;
        deepCopy(medicineType, type);
    }

    ~Medicine() {
        if (medicineType) delete[] medicineType;
    }

    bool allocate(int amount) {
        if (quantity >= amount) {
            quantity -= amount;
            return true;
        }
        return false;
    }

    void display() const {
        cout << "Medicine: " << itemName << " | Type: " << medicineType
            << " | Quantity: " << quantity << " units | Expiry: " << expiryDate << endl;
    }

    void saveToFile(ofstream& file) {
        char buffer[500];
        sprintf(buffer, "Medicine|%s|%d|%s|%s", itemName, quantity, expiryDate, medicineType);
        encryptDecrypt(buffer);
        file << buffer << endl;
    }
};

#endif
