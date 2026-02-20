#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"

class Admin : public Person {
private:
    char* username;
    char* password;
    char* role;

public:
    Admin() : Person() {
        username = nullptr;
        password = nullptr;
        role = nullptr;
        deepCopy(username, "admin");
        deepCopy(password, "admin123");
        deepCopy(role, "Administrator");
    }

    Admin(const char* n, const char* c, int a, const char* contact,
        const char* user, const char* pass, const char* r)
        : Person(n, c, a, contact) {
        username = nullptr;
        password = nullptr;
        role = nullptr;
        deepCopy(username, user);
        deepCopy(password, pass);
        deepCopy(role, r);
    }

    ~Admin() {
        if (username) delete[] username;
        if (password) delete[] password;
        if (role) delete[] role;
    }

    bool authenticate(const char* user, const char* pass) {
        return (strcmp(username, user) == 0 && strcmp(password, pass) == 0);
    }

    void display() const {
        cout << "\n--- ADMIN DETAILS ---" << endl;
        cout << "Name: " << name << endl;
        cout << "Username: " << username << endl;
        cout << "Role: " << role << endl;
    }
};

#endif
