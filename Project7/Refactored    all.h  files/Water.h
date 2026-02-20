#ifndef WATER_H
#define WATER_H

#include "Resource.h"

class Water : public Resource {
public:
    Water() : Resource() {}

    Water(const char* name, int qty, const char* expiry)
        : Resource(name, qty, "Water", expiry) {
    }

    bool allocate(int amount) {
        if (quantity >= amount) {
            quantity -= amount;
            return true;
        }
        return false;
    }

    void display() const {
        cout << "Water: " << itemName << " | Quantity: " << quantity
            << " liters | Expiry: " << expiryDate << endl;
    }

    void saveToFile(ofstream& file) {
        char buffer[500];
        sprintf(buffer, "Water|%s|%d|%s", itemName, quantity, expiryDate);
        encryptDecrypt(buffer);
        file << buffer << endl;
    }
};

#endif
