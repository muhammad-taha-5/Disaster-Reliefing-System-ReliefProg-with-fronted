#ifndef PERSON_H
#define PERSON_H

#include "Utils.h"

class Person {
protected:
    char* name;
    char* cnic;
    int age;
    char* contactNumber;

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
    Person() {
        name = nullptr;
        cnic = nullptr;
        contactNumber = nullptr;
        deepCopy(name, "");
        deepCopy(cnic, "");
        deepCopy(contactNumber, "");
        age = 0;
    }

    Person(const char* n, const char* c, int a, const char* contact) {
        name = nullptr;
        cnic = nullptr;
        contactNumber = nullptr;
        deepCopy(name, n);
        deepCopy(cnic, c);
        deepCopy(contactNumber, contact);
        age = a;
    }

    virtual ~Person() {
        if (name) delete[] name;
        if (cnic) delete[] cnic;
        if (contactNumber) delete[] contactNumber;
    }

    const char* getName() const { return name; }
    const char* getCNIC() const { return cnic; }
    int getAge() const { return age; }
    const char* getContact() const { return contactNumber; }

    virtual void display() const = 0;
};

#endif
