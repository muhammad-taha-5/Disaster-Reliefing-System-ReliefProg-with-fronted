#include "AllocationSystem.h"
#include "PredictionSystem.h"
#include "UXManager.h"
#include "ReliefService.h"
#include "Admin.h"

int main() {
    showStartScreen();

    AllocationSystem system_rel;
    PredictionSystem predictor;
    UXManager ux;
    Admin admin_obj;
    bool isLoggedIn = false;

    setColor(C_TITLE);
    cout << "\n--- ADMIN PORTAL ACCESS ---" << endl;
    setColor(C_DEFAULT);

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
    } else {
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
        } else {
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
            setColor(C_TITLE); cout << "\n--- REGISTER NEW VICTIM ---" << endl;
            setColor(C_DEFAULT); cin.ignore();
            setColor(C_PROMPT); cout << "Name: "; setColor(C_DEFAULT); cin.getline(name, 100);
            setColor(C_PROMPT); cout << "CNIC (13 digits): "; setColor(C_DEFAULT); cin >> cnic;
            setColor(C_PROMPT); cout << "Age: "; setColor(C_DEFAULT); cin >> age;
            setColor(C_PROMPT); cout << "Contact Number: "; setColor(C_DEFAULT); cin >> contact;
            setColor(C_PROMPT); cout << "Family Size: "; setColor(C_DEFAULT); cin >> fSize;
            setColor(C_PROMPT); cout << "Is Injured? (y/n): "; setColor(C_DEFAULT); cin >> inp; injured = (inp == 'y' || inp == 'Y');
            setColor(C_PROMPT); cout << "Is Pregnant? (y/n): "; setColor(C_DEFAULT); cin >> inp; pregnant = (inp == 'y' || inp == 'Y');
            setColor(C_PROMPT); cout << "Has Shelter? (y/n): "; setColor(C_DEFAULT); cin >> inp; shelter = (inp == 'y' || inp == 'Y');
            cin.ignore();
            setColor(C_PROMPT); cout << "Disaster Type (Flood/Earthquake/Fire): "; setColor(C_DEFAULT); cin.getline(dtype, 50);
            setColor(C_PROMPT); cout << "Location: "; setColor(C_DEFAULT); cin.getline(loc, 100);
            setColor(C_PROMPT); cout << "Latitude: "; setColor(C_DEFAULT); cin >> lat;
            setColor(C_PROMPT); cout << "Longitude: "; setColor(C_DEFAULT); cin >> lon;
            system_rel.addVictim(new Victim(name, cnic, age, contact, fSize, injured, pregnant, shelter, dtype, loc, lat, lon));
            break;
        }
        case 2: {
            int type;
            setColor(C_TITLE); cout << "\n--- ADD RESOURCE ---" << endl;
            setColor(C_DEFAULT); cout << "1. Food\n2. Medicine\n3. Water\n4. Shelter" << endl;
            setColor(C_PROMPT); cout << "Select type: "; setColor(C_DEFAULT); cin >> type;
            char name[100], expiry[20]; int qty;
            cin.ignore();
            setColor(C_PROMPT); cout << "Item Name: "; setColor(C_DEFAULT); cin.getline(name, 100);
            setColor(C_PROMPT); cout << "Quantity: "; setColor(C_DEFAULT); cin >> qty;
            cin.clear(); while (cin.get() != '\n');
            setColor(C_PROMPT); cout << "Expiry Date (YYYY-MM-DD): "; setColor(C_DEFAULT); cin.getline(expiry, 20);
            if (type == 1) {
                char ftype[50]; setColor(C_PROMPT); cout << "Food Type: "; setColor(C_DEFAULT); cin.getline(ftype, 50);
                system_rel.addResource(new Food(name, qty, expiry, ftype));
            } else if (type == 2) {
                char mtype[50]; setColor(C_PROMPT); cout << "Medicine Type: "; setColor(C_DEFAULT); cin.getline(mtype, 50);
                system_rel.addResource(new Medicine(name, qty, expiry, mtype));
            } else if (type == 3) system_rel.addResource(new Water(name, qty, expiry));
            else if (type == 4) {
                int cap; setColor(C_PROMPT); cout << "Capacity per shelter: "; setColor(C_DEFAULT); cin >> cap;
                system_rel.addResource(new Shelter(name, qty, cap));
            }
            break;
        }
        case 3: system_rel.displayAllVictims(); break;
        case 4: system_rel.displayInventory(); break;
        case 5: system_rel.smartAllocate(); break;
        case 6: system_rel.generateReport(); break;
        case 7: system_rel.checkLowStock(); break;
        case 8: system_rel.saveAllData(); break;
        case 9: {
            char searchCNIC[20]; setColor(C_PROMPT); cout << "Enter CNIC: "; setColor(C_DEFAULT); cin >> searchCNIC;
            system_rel.searchVictimByCNIC(searchCNIC); break;
        }
        case 10: system_rel.displayMedicalEmergencies(); break;
        case 11: {
            char dName[100], dID[20], dDate[20]; double dAmt;
            setColor(C_TITLE); cout << "\n===== DONATION REGISTRATION =====\n";
            cin.ignore(); setColor(C_PROMPT); cout << "Donor Name: "; setColor(C_DEFAULT); cin.getline(dName, 100);
            setColor(C_PROMPT); cout << "Donor ID: "; setColor(C_DEFAULT); cin >> dID;
            setColor(C_PROMPT); cout << "Amount ($): "; setColor(C_DEFAULT); cin >> dAmt;
            setColor(C_PROMPT); cout << "Date: "; setColor(C_DEFAULT); cin >> dDate;
            system_rel.addDonor(new Donor(dName, dID, dAmt, dDate)); break;
        }
        case 12: system_rel.displayDonors(); break;
        case 13: system_rel.predictResourceNeeds(); break;
        case 14: {
            int subChoice; setColor(C_TITLE); cout << "\n--- REGIONAL HAZARD PREDICTION ---" << endl;
            setColor(C_DEFAULT); cout << "1. View All\n2. Search Specific" << endl;
            setColor(C_PROMPT); cout << "Enter Choice: "; setColor(C_DEFAULT); cin >> subChoice;
            if (subChoice == 1) predictor.generatePredictionReport();
            else if (subChoice == 2) predictor.searchRegionReport();
            break;
        }
        case 15: system_rel.viewAllocations(); break;
        case 16: {
            char num[20], msg[100]; setColor(C_TITLE); cout << "\n--- SMS ALERT SERVICE ---" << endl;
            setColor(C_PROMPT); cout << "Recipient Number: "; setColor(C_DEFAULT); cin >> num;
            cin.ignore(); setColor(C_PROMPT); cout << "Message: "; setColor(C_DEFAULT); cin.getline(msg, 100);
            ux.sendAlert(num, msg); break;
        }
        case 17: ux.changeLanguage(); break;
        case 18: {
            char bMsg[100]; setColor(C_TITLE); cout << "\n--- GLOBAL EMERGENCY BROADCAST ---" << endl;
            setColor(C_PROMPT); cout << "Broadcast Message: "; setColor(C_DEFAULT); cin.ignore(); cin.getline(bMsg, 100);
            ux.emergencyBroadcast(bMsg); break;
        }
        case 19: {
            double uLat, uLon; setColor(C_TITLE); cout << "\n--- NEAREST RELIEF CENTER FINDER ---" << endl;
            setColor(C_PROMPT); cout << "Latitude: "; setColor(C_DEFAULT); cin >> uLat;
            setColor(C_PROMPT); cout << "Longitude: "; setColor(C_DEFAULT); cin >> uLon;
            ReliefService rss; rss.findNearest(uLat, uLon); break;
        }
        case 20: setColor(C_SUCCESS); cout << "\n[+] Thank you for using the system. Stay safe!" << endl; setColor(C_DEFAULT); system_rel.saveAllData(); break;
        default: setColor(C_ERROR); cout << "\n[!] Invalid choice!" << endl; setColor(C_DEFAULT);
        }
    } while (choice != 20);

    return 0;
}
