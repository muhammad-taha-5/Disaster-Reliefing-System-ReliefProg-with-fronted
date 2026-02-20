#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio> // For sprintf
#include <cmath>  // For distance calculations
#include <windows.h>
using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Color Constants
const int C_DEFAULT = 7;
const int C_TITLE = 11;   // Cyan
const int C_MENU = 14;    // Yellow
const int C_SUCCESS = 10; // Light Green
const int C_ERROR = 12;   // Light Red
const int C_INFO = 13;    // Pink/Purple
const int C_PROMPT = 9;   // Bright Blue
const int C_WARNING = 6;  // Dark Yellow/Brown for warnings

void showStartScreen() {
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

// ============================================
// HELPER FUNCTIONS (Manual Implementation)
// ============================================

// Manual string to int conversion (replaces atoi)
// Manual string to int conversion (replaces atoi)
int stringToInt(const char* str) {
    if (!str) return 0;
    int res = 0;
    int sign = 1;
    int i = 0;
    // Skip whitespace/control chars
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n') i++;

    if (str[i] == '-') { sign = -1; i++; }
    for (; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + (str[i] - '0');
        else break; // Stop at non-digit
    }
    return sign * res;
}

// Manual string to double conversion (replaces atof)
double stringToDouble(const char* str) {
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

// Safe Encryption/Decryption (Symmetric Flip)
// detailed: 158 - x maps the range [32, 126] onto itself.
// e.g. 32 -> 126, 126 -> 32. 79 -> 79.
// This matches the files 'G=*9,"...' that the user has.
void encryptDecrypt(char* str) {
    if (!str) return;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 32 && str[i] <= 126) {
            str[i] = 158 - str[i];
        }
    }
}

struct RegionData {
    char name[50];
    double rainfall;       // mm
    double temperature;    // Celsius
    double seismicActivity;// Richter scale
    double riverLevel;     // meters
    double populationDensity; // people per sq km
};

class PredictionSystem {
private:
    RegionData regions[20];
    int regionCount;

public:
    PredictionSystem() {
        regionCount = 0;
    }

    void generateMockData() {
        ifstream infile("region_data.txt");
        if (infile.good()) {
            infile.close();
            return; // File exists
        }
        infile.close();

        ofstream outfile("region_data.txt");
        if (outfile.is_open()) {
            // Format: RegionName|Rainfall|Temp|Seismic|RiverLevel|PopDensity
            // Encrypted via same global function
            char lines[10][200] = {
                "Karachi|120.5|32.0|2.1|4.5|2000",
                "Quetta|10.0|15.0|5.8|1.2|800",
                "Lahore|250.0|38.0|1.5|7.8|1800",
                "Peshawar|45.0|28.0|3.2|3.0|1200",
                "Islamabad|80.0|25.0|2.8|2.5|900",
                "Multan|5.0|46.0|1.0|2.0|1100",
                "Gilgit|15.0|10.0|4.5|5.0|300",
                "Gwadar|60.0|34.0|5.2|3.5|400",
                "Sialkot|180.0|30.0|1.8|6.5|1000",
                "Murree|200.0|18.0|2.0|3.0|500"
            };

            for (int i = 0; i < 10; i++) {
                encryptDecrypt(lines[i]); // Encrypt before writing
                outfile << lines[i] << endl;
            }
            outfile.close();
            cout << "[+] Generated mock regional data file: region_data.txt" << endl;
        }
    }

    void loadRegionalData() {
        generateMockData(); // Ensure file exists
        ifstream file("region_data.txt");
        regionCount = 0;

        if (file.is_open()) {
            char line[500];
            while (file.getline(line, 500)) {
                if (regionCount >= 20) break;

                encryptDecrypt(line); // Decrypt

                char* name = strtok(line, "|");
                char* rainStr = strtok(nullptr, "|");
                char* tempStr = strtok(nullptr, "|");
                char* seismicStr = strtok(nullptr, "|");
                char* riverStr = strtok(nullptr, "|");
                char* popStr = strtok(nullptr, "|");

                if (name && rainStr && tempStr) {
                    strcpy(regions[regionCount].name, name);
                    regions[regionCount].rainfall = stringToDouble(rainStr);
                    regions[regionCount].temperature = stringToDouble(tempStr);
                    regions[regionCount].seismicActivity = stringToDouble(seismicStr);
                    regions[regionCount].riverLevel = stringToDouble(riverStr);
                    regions[regionCount].populationDensity = stringToDouble(popStr);
                    regionCount++;
                }
            }
            file.close();
        }
    }

    void generatePredictionReport() {
        loadRegionalData();
        setColor(C_TITLE);
        cout << "\n===== REGIONAL HAZARD PREDICTION REPORT =====" << endl;
        setColor(C_DEFAULT);

        ofstream rFile("prediction_report.txt");
        rFile << "===== AUTOMATED HAZARD PREDICTION REPORT =====" << endl;

        for (int i = 0; i < regionCount; i++) {
            displayRegionReport(i, rFile);
        }
        rFile.close();
        cout << "[+] Full detailed report saved to 'prediction_report.txt'" << endl;
    }

