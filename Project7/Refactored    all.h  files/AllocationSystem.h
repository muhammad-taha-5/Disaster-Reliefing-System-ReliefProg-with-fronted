#ifndef ALLOCATIONSYSTEM_H
#define ALLOCATIONSYSTEM_H

#include "Victim.h"
#include "Food.h"
#include "Medicine.h"
#include "Water.h"
#include "Shelter.h"
#include "Donor.h"

class AllocationSystem {
private:
    Victim* victims[100];
    Resource* inventory[50];
    Donor* donors[100];
    int victimCount;
    int resourceCount;
    int donorCount;
    char* currentDisaster;

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
        for (int i = 0; i < victimCount; i++) if (victims[i]) delete victims[i];
        for (int i = 0; i < resourceCount; i++) if (inventory[i]) delete inventory[i];
        for (int i = 0; i < donorCount; i++) if (donors[i]) delete donors[i];
        if (currentDisaster) delete[] currentDisaster;
    }

    void setDisasterType(const char* type) { deepCopy(currentDisaster, type); }

    bool checkDuplicate(const char* cnic) {
        for (int i = 0; i < victimCount; i++) {
            if (strcmp(victims[i]->getCNIC(), cnic) == 0) return true;
        }
        return false;
    }

    void addVictim(Victim* victim) {
        if (victimCount < 100) {
            if (checkDuplicate(victim->getCNIC())) {
                setColor(C_WARNING);
                cout << "\n[!] DUPLICATE DETECTED! This CNIC is already registered." << endl;
                setColor(C_DEFAULT);
                delete victim;
                return;
            }
            victims[victimCount++] = victim;
            setColor(C_SUCCESS);
            cout << "\n[+] Victim registered successfully! Priority Score: " << victim->getPriorityScore() << endl;
            setColor(C_DEFAULT);
        } else {
            setColor(C_ERROR);
            cout << "\n[!] Victim list is full!" << endl;
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
        } else {
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
        } else {
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
        sortByPriority();
        setColor(C_TITLE);
        cout << "\n========== SMART ALLOCATION PROCESS ==========" << endl;
        setColor(C_DEFAULT);
        int helpedCount = 0;
        for (int i = 0; i < victimCount; i++) {
            if (victims[i]->isHelped()) continue;
            int familySize = victims[i]->getFamilySize();
            bool allocated = false;
            cout << "\n> Processing: " << victims[i]->getName() << " (Priority: " << victims[i]->getPriorityScore() << ")" << endl;

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
            } else {
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
                cout << "[!] LOW STOCK: " << inventory[i]->getItemName() << " - Only " << inventory[i]->getQuantity() << " remaining!" << endl;
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
        for (int i = 0; i < resourceCount; i++) inventory[i]->display();
        setColor(C_TITLE);
        cout << "=======================================" << endl;
        setColor(C_DEFAULT);
    }

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

    void displayMedicalEmergencies() {
        setColor(C_TITLE);
        cout << "\n===== MEDICAL EMERGENCY LIST =====\n";
        setColor(C_DEFAULT);
        bool found = false;
        for (int i = 0; i < victimCount; i++) {
            if (victims[i]->getInjuredStatus() || victims[i]->getPregnantStatus()) {
                cout << "Name: " << victims[i]->getName() << " | Condition: " << (victims[i]->getInjuredStatus() ? "Injured " : "") << (victims[i]->getPregnantStatus() ? "Pregnant" : "") << endl;
                found = true;
            }
        }
        if (!found) cout << "No medical emergencies reported." << endl;
    }

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
                if (victims[i]->getInjuredStatus() || victims[i]->getPregnantStatus()) totalMedicineNeeded += 5;
            }
        }
        cout << "Predicted Demand (Pending Victims):\n";
        cout << " - Food Needed: " << totalFoodNeeded << " kg\n";
        cout << " - Water Needed: " << totalWaterNeeded << " liters\n";
        cout << " - Medicine Needed: " << totalMedicineNeeded << " units\n";
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
        for (int i = 0; i < donorCount; i++) donors[i]->display();
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
            if (victims[i]->getInjuredStatus() || victims[i]->getPregnantStatus()) medicalEmergencies++;
        }
        file << "Families Helped: " << helpedCount << endl;
        file << "Medical Emergencies: " << medicalEmergencies << endl;
        file << "Remaining Stock:" << endl;
        for (int i = 0; i < resourceCount; i++) file << "  - " << inventory[i]->getItemName() << ": " << inventory[i]->getQuantity() << endl;
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
        char bom[3];
        file.read(bom, 3);
        if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF)) file.seekg(0);
        setColor(C_TITLE);
        cout << "\n===== ALLOCATION HISTORY (DECRYPTED) =====" << endl;
        setColor(C_DEFAULT);
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
                cout << name;
                int len = strlen(name);
                for (int k = 0; k < (20 - len); k++) cout << " ";
                cout << cnic;
                len = strlen(cnic);
                for (int k = 0; k < (16 - len); k++) cout << " ";
                cout << fsize << "         ";
                if (prio) cout << prio << "        "; else cout << "N/A       ";
                if (status) cout << status; else cout << "HELPED";
                cout << endl;
            }
        }
        file.close();
        cout << "==================================================================" << endl;
    }

    void saveAllData() {
        ofstream vFile("victims.txt");
        if (vFile.is_open()) {
            for (int i = 0; i < victimCount; i++) victims[i]->saveToFile(vFile);
            vFile.close();
        }
        ofstream rFile("inventory.txt");
        if (rFile.is_open()) {
            for (int i = 0; i < resourceCount; i++) inventory[i]->saveToFile(rFile);
            rFile.close();
        }
        ofstream dFile("donations.txt");
        if (dFile.is_open()) {
            for (int i = 0; i < donorCount; i++) donors[i]->saveToFile(dFile);
            dFile.close();
        }
        setColor(C_SUCCESS);
        cout << "\n[+] All data saved (ENCRYPTED) successfully!" << endl;
        setColor(C_DEFAULT);
    }

    void loadData() {
        ifstream vFile("victims.txt");
        if (vFile.is_open()) {
            char bom[3];
            vFile.read(bom, 3);
            if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF)) vFile.seekg(0);
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
                    if (receivedStr && stringToInt(receivedStr) == 1) v->markAsHelped();
                    victims[victimCount++] = v;
                }
            }
            vFile.close();
        }
        ifstream rFile("inventory.txt");
        if (rFile.is_open()) {
            char bom[3];
            rFile.read(bom, 3);
            if (!(bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF)) rFile.seekg(0);
            char line[500];
            while (rFile.getline(line, 500)) {
                if (resourceCount >= 50) break;
                encryptDecrypt(line);
                char* type = strtok(line, "|");
                char* name = strtok(nullptr, "|");
                char* qtyStr = strtok(nullptr, "|");
                if (type && name && qtyStr) {
                    int qty = stringToInt(qtyStr);
                    if (strcmp(type, "Food") == 0) {
                        char* expiry = strtok(nullptr, "|");
                        char* ftype = strtok(nullptr, "|");
                        if (expiry && ftype) addResource(new Food(name, qty, expiry, ftype));
                    } else if (strcmp(type, "Medicine") == 0) {
                        char* expiry = strtok(nullptr, "|");
                        char* mtype = strtok(nullptr, "|");
                        if (expiry && mtype) addResource(new Medicine(name, qty, expiry, mtype));
                    } else if (strcmp(type, "Water") == 0) {
                        char* expiry = strtok(nullptr, "|");
                        if (expiry) addResource(new Water(name, qty, expiry));
                    } else if (strcmp(type, "Shelter") == 0) {
                        char* capStr = strtok(nullptr, "|");
                        if (capStr) addResource(new Shelter(name, qty, stringToInt(capStr)));
                    }
                }
            }
            rFile.close();
        }
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
                if (name && id && amtStr && date) addDonor(new Donor(name, id, stringToDouble(amtStr), date));
            }
            dFile.close();
        }
    }
};

#endif
