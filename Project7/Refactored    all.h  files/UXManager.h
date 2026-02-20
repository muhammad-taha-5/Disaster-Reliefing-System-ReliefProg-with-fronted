#ifndef UXMANAGER_H
#define UXMANAGER_H

#include "Utils.h"

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
        } else if (currentLang == SPANISH) {
            cout << "\n==========================================" << endl;
            cout << "=           MEN\xDA PRINCIPAL               =" << endl;
            cout << "==========================================" << endl;
        } else {
            cout << "\n==========================================" << endl;
            cout << "=           MAIN MENU                    =" << endl;
            cout << "==========================================" << endl;
        }
        setColor(C_DEFAULT);
    }
};

#endif