    void searchRegionReport() {
        loadRegionalData();
        if (regionCount == 0) {
            cout << "[!] No regional data available." << endl;
            return;
        }

        char searchName[50];
        cout << "\nEnter Region Name to search: ";
        cin.ignore();
        cin.getline(searchName, 50);

        bool found = false;
        ofstream rFile("region_search_result.txt");

        for (int i = 0; i < regionCount; i++) {
            // Case-insensitive manual match
            bool match = true;
            int j = 0;
            while (regions[i].name[j] != '\0' || searchName[j] != '\0') {
                char c1 = regions[i].name[j];
                char c2 = searchName[j];
                if (c1 >= 'a' && c1 <= 'z') c1 -= 32;
                if (c2 >= 'a' && c2 <= 'z') c2 -= 32;
                if (c1 != c2) {
                    match = false;
                    break;
                }
                j++;
            }

            if (match) {
                if (!found) {
                    setColor(C_TITLE);
                    cout << "\n===== SEARCH RESULT FOR: " << searchName << " =====" << endl;
                    setColor(C_DEFAULT);
                }
                displayRegionReport(i, rFile);
                found = true;
            }
        }

        if (!found) {
            cout << "[!] No prediction data found for region: " << searchName << endl;
        }
        else {
            cout << "[+] Result saved to 'region_search_result.txt'" << endl;
        }
        rFile.close();
    }

private:
    void displayRegionReport(int i, ofstream& rFile) {
        RegionData& r = regions[i];
        int riskScore = 0;
        char riskLevel[20] = "LOW";
        char prediction[100] = "Normal Conditions";

        // Calculation Logic
        if (r.rainfall > 150) riskScore += 30;
        if (r.riverLevel > 6.0) riskScore += 25;
        if (r.seismicActivity > 5.0) riskScore += 40;
        if (r.temperature > 42.0) riskScore += 20;

        // Determine Level & Color
        int levelColor = C_SUCCESS; // Default Green for LOW
        if (riskScore >= 60) {
            strcpy(riskLevel, "CRITICAL");
            levelColor = C_ERROR; // Red
        }
        else if (riskScore >= 30) {
            strcpy(riskLevel, "HIGH");
            levelColor = C_WARNING; // Yellow/Brown
        }
        else if (riskScore >= 15) {
            strcpy(riskLevel, "MODERATE");
            levelColor = C_TITLE; // Cyan
        }

        // Specific Prediction
        if (r.seismicActivity > 5.0) strcpy(prediction, "Earthquake Warning!");
        else if (r.rainfall > 200 || r.riverLevel > 7.0) strcpy(prediction, "Severe Flooding Imminent");
        else if (r.rainfall > 100) strcpy(prediction, "Flood Alert");
        else if (r.temperature > 40.0) strcpy(prediction, "Heatwave Warning");

        // Display
        setColor(C_TITLE);
        cout << "Region: ";
        setColor(C_DEFAULT);
        cout << r.name << endl;

        cout << "  - Risk Score: " << riskScore << "/100 (";
        setColor(levelColor);
        cout << riskLevel;
        setColor(C_DEFAULT);
        cout << ")" << endl;

        cout << "  - Prediction: ";
        setColor(levelColor);
        cout << prediction << endl;
        setColor(C_DEFAULT);

        cout << "  - Data: " << r.rainfall << "mm Rain, " << r.seismicActivity << " Richter" << endl;
        setColor(C_MENU);
        cout << "---------------------------------------------" << endl;
        setColor(C_DEFAULT);

        // File logging (no colors in text file)
        if (rFile.is_open()) {
            rFile << "Region: " << r.name << endl;
            rFile << "Risk: " << riskLevel << " (" << riskScore << ")" << endl;
            rFile << "Prediction: " << prediction << endl;
            rFile << "-----------------------------" << endl;
        }
    }
};

class UXManager {
public:
    enum Language { ENGLISH, URDU, SPANISH };
    Language currentLang;

    UXManager() { currentLang = ENGLISH; }

    void sendAlert(const char* contact, const char* message) {
        cout << "\n[SYSTEM] Initializing Communication Protocol...\n[SYSTEM] Connecting to Gateway...";
        for (int i = 0; i < 3; i++) {
            for (long long j = 0; j < 100000000; j++);
            cout << ".";
        }

        cout << "\n[SMS] Sending to: " << contact << "\n[CONTENT] " << message << endl;

        ofstream outbox("outbox.txt", ios::app);
        if (outbox.is_open()) {
            outbox << "TYPE: SMS/Email | TO: " << contact << " | MSG: " << message << " | STATUS: DELIVERED" << endl;
            outbox.close();
        }
        cout << "[SUCCESS] Alert delivered and logged in 'outbox.txt'" << endl;
    }

    void emergencyBroadcast(const char* msg) {
        for (int i = 0; i < 3; i++) {
            cout << "\a";
            system("cls");
            cout << "\n\n\n\t\t###########################################" << endl;
            cout << "\t\t##       EMERGENCY BROADCAST SYSTEM      ##" << endl;
            cout << "\t\t###########################################" << endl;
            cout << "\n\t\t   ALERT: " << msg << endl;
            cout << "\n\t\t###########################################" << endl;
            for (long long j = 0; j < 200000000; j++);
            system("cls");
            for (long long j = 0; j < 100000000; j++);
        }
        cout << "\n[!] Broadcast completed to all regional channels." << endl;
    }

    void changeLanguage() {
        int choice;
        cout << "\n--- SELECT LANGUAGE / ZUBAN MUNTKHIB KAREIN ---" << endl;
        cout << "1. English" << endl;
        cout << "2. Urdu (اردو)" << endl;
        cout << "3. Spanish (Español)" << endl;
        cout << "Choice: ";
        cin >> choice;
        if (choice == 1) currentLang = ENGLISH;
        else if (choice == 2) currentLang = URDU;
        else if (choice == 3) currentLang = SPANISH;

        if (currentLang == URDU) cout << "\n[+] Zuban tabdeel ho gayi hai!" << endl;
        else if (currentLang == SPANISH) cout << "\n[+] ¡Idioma cambiado con éxito!" << endl;
        else cout << "\n[+] Language changed to English!" << endl;
    }

    void printMenuHeader() {
        setColor(C_MENU);
        if (currentLang == URDU) {
            cout << "\n==========================================" << endl;
            cout << "=           MUKHYA MENU (MAIN)           =" << endl;
            cout << "==========================================" << endl;
        }
        else if (currentLang == SPANISH) {
            cout << "\n==========================================" << endl;
            cout << "=           MEN\xDA PRINCIPAL               =" << endl;
            cout << "==========================================" << endl;
        }
        else {
            cout << "\n==========================================" << endl;
            cout << "=           MAIN MENU                    =" << endl;
            cout << "==========================================" << endl;
        }
        setColor(C_DEFAULT);
    }
};

// ============================================
// RELIEF CENTER FINDER (New Feature)
// ============================================
struct ReliefCenter {
    char name[50];
    double latitude;
    double longitude;
};

