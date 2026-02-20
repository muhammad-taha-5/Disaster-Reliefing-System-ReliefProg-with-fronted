#ifndef PREDICTIONSYSTEM_H
#define PREDICTIONSYSTEM_H

#include "Utils.h"

struct RegionData {
    char name[50];
    double rainfall;
    double temperature;
    double seismicActivity;
    double riverLevel;
    double populationDensity;
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
            return;
        }
        infile.close();

        ofstream outfile("region_data.txt");
        if (outfile.is_open()) {
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
                encryptDecrypt(lines[i]);
                outfile << lines[i] << endl;
            }
            outfile.close();
            cout << "[+] Generated mock regional data file: region_data.txt" << endl;
        }
    }

    void loadRegionalData() {
        generateMockData();
        ifstream file("region_data.txt");
        regionCount = 0;

        if (file.is_open()) {
            char line[500];
            while (file.getline(line, 500)) {
                if (regionCount >= 20) break;
                encryptDecrypt(line);
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
        if (!found) cout << "[!] No prediction data found for region: " << searchName << endl;
        else cout << "[+] Result saved to 'region_search_result.txt'" << endl;
        rFile.close();
    }

private:
    void displayRegionReport(int i, ofstream& rFile) {
        RegionData& r = regions[i];
        int riskScore = 0;
        char riskLevel[20] = "LOW";
        char prediction[100] = "Normal Conditions";
        if (r.rainfall > 150) riskScore += 30;
        if (r.riverLevel > 6.0) riskScore += 25;
        if (r.seismicActivity > 5.0) riskScore += 40;
        if (r.temperature > 42.0) riskScore += 20;
        int levelColor = C_SUCCESS;
        if (riskScore >= 60) {
            strcpy(riskLevel, "CRITICAL");
            levelColor = C_ERROR;
        } else if (riskScore >= 30) {
            strcpy(riskLevel, "HIGH");
            levelColor = C_WARNING;
        } else if (riskScore >= 15) {
            strcpy(riskLevel, "MODERATE");
            levelColor = C_TITLE;
        }
        if (r.seismicActivity > 5.0) strcpy(prediction, "Earthquake Warning!");
        else if (r.rainfall > 200 || r.riverLevel > 7.0) strcpy(prediction, "Severe Flooding Imminent");
        else if (r.rainfall > 100) strcpy(prediction, "Flood Alert");
        else if (r.temperature > 40.0) strcpy(prediction, "Heatwave Warning");
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
        if (rFile.is_open()) {
            rFile << "Region: " << r.name << endl;
            rFile << "Risk: " << riskLevel << " (" << riskScore << ")" << endl;
            rFile << "Prediction: " << prediction << endl;
            rFile << "-----------------------------" << endl;
        }
    }
};

#endif
