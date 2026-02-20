#ifndef FOOD_H
#define FOOD_H

#include "Resource.h"

class Food : public Resource {
private:
    char* foodType;

public:
    Food() : Resource() {
        foodType = nullptr;
        deepCopy(foodType, "");
    }

    Food(const char* name, int qty, const char* expiry, const char* type)
        : Resource(name, qty, "Food", expiry) {
        foodType = nullptr;
        deepCopy(foodType, type);
    }

    ~Food() {
        if (foodType) delete[] foodType;
    }

    bool allocate(int amount) {
        if (quantity >= amount) {
            quantity -= amount;
            return true;
        }
        return false;
    }

    void display() const {
        cout << "Food: " << itemName << " | Type: " << foodType
            << " | Quantity: " << quantity << " kg | Expiry: " << expiryDate << endl;
    }

    void saveToFile(ofstream& file) {
        char buffer[500];
        sprintf(buffer, "Food|%s|%d|%s|%s", itemName, quantity, expiryDate, foodType);
        encryptDecrypt(buffer);
        file << buffer << endl;
    }
};

#endif