class ReliefService {
private:
    ReliefCenter centers[5];
public:
    ReliefService() {
        // Mock Relief Centers
        strcpy(centers[0].name, "Central Rescue Base (Karachi)");
        centers[0].latitude = 24.8607; centers[0].longitude = 67.0011;

        strcpy(centers[1].name, "Northern Aid Camp (Lahore)");
        centers[1].latitude = 31.5204; centers[1].longitude = 74.3587;

        strcpy(centers[2].name, "Federal Medical Post (Islamabad)");
        centers[2].latitude = 33.6844; centers[2].longitude = 73.0479;

        strcpy(centers[3].name, "Mountain Rescue Unit (Quetta)");
        centers[3].latitude = 30.1798; centers[3].longitude = 66.9750;

        strcpy(centers[4].name, "Frontier Relief Hub (Peshawar)");
        centers[4].latitude = 34.0151; centers[4].longitude = 71.5249;
    }

    void findNearest(double userLat, double userLon) {
        int nearestIdx = 0;
        double minDistance = 1e9;

        cout << "\n--- SEARCHING NEAREST RELIEF CENTER ---" << endl;
        for (int i = 0; i < 5; i++) {
            // Simple Euclidean distance for simulation
            double dist = sqrt(pow(centers[i].latitude - userLat, 2) +
                pow(centers[i].longitude - userLon, 2));

            if (dist < minDistance) {
                minDistance = dist;
                nearestIdx = i;
            }
        }

        cout << "[+] Found Nearest Center!" << endl;
        cout << "Name: " << centers[nearestIdx].name << endl;
        cout << "Coordinates: " << centers[nearestIdx].latitude << ", " << centers[nearestIdx].longitude << endl;
        // Mock distance conversion (1 degree approx 111km)
        cout << "Approximate Distance: " << minDistance * 111 << " km away" << endl;
        cout << "---------------------------------------" << endl;
    }
};

// ABSTRACT BASE CLASS - Person

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

        encryptDecrypt(buffer); // Encrypt before writing
        file << buffer << endl;
    }
};

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

class AllocationSystem {
private:
    Victim* victims[100];
    Resource* inventory[50];
    Donor* donors[100];
    int victimCount;
    int resourceCount;
    int donorCount;
    char* currentDisaster;

    // Bubble sort by priority (descending)
    void sortByPriority() {
        for (int i = 0; i < victimCount - 1; i++) {
            for (int j = 0; j < victimCount - i - 1; j++) {
                if (victims[j]->getPriorityScore() < victims[j + 1]->getPriorityScore()) {
                    Victim* temp = victims[j];
                    victims[j] = victims[j + 1];
                    victims[j + 1] = temp;
                }
            }
        }
    }

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
    AllocationSystem() {
        victimCount = 0;
        resourceCount = 0;
        donorCount = 0;
        currentDisaster = nullptr;
        deepCopy(currentDisaster, "General");

        for (int i = 0; i < 100; i++) victims[i] = nullptr;
        for (int i = 0; i < 50; i++) inventory[i] = nullptr;
        for (int i = 0; i < 100; i++) donors[i] = nullptr;
        loadData();
    }

    ~AllocationSystem() {
        for (int i = 0; i < victimCount; i++) {
            if (victims[i]) delete victims[i];
        }
        for (int i = 0; i < resourceCount; i++) {
            if (inventory[i]) delete inventory[i];
        }
        for (int i = 0; i < donorCount; i++) {
            if (donors[i]) delete donors[i];
        }
        if (currentDisaster) delete[] currentDisaster;
    }

    void setDisasterType(const char* type) {
        deepCopy(currentDisaster, type);
    }

    bool checkDuplicate(const char* cnic) {
        for (int i = 0; i < victimCount; i++) {
            if (strcmp(victims[i]->getCNIC(), cnic) == 0) {
                return true;
            }
        }
        return false;
    }

    void addVictim(Victim* victim) {
        if (victimCount < 100) {
            if (checkDuplicate(victim->getCNIC())) {
                setColor(C_WARNING);
                cout << "\n[!] DUPLICATE DETECTED! This CNIC is already registered." << endl;
                cout << "Preventing double allocation to maintain fairness." << endl;
                setColor(C_DEFAULT);
                delete victim;
                return;
            }
            victims[victimCount++] = victim;
            setColor(C_SUCCESS);
            cout << "\n[+] Victim registered successfully! Priority Score: "
                << victim->getPriorityScore() << endl;
            setColor(C_DEFAULT);
        }
        else {
            setColor(C_ERROR);
            cout << "\n? Victim list is full!" << endl;
            setColor(C_DEFAULT);
            delete victim;
        }
    }

    void addResource(Resource* resource) {
        if (resourceCount < 50) {
            inventory[resourceCount++] = resource;
            setColor(C_SUCCESS);
            cout << "\n[+] Resource added successfully!" << endl;
            setColor(C_DEFAULT);
        }
        else {
            setColor(C_ERROR);
            cout << "\n[!] Inventory is full!" << endl;
            setColor(C_DEFAULT);
            delete resource;
        }
    }

    void addDonor(Donor* donor) {
        if (donorCount < 100) {
            donors[donorCount++] = donor;
            setColor(C_SUCCESS);
            cout << "\n[+] Donation recorded successfully!" << endl;
            setColor(C_DEFAULT);
        }
        else {
            setColor(C_ERROR);
            cout << "\n[!] Donor list is full!" << endl;
            setColor(C_DEFAULT);
            delete donor;
        }
    }

