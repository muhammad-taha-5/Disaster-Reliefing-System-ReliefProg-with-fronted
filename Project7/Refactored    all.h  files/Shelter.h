#ifndef SHELTER_H
#define SHELTER_H

#include "Resource.h"

class Shelter : public Resource {
private:
    int capacity;

public:
    Shelter() : Resource() {
        capacity = 0;
    }

    Shelter(const char* name, int qty, int cap)
        : Resource(name, qty, "Shelter", "N/A") {
        capacity = cap;
    }

    bool allocate(int amount) {
        if (quantity >= amount) {
            quantity -= amount;
            return true;
        }
        return false;
    }

    void display() const {
        cout << "Shelter: " << itemName << " | Available: " << quantity
            << " | Capacity: " << capacity << " persons each" << endl;
    }

    void saveToFile(ofstream& file) {
        char buffer[500];
        sprintf(buffer, "Shelter|%s|%d|%d", itemName, quantity, capacity);
        encryptDecrypt(buffer);
        file << buffer << endl;
    }
};

#endif
