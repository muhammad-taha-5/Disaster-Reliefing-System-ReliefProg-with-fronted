#ifndef RESOURCE_H
#define RESOURCE_H

#include "Utils.h"

class Resource {
protected:
    char* itemName;
    int quantity;
    char* category;
    char* expiryDate;

    void deepCopy(char*& dest, const char* src) {
        if (dest != nullptr) delete[] dest;
        if (src == nullptr) {
            dest = new char[1];
            dest[0] = '\0';
            return;
        }
        int len = (int)strlen(src);
        dest = new char[len + 1];
        strcpy(dest, src);
    }

public:
    Resource() {
        itemName = nullptr;
        category = nullptr;
        expiryDate = nullptr;
        deepCopy(itemName, "");
        deepCopy(category, "");
        deepCopy(expiryDate, "");
        quantity = 0;
    }

    Resource(const char* name, int qty, const char* cat, const char* expiry) {
        itemName = nullptr;
        category = nullptr;
        expiryDate = nullptr;
        deepCopy(itemName, name);
        deepCopy(category, cat);
        deepCopy(expiryDate, expiry);
        quantity = qty;
    }

    virtual ~Resource() {
        if (itemName) delete[] itemName;
        if (category) delete[] category;
        if (expiryDate) delete[] expiryDate;
    }

    int getQuantity() const { return quantity; }
    const char* getItemName() const { return itemName; }
    const char* getCategory() const { return category; }
    const char* getExpiryDate() const { return expiryDate; }

    void updateQuantity(int amount) {
        quantity += amount;
        if (quantity < 0) quantity = 0;
    }

    virtual bool allocate(int amount) = 0;
    virtual void display() const = 0;
    virtual void saveToFile(ofstream& file) = 0;
};

#endif