    void smartAllocate() {
        if (victimCount == 0) {
            setColor(C_WARNING);
            cout << "\n[!] No victims registered yet!" << endl;
            setColor(C_DEFAULT);
            return;
        }

        // Sort victims by priority
        sortByPriority();

        setColor(C_TITLE);
        cout << "\n========== SMART ALLOCATION PROCESS ==========" << endl;
        setColor(C_DEFAULT);
        cout << "Allocating resources based on priority scores..." << endl;

        int helpedCount = 0;

        for (int i = 0; i < victimCount; i++) {
            if (victims[i]->isHelped()) {
                continue; // Skip already helped victims
            }

            int familySize = victims[i]->getFamilySize();
            bool allocated = false;

            cout << "\n> Processing: " << victims[i]->getName()
                << " (Priority: " << victims[i]->getPriorityScore() << ")" << endl;

            // Allocate food (2 kg per person)
            int foodNeeded = familySize * 2;
            for (int j = 0; j < resourceCount; j++) {
                if (strcmp(inventory[j]->getCategory(), "Food") == 0) {
                    if (inventory[j]->allocate(foodNeeded)) {
                        setColor(C_SUCCESS);
                        cout << "  -> Allocated " << foodNeeded << " kg food" << endl;
                        setColor(C_DEFAULT);
                        allocated = true;
                        break;
                    }
                }
            }

            // Allocate water (3 liters per person)
            int waterNeeded = familySize * 3;
            for (int j = 0; j < resourceCount; j++) {
                if (strcmp(inventory[j]->getCategory(), "Water") == 0) {
                    if (inventory[j]->allocate(waterNeeded)) {
                        setColor(C_SUCCESS);
                        cout << "  -> Allocated " << waterNeeded << " L water" << endl;
                        setColor(C_DEFAULT);
                        allocated = true;
                        break;
                    }
                }
            }

            // Allocate medicine if injured/medical emergency
            if (victims[i]->getInjuredStatus() || victims[i]->getPregnantStatus()) {
                for (int j = 0; j < resourceCount; j++) {
                    if (strcmp(inventory[j]->getCategory(), "Medicine") == 0) {
                        if (inventory[j]->allocate(5)) {
                            setColor(C_SUCCESS);
                            cout << "  -> Allocated 5 units medicine (Medical Emergency)" << endl;
                            setColor(C_DEFAULT);
                            allocated = true;
                            break;
                        }
                    }
                }
            }

            if (allocated) {
                victims[i]->markAsHelped();
                helpedCount++;
                saveAllocation(victims[i]);
            }
            else {
                setColor(C_WARNING);
                cout << "  [!] Insufficient resources for this victim" << endl;
                setColor(C_DEFAULT);
            }
        }

        setColor(C_TITLE);
        cout << "\n========================================" << endl;
        setColor(C_DEFAULT);
        cout << "Total families helped: " << helpedCount << "/" << victimCount << endl;
        checkLowStock();
    }

    void checkLowStock() {
        setColor(C_TITLE);
        cout << "\n--- LOW STOCK ALERTS ---" << endl;
        setColor(C_DEFAULT);
        bool lowStock = false;

        for (int i = 0; i < resourceCount; i++) {
            if (inventory[i]->getQuantity() < 20) {
                setColor(C_WARNING);
                cout << "[!] LOW STOCK: " << inventory[i]->getItemName()
                    << " - Only " << inventory[i]->getQuantity() << " remaining!" << endl;
                setColor(C_DEFAULT);
                lowStock = true;
            }
        }

        if (!lowStock) {
            setColor(C_SUCCESS);
            cout << "[+] All resources have adequate stock." << endl;
            setColor(C_DEFAULT);
        }
    }

    void displayAllVictims() {
        if (victimCount == 0) {
            setColor(C_WARNING);
            cout << "\n[!] No victims registered." << endl;
            setColor(C_DEFAULT);
            return;
        }

        setColor(C_TITLE);
        cout << "\n========== ALL REGISTERED VICTIMS ==========" << endl;
        setColor(C_DEFAULT);
        for (int i = 0; i < victimCount; i++) {
            victims[i]->display();
            cout << "-------------------------------------------" << endl;
        }
    }

    void displayInventory() {
        if (resourceCount == 0) {
            setColor(C_WARNING);
            cout << "\n[!] No resources in inventory." << endl;
            setColor(C_DEFAULT);
            return;
        }

        setColor(C_TITLE);
        cout << "\n========== CURRENT INVENTORY ==========" << endl;
        setColor(C_DEFAULT);
        for (int i = 0; i < resourceCount; i++) {
            inventory[i]->display();
        }
        setColor(C_TITLE);
        cout << "=======================================" << endl;
        setColor(C_DEFAULT);
    }

    // --- TIER 3 FEATURE: Search Victim ---
    void searchVictimByCNIC(const char* searchCNIC) {
        bool found = false;
        setColor(C_TITLE);
        cout << "\n===== VICTIM SEARCH =====\n";
        setColor(C_DEFAULT);
        for (int i = 0; i < victimCount; i++) {
            if (strcmp(victims[i]->getCNIC(), searchCNIC) == 0) {
                victims[i]->display();
                found = true;
                break;
            }
        }
        if (!found) {
            setColor(C_WARNING);
            cout << "[!] No victim found with CNIC: " << searchCNIC << endl;
            setColor(C_DEFAULT);
        }
    }

    // --- TIER 3 FEATURE: Medical Emergency Viewer ---
    void displayMedicalEmergencies() {
        setColor(C_TITLE);
        cout << "\n===== MEDICAL EMERGENCY LIST =====\n";
        setColor(C_DEFAULT);
        bool found = false;
        for (int i = 0; i < victimCount; i++) {
            if (victims[i]->getInjuredStatus() || victims[i]->getPregnantStatus()) {
                cout << "Name: " << victims[i]->getName()
                    << " | Condition: " << (victims[i]->getInjuredStatus() ? "Injured " : "")
                    << (victims[i]->getPregnantStatus() ? "Pregnant" : "") << endl;
                found = true;
            }
        }
        if (!found) cout << "No medical emergencies reported." << endl;
    }

    // --- TIER 3 FEATURE: Predictive Planning ---
    void predictResourceNeeds() {
        setColor(C_TITLE);
        cout << "\n===== PREDICTIVE RESOURCE PLANNING =====\n";
        setColor(C_DEFAULT);
        int totalFoodNeeded = 0;
        int totalWaterNeeded = 0;
        int totalMedicineNeeded = 0;

        for (int i = 0; i < victimCount; i++) {
            if (!victims[i]->isHelped()) {
                totalFoodNeeded += victims[i]->getFamilySize() * 2;
                totalWaterNeeded += victims[i]->getFamilySize() * 3;
                if (victims[i]->getInjuredStatus() || victims[i]->getPregnantStatus()) {
                    totalMedicineNeeded += 5;
                }
            }
        }

        cout << "Predicted Demand (Pending Victims):\n";
        cout << " - Food Needed: " << totalFoodNeeded << " kg\n";
        cout << " - Water Needed: " << totalWaterNeeded << " liters\n";
        cout << " - Medicine Needed: " << totalMedicineNeeded << " units\n";

        // Simple analysis vs inventory could go here, but this is a good start.
    }

