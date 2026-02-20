#ifndef RELIEFSERVICE_H
#define RELIEFSERVICE_H

#include "Utils.h"

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
            double dist = sqrt(pow(centers[i].latitude - userLat, 2) + pow(centers[i].longitude - userLon, 2));
            if (dist < minDistance) {
                minDistance = dist;
                nearestIdx = i;
            }
        }
        cout << "[+] Found Nearest Center!" << endl;
        cout << "Name: " << centers[nearestIdx].name << endl;
        cout << "Coordinates: " << centers[nearestIdx].latitude << ", " << centers[nearestIdx].longitude << endl;
        cout << "Approximate Distance: " << minDistance * 111 << " km away" << endl;
        cout << "---------------------------------------" << endl;
    }
};

#endif
