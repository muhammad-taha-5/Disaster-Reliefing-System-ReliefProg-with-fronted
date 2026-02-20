#ifndef VICTIM_H
#define VICTIM_H

#include "Person.h"

class Victim : public Person {
private:
    int familySize;
    bool isInjured;
    bool isPregnant;
    bool hasShelter;
    char* disasterType;
    int priorityScore;
    bool resourcesReceived;
    char* location;
    double latitude;
    double longitude;

public:
    Victim() : Person() {
        familySize = 0;
        isInjured = false;
        isPregnant = false;
        hasShelter = false;
        disasterType = nullptr;
        location = nullptr;
        deepCopy(disasterType, "");
        deepCopy(location, "");
        priorityScore = 0;
        resourcesReceived = false;
        latitude = 0.0;
        longitude = 0.0;
    }

    Victim(const char* n, const char* c, int a, const char* contact,
        int fSize, bool injured, bool pregnant, bool shelter,
        const char* dtype, const char* loc, double lat, double lon)
        : Person(n, c, a, contact) {
        familySize = fSize;
        isInjured = injured;
        isPregnant = pregnant;
        hasShelter = shelter;
        disasterType = nullptr;
        location = nullptr;
        deepCopy(disasterType, dtype);
        deepCopy(location, loc);
        resourcesReceived = false;
        latitude = lat;
        longitude = lon;
        priorityScore = calculatePriority();
    }

    ~Victim() {
        if (disasterType) delete[] disasterType;
        if (location) delete[] location;
    }

    int calculatePriority() {
        int score = 0;
        score += familySize * 5;
        if (isInjured) score += 40;
        if (isPregnant) score += 35;
        if (age > 65) score += 20;
        if (age < 5) score += 25;
        if (!hasShelter) score += 30;
        if (strcmp(disasterType, "Earthquake") == 0) score += 15;
        else if (strcmp(disasterType, "Flood") == 0) score += 12;
        else if (strcmp(disasterType, "Fire") == 0) score += 18;
        return score;
    }

    int getFamilySize() const { return familySize; }
    int getPriorityScore() const { return priorityScore; }
    const char* getDisasterType() const { return disasterType; }
    const char* getLocation() const { return location; }
    bool isHelped() const { return resourcesReceived; }
    bool getInjuredStatus() const { return isInjured; }
    bool getPregnantStatus() const { return isPregnant; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    void markAsHelped() { resourcesReceived = true; }

    void display() const {
        cout << "\n--- VICTIM DETAILS ---" << endl;
        cout << "Name: " << name << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contactNumber << endl;
        cout << "Family Size: " << familySize << endl;
        cout << "Disaster Type: " << disasterType << endl;
        cout << "Location: " << location << endl;
        cout << "Injured: " << (isInjured ? "YES" : "NO") << endl;
        cout << "Pregnant: " << (isPregnant ? "YES" : "NO") << endl;
        cout << "Has Shelter: " << (hasShelter ? "YES" : "NO") << endl;
        cout << "Priority Score: " << priorityScore << endl;
        cout << "Resources Received: " << (resourcesReceived ? "YES" : "NO") << endl;
    }

    void saveToFile(ofstream& file) {
        char buffer[1024];
        sprintf(buffer, "%s|%s|%d|%s|%d|%d|%d|%d|%s|%s|%f|%f|%d|%d",
            name, cnic, age, contactNumber, familySize, isInjured, isPregnant,
            hasShelter, disasterType, location, latitude, longitude, priorityScore, resourcesReceived);

        encryptDecrypt(buffer);
        file << buffer << endl;
    }
};

#endif