    void displayDonors() {
        if (donorCount == 0) {
            setColor(C_WARNING);
            cout << "\n[!] No donors registered." << endl;
            setColor(C_DEFAULT);
            return;
        }
        setColor(C_TITLE);
        cout << "\n===== DONOR LIST =====\n";
        setColor(C_DEFAULT);
        for (int i = 0; i < donorCount; i++) {
            donors[i]->display();
        }
    }

    void generateReport() {
        ofstream file("daily_report.txt", ios::app);

        if (!file.is_open()) {
            setColor(C_ERROR);
            cout << "\n[!] Error generating report!" << endl;
            setColor(C_DEFAULT);
            return;
        }

        file << "\n========== DAILY REPORT ==========" << endl;
        file << "Disaster Type: " << currentDisaster << endl;
        file << "Total Victims Registered: " << victimCount << endl;

        int helpedCount = 0;
        int medicalEmergencies = 0;

        for (int i = 0; i < victimCount; i++) {
            if (victims[i]->isHelped()) helpedCount++;
            if (victims[i]->getInjuredStatus() || victims[i]->getPregnantStatus()) {
                medicalEmergencies++;
            }
        }

        file << "Families Helped: " << helpedCount << endl;
        file << "Medical Emergencies: " << medicalEmergencies << endl;
        file << "Remaining Stock:" << endl;

        for (int i = 0; i < resourceCount; i++) {
            file << "  - " << inventory[i]->getItemName()
                << ": " << inventory[i]->getQuantity() << endl;
        }

        file << "==================================\n" << endl;
        file.close();

        file << "==================================\n" << endl;
        file.close();

        setColor(C_SUCCESS);
        cout << "\n[+] Daily report generated successfully!" << endl;
        setColor(C_DEFAULT);
    }

    void saveAllocation(Victim* victim) {
        ofstream file("allocations.txt", ios::app);
        if (file.is_open()) {
            char buffer[500];
            sprintf(buffer, "%s|%s|%d|%d|HELPED", victim->getName(), victim->getCNIC(), victim->getFamilySize(), victim->getPriorityScore());
            // Allocations generally kept in plain text for easy auditing, but let's encrypt for consistency request
            encryptDecrypt(buffer);
            file << buffer << endl;
            file.close();
        }
    }

    void viewAllocations() {
        ifstream file("allocations.txt");
        if (!file.is_open()) {
            setColor(C_WARNING);
            cout << "\n[!] No allocation history found." << endl;
            setColor(C_DEFAULT);
            return;
        }

        // Skip BOM if present
        char bom[3];
        file.read(bom, 3);
        if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF)) {
            file.seekg(0);
        }

        setColor(C_TITLE);
        cout << "\n===== ALLOCATION HISTORY (DECRYPTED) =====" << endl;
        setColor(C_DEFAULT);
        // Simple header formatting
        cout << "Name                 CNIC            Family    Priority  Status" << endl;
        cout << "------------------------------------------------------------------" << endl;

        char line[500];
        while (file.getline(line, 500)) {
            encryptDecrypt(line);

            char* name = strtok(line, "|");
            char* cnic = strtok(nullptr, "|");
            char* fsize = strtok(nullptr, "|");
            char* prio = strtok(nullptr, "|");
            char* status = strtok(nullptr, "|");

            if (name && cnic && fsize) {
                // Manual alignment since we avoided <iomanip>
                cout << name;

                // Padding loop for Name column (approx 20 chars)
                int len = strlen(name);
                for (int k = 0; k < (20 - len); k++) cout << " ";

                cout << cnic;

                // Padding for CNIC (approx 15 chars)
                len = strlen(cnic);
                for (int k = 0; k < (16 - len); k++) cout << " ";

                cout << fsize << "         "; // Fixed spacing for family

                if (prio) cout << prio << "        ";
                else cout << "N/A       ";

                if (status) cout << status;
                else cout << "HELPED";

                cout << endl;
            }
        }
        file.close();
        cout << "==================================================================" << endl;
    }

    void saveAllData() {
        // Save victims
        ofstream vFile("victims.txt");
        if (vFile.is_open()) {
            for (int i = 0; i < victimCount; i++) {
                victims[i]->saveToFile(vFile);
            }
            vFile.close();
        }

        // Save inventory
        ofstream rFile("inventory.txt");
        if (rFile.is_open()) {
            for (int i = 0; i < resourceCount; i++) {
                inventory[i]->saveToFile(rFile);
            }
            rFile.close();
        }

        // Save donations
        ofstream dFile("donations.txt");
        if (dFile.is_open()) {
            for (int i = 0; i < donorCount; i++) {
                donors[i]->saveToFile(dFile);
            }
            dFile.close();
        }

        setColor(C_SUCCESS);
        cout << "\n[+] All data saved (ENCRYPTED) successfully!" << endl;
        setColor(C_DEFAULT);
    }

    void loadData() {
        // Load Victims
        ifstream vFile("victims.txt");
        if (vFile.is_open()) {
            // Check for and skip UTF-8 BOM
            char bom[3];
            vFile.read(bom, 3);
            if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF)) {
                vFile.seekg(0); // If no BOM, reset to beginning
            }

            char line[1024];
            while (vFile.getline(line, 1024)) {
                if (victimCount >= 100) break;

                encryptDecrypt(line);

                char* name = strtok(line, "|");
                char* cnic = strtok(nullptr, "|");
                char* ageStr = strtok(nullptr, "|");
                char* contact = strtok(nullptr, "|");
                char* fSizeStr = strtok(nullptr, "|");
                char* injuredStr = strtok(nullptr, "|");
                char* pregnantStr = strtok(nullptr, "|");
                char* shelterStr = strtok(nullptr, "|");
                char* dtype = strtok(nullptr, "|");
                char* loc = strtok(nullptr, "|");
                char* latStr = strtok(nullptr, "|");
                char* lonStr = strtok(nullptr, "|");

                if (name && cnic && ageStr && contact && fSizeStr && injuredStr && pregnantStr && shelterStr && dtype && loc && latStr && lonStr) {
                    int age = stringToInt(ageStr);
                    int fSize = stringToInt(fSizeStr);
                    bool injured = stringToInt(injuredStr);
                    bool pregnant = stringToInt(pregnantStr);
                    bool shelter = stringToInt(shelterStr);
                    double lat = stringToDouble(latStr);
                    double lon = stringToDouble(lonStr);

                    char* priorityStr = strtok(nullptr, "|");
                    char* receivedStr = strtok(nullptr, "|");

                    Victim* v = new Victim(name, cnic, age, contact, fSize, injured, pregnant, shelter, dtype, loc, lat, lon);

                    // Correctly load helped status
                    if (receivedStr && stringToInt(receivedStr) == 1) {
                        v->markAsHelped();
                    }
                    victims[victimCount++] = v;
                }
            }
            vFile.close();
            setColor(C_INFO);
            cout << "[+] Loaded " << victimCount << " victims." << endl;
            setColor(C_DEFAULT);
        }

        // Load Inventory
        ifstream rFile("inventory.txt");
        if (rFile.is_open()) {
            // Check for and skip UTF-8 BOM
            char bom[3];
            rFile.read(bom, 3);
            if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF)) {
                rFile.seekg(0); // If no BOM, reset to beginning
            }

            char line[500];
            while (rFile.getline(line, 500)) {
                if (resourceCount >= 50) break;
                encryptDecrypt(line); // Decrypt

                char* type = strtok(line, "|");
                char* name = strtok(nullptr, "|");
                char* qtyStr = strtok(nullptr, "|");

                if (type && name && qtyStr) {
                    int qty = stringToInt(qtyStr);
                    if (strcmp(type, "Food") == 0) {
                        char* expiry = strtok(nullptr, "|");
                        char* ftype = strtok(nullptr, "|");
                        if (expiry && ftype)
                            addResource(new Food(name, qty, expiry, ftype));
                    }
                    else if (strcmp(type, "Medicine") == 0) {
                        char* expiry = strtok(nullptr, "|");
                        char* mtype = strtok(nullptr, "|");
                        if (expiry && mtype)
                            addResource(new Medicine(name, qty, expiry, mtype));
                    }
                    else if (strcmp(type, "Water") == 0) {
                        char* expiry = strtok(nullptr, "|");
                        if (expiry)
                            addResource(new Water(name, qty, expiry));
                    }
                    else if (strcmp(type, "Shelter") == 0) {
                        char* capStr = strtok(nullptr, "|");
                        if (capStr)
                            addResource(new Shelter(name, qty, stringToInt(capStr)));
                    }
                }
            }
            rFile.close();
            setColor(C_INFO);
            cout << "[+] Loaded inventory (Decrypted)." << endl;
            setColor(C_DEFAULT);
        }

        // Load Donors
        ifstream dFile("donations.txt");
        if (dFile.is_open()) {
            char line[500];
            while (dFile.getline(line, 500)) {
                if (donorCount >= 100) break;
                encryptDecrypt(line);

                char* name = strtok(line, "|");
                char* id = strtok(nullptr, "|");
                char* amtStr = strtok(nullptr, "|");
                char* date = strtok(nullptr, "|");

                if (name && id && amtStr && date) {
                    addDonor(new Donor(name, id, stringToDouble(amtStr), date));
                }
            }
            dFile.close();
            setColor(C_INFO);
            cout << "[+] Loaded " << donorCount << " donors." << endl;
            setColor(C_DEFAULT);
        }
    }
};

int main() {
    showStartScreen();

    AllocationSystem system_rel; // Renamed to avoid confusion with system()
    PredictionSystem predictor;
    UXManager ux;
    Admin admin_obj;
    bool isLoggedIn = false;

    setColor(C_TITLE);
    cout << "\n--- ADMIN PORTAL ACCESS ---" << endl;
    setColor(C_DEFAULT);

    // Admin Login
    char username[50], password[50];
    setColor(C_TITLE);
    cout << "\n--- ADMIN LOGIN ---" << endl;
    setColor(C_PROMPT);
    cout << "Username: ";
    setColor(C_DEFAULT);
    cin >> username;
    setColor(C_PROMPT);
    cout << "Password: ";
    setColor(C_DEFAULT);
    cin >> password;

    if (admin_obj.authenticate(username, password)) {
        isLoggedIn = true;
        setColor(C_SUCCESS);
        cout << "\n[+] Login successful! Welcome, Administrator." << endl;
        setColor(C_DEFAULT);
    }
    else {
        setColor(C_ERROR);
        cout << "\n[!] Invalid credentials! Exiting..." << endl;
        setColor(C_DEFAULT);
        return 0;
    }

    int choice;
    do {
        ux.printMenuHeader();
        if (ux.currentLang == ux.URDU) {
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "1. "; setColor(C_DEFAULT); cout << "Victim Register Karein             "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "2. "; setColor(C_DEFAULT); cout << "Resource Inventory mein Shamil     "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "3. "; setColor(C_DEFAULT); cout << "Tamam Victims Dekhein              "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "4. "; setColor(C_DEFAULT); cout << "Inventory Stock Check Karein       "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "5. "; setColor(C_DEFAULT); cout << "Smart Resource Allocation          "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "6. "; setColor(C_DEFAULT); cout << "Daily Report Banayein              "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "7. "; setColor(C_DEFAULT); cout << "Stock Alert Check Karein           "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "8. "; setColor(C_DEFAULT); cout << "Tamam Data Save Karein             "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "9. "; setColor(C_DEFAULT); cout << "Victim Search (CNIC)               "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "10. "; setColor(C_DEFAULT); cout << "Medical Emergency List             "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "11. "; setColor(C_DEFAULT); cout << "Donation Register Karein           "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "12. "; setColor(C_DEFAULT); cout << "Donors ki List                     "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "13. "; setColor(C_DEFAULT); cout << "Resource Prediction Planning       "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "14. "; setColor(C_DEFAULT); cout << "Regional Hazard Check Karein      "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "15. "; setColor(C_DEFAULT); cout << "Allocation History Dekhein         "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "16. "; setColor(C_DEFAULT); cout << "SMS Alert Bhejein                 "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "17. "; setColor(C_DEFAULT); cout << "Zuban Tabdeel Karein              "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "18. "; setColor(C_DEFAULT); cout << "Emergency Broadcast (Ehtiyat)     "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "19. "; setColor(C_DEFAULT); cout << "Kareebi Relief Center Dhundein    "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "20. "; setColor(C_DEFAULT); cout << "Exit (Band Karein)                "; setColor(C_MENU); cout << "=" << endl;
        }
        else {
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "1. "; setColor(C_DEFAULT); cout << "Register Victim                    "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "2. "; setColor(C_DEFAULT); cout << "Add Resource to Inventory          "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "3. "; setColor(C_DEFAULT); cout << "View All Victims                   "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "4. "; setColor(C_DEFAULT); cout << "View Current Inventory             "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "5. "; setColor(C_DEFAULT); cout << "Smart Resource Allocation          "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "6. "; setColor(C_DEFAULT); cout << "Generate Daily Report              "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "7. "; setColor(C_DEFAULT); cout << "Check Low Stock Alerts             "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "8. "; setColor(C_DEFAULT); cout << "Save All Data                      "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "=  "; setColor(C_TITLE); cout << "9. "; setColor(C_DEFAULT); cout << "Search Victim (CNIC)               "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "10. "; setColor(C_DEFAULT); cout << "Medical Emergency Viewer           "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "11. "; setColor(C_DEFAULT); cout << "Donate & Register Donor            "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "12. "; setColor(C_DEFAULT); cout << "View Donors                        "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "13. "; setColor(C_DEFAULT); cout << "Resource Predictive Planning       "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "14. "; setColor(C_DEFAULT); cout << "Regional Hazard Prediction         "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "15. "; setColor(C_DEFAULT); cout << "View Allocation History            "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "16. "; setColor(C_DEFAULT); cout << "SMS / Email Alerts Simulation      "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "17. "; setColor(C_DEFAULT); cout << "Multi-Language Interface           "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "18. "; setColor(C_DEFAULT); cout << "Emergency Broadcast System         "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "19. "; setColor(C_DEFAULT); cout << "Find Nearest Relief Center         "; setColor(C_MENU); cout << "=" << endl;
            setColor(C_MENU); cout << "= "; setColor(C_TITLE); cout << "20. "; setColor(C_DEFAULT); cout << "Exit                               "; setColor(C_MENU); cout << "=" << endl;
        }
        setColor(C_MENU);
        cout << "==========================================" << endl;
        setColor(C_PROMPT);
        cout << "Enter choice: ";
        setColor(C_DEFAULT);
        cin >> choice;

        switch (choice) {
        case 1: {
            char name[100], cnic[20], contact[20], dtype[50], loc[100];
            int age, fSize;
            bool injured, pregnant, shelter;
            double lat, lon;
            char inp;

            setColor(C_TITLE);
            cout << "\n--- REGISTER NEW VICTIM ---" << endl;
            setColor(C_DEFAULT);
            cin.ignore();
            setColor(C_PROMPT);
            cout << "Name: ";
            setColor(C_DEFAULT);
            cin.getline(name, 100);
            setColor(C_PROMPT);
            cout << "CNIC (13 digits): ";
            setColor(C_DEFAULT);
            cin >> cnic;
            setColor(C_PROMPT);
            cout << "Age: ";
            setColor(C_DEFAULT);
            cin >> age;
            setColor(C_PROMPT);
            cout << "Contact Number: ";
            setColor(C_DEFAULT);
            cin >> contact;
            setColor(C_PROMPT);
            cout << "Family Size: ";
            setColor(C_DEFAULT);
            cin >> fSize;
            setColor(C_PROMPT);
            cout << "Is Injured? (y/n): ";
            setColor(C_DEFAULT);
            cin >> inp;
            injured = (inp == 'y' || inp == 'Y');
            setColor(C_PROMPT);
            cout << "Is Pregnant? (y/n): ";
            setColor(C_DEFAULT);
            cin >> inp;
            pregnant = (inp == 'y' || inp == 'Y');
            setColor(C_PROMPT);
            cout << "Has Shelter? (y/n): ";
            setColor(C_DEFAULT);
            cin >> inp;
            shelter = (inp == 'y' || inp == 'Y');
            cin.ignore();
            setColor(C_PROMPT);
            cout << "Disaster Type (Flood/Earthquake/Fire): ";
            setColor(C_DEFAULT);
            cin.getline(dtype, 50);
            setColor(C_PROMPT);
            cout << "Location: ";
            setColor(C_DEFAULT);
            cin.getline(loc, 100);
            setColor(C_PROMPT);
            cout << "Latitude: ";
            setColor(C_DEFAULT);
            cin >> lat;
            setColor(C_PROMPT);
            cout << "Longitude: ";
            setColor(C_DEFAULT);
            cin >> lon;

            Victim* v = new Victim(name, cnic, age, contact, fSize, injured,
                pregnant, shelter, dtype, loc, lat, lon);
            system_rel.addVictim(v);
            break;
        }

        case 2: {
            int type;
            setColor(C_TITLE);
            cout << "\n--- ADD RESOURCE ---" << endl;
            setColor(C_DEFAULT);
            cout << "1. Food\n2. Medicine\n3. Water\n4. Shelter" << endl;
            setColor(C_PROMPT);
            cout << "Select type: ";
            setColor(C_DEFAULT);
            cin >> type;

            char name[100], expiry[20];
            int qty;

            cin.ignore();
            setColor(C_PROMPT);
            cout << "Item Name: ";
            setColor(C_DEFAULT);
            cin.getline(name, 100);
            setColor(C_PROMPT);
            cout << "Quantity: ";
            setColor(C_DEFAULT);
            cin >> qty;

            // Clear buffer, including 'kg' or other text
            cin.clear();
            while (cin.get() != '\n');

            setColor(C_PROMPT);
            cout << "Expiry Date (YYYY-MM-DD): ";
            setColor(C_DEFAULT);
            cin.getline(expiry, 20);

            if (type == 1) {
                char ftype[50];
                setColor(C_PROMPT);
                cout << "Food Type (Rice/Wheat/etc): ";
                setColor(C_DEFAULT);
                cin.getline(ftype, 50);
                system_rel.addResource(new Food(name, qty, expiry, ftype));
            }
            else if (type == 2) {
                char mtype[50];
                setColor(C_PROMPT);
                cout << "Medicine Type (Painkiller/Antibiotic/etc): ";
                setColor(C_DEFAULT);
                cin.getline(mtype, 50);
                system_rel.addResource(new Medicine(name, qty, expiry, mtype));
            }
            else if (type == 3) {
                system_rel.addResource(new Water(name, qty, expiry));
            }
            else if (type == 4) {
                int cap;
                setColor(C_PROMPT);
                cout << "Capacity per shelter: ";
                setColor(C_DEFAULT);
                cin >> cap;
                system_rel.addResource(new Shelter(name, qty, cap));
            }
            break;
        }

        case 3:
            setColor(C_INFO);
            system_rel.displayAllVictims();
            setColor(C_DEFAULT);
            break;

        case 4:
            setColor(C_INFO);
            system_rel.displayInventory();
            setColor(C_DEFAULT);
            break;

        case 5:
            setColor(C_INFO);
            system_rel.smartAllocate();
            setColor(C_DEFAULT);
            break;

        case 6:
            system_rel.generateReport();
            break;

        case 7:
            system_rel.checkLowStock();
            break;

        case 8:
            system_rel.saveAllData();
            break;

        case 9: {
            char searchCNIC[20];
            setColor(C_PROMPT);
            cout << "Enter CNIC to search: ";
            setColor(C_DEFAULT);
            cin >> searchCNIC;
            system_rel.searchVictimByCNIC(searchCNIC);
            break;
        }

        case 10:
            system_rel.displayMedicalEmergencies();
            break;

        case 11: {
            char dName[100], dID[20], dDate[20];
            double dAmt;
            setColor(C_TITLE);
            cout << "\n===== DONATION REGISTRATION =====\n";
            setColor(C_DEFAULT);
            cin.ignore();
            setColor(C_PROMPT);
            cout << "Donor Name: ";
            setColor(C_DEFAULT);
            cin.getline(dName, 100);
            setColor(C_PROMPT);
            cout << "Donor ID: ";
            setColor(C_DEFAULT);
            cin >> dID;
            setColor(C_PROMPT);
            cout << "Amount ($): ";
            setColor(C_DEFAULT);
            cin >> dAmt;
            setColor(C_PROMPT);
            cout << "Date (DD-MM-YYYY): ";
            setColor(C_DEFAULT);
            cin >> dDate;
            system_rel.addDonor(new Donor(dName, dID, dAmt, dDate));
            break;
        }

        case 12:
            system_rel.displayDonors();
            break;

        case 13:
            system_rel.predictResourceNeeds();
            break;

        case 14: {
            int subChoice;
            setColor(C_TITLE);
            cout << "\n--- REGIONAL HAZARD PREDICTION ---" << endl;
            setColor(C_DEFAULT);
            cout << "1. View All Regions\n2. Search Specific Region" << endl;
            setColor(C_PROMPT);
            cout << "Enter Choice: ";
            setColor(C_DEFAULT);
            cin >> subChoice;
            if (subChoice == 1) predictor.generatePredictionReport();
            else if (subChoice == 2) predictor.searchRegionReport();
            else {
                setColor(C_ERROR);
                cout << "[!] Invalid Choice!" << endl;
                setColor(C_DEFAULT);
            }
            break;
        }

        case 15:
            setColor(C_INFO);
            system_rel.viewAllocations();
            setColor(C_DEFAULT);
            break;

        case 16: {
            char num[20], msg[100];
            setColor(C_TITLE);
            cout << "\n--- SMS ALERT SERVICE ---" << endl;
            setColor(C_DEFAULT);
            setColor(C_PROMPT);
            cout << "Enter Recipient Number: ";
            setColor(C_DEFAULT);
            cin >> num;
            cin.ignore();
            setColor(C_PROMPT);
            cout << "Enter Message: ";
            setColor(C_DEFAULT);
            cin.getline(msg, 100);
            ux.sendAlert(num, msg);
            break;
        }

        case 17:
            ux.changeLanguage();
            break;

        case 18: {
            char bMsg[100];
            setColor(C_TITLE);
            cout << "\n--- GLOBAL EMERGENCY BROADCAST ---" << endl;
            setColor(C_DEFAULT);
            setColor(C_PROMPT);
            cout << "Enter Broadcast Message: ";
            setColor(C_DEFAULT);
            cin.ignore();
            cin.getline(bMsg, 100);
            ux.emergencyBroadcast(bMsg);
            break;
        }

        case 19: {
            double uLat, uLon;
            setColor(C_TITLE);
            cout << "\n--- NEAREST RELIEF CENTER FINDER ---" << endl;
            setColor(C_DEFAULT);
            setColor(C_PROMPT);
            cout << "Enter Your Latitude: ";
            setColor(C_DEFAULT);
            cin >> uLat;
            setColor(C_PROMPT);
            cout << "Enter Your Longitude: ";
            setColor(C_DEFAULT);
            cin >> uLon;
            ReliefService rss;
            rss.findNearest(uLat, uLon);
            break;
        }

        case 20:
            setColor(C_SUCCESS);
            cout << "\n[+] Thank you for using the system. Stay safe!" << endl;
            setColor(C_DEFAULT);
            system_rel.saveAllData();
            break;

        default:
            setColor(C_ERROR);
            cout << "\n[!] Invalid choice!" << endl;
            setColor(C_DEFAULT);
        }
    } while (choice != 20);

    return 0;
}