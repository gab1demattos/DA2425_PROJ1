#include "Output.h"
#include <iostream>
#include <vector>

using namespace std;

/**
 * Outputs the best driving route in the specified format.
 * 
 * @param source The starting point of the route.
 * @param destination The destination point of the route.
 * @param bestRoute A vector containing the nodes in the best route.
 * @param totalCost The total cost (e.g., distance or time) of the best route.
 */

void OutputBestRoute(int source, int destination, const pair<vector<int>,int>& solBestRoute, const pair<vector<int>,int>& solALternativeRoute) {
    vector<int> bestRoute = solBestRoute.first;
    int totalCost = solBestRoute.second;

    vector<int> alternativeRoute = solALternativeRoute.first;
    int alternativeTime = solALternativeRoute.second;

    // Output the source and destination
    cout << "Source:" << source << endl;
    cout << "Destination:" << destination << endl;

    // Output the best driving route
    cout << "BestDrivingRoute:";
    for (size_t i = 0; i < bestRoute.size(); ++i) {
        cout << bestRoute[i];
        if (i < bestRoute.size() - 1) {
            cout << ",";
        }
    }
    cout << "(" << totalCost << ")" << endl;

    if (alternativeRoute.empty()) {
        cout << "AlternativeRoute:None" << endl;
    } else {
        cout << "AlternativeRoute:";
        for (size_t i = 0; i < alternativeRoute.size(); ++i) {
            cout << alternativeRoute[i];
            if (i < alternativeRoute.size() - 1) {
                cout << ",";
            }
        }
        cout << "(" << alternativeTime << ")" << endl;
    }
}



void OutputBestEnvironmentallyFriendlyRoute(int source, int destination, const pair<vector<int>,int>& solBestDrivingRoute, const pair<vector<int>,int>& solBestWalkingRoute, const int &parkingNode, const int &totalTime) {
    vector<int> bestDrivingRoute = solBestDrivingRoute.first;
    int drivingTime = solBestDrivingRoute.second;

    vector<int> bestWalkingRoute = solBestWalkingRoute.first;
    int walkingTime = solBestWalkingRoute.second;

    // Output the source and destination
    cout << "Source:" << source << endl;
    cout << "Destination:" << destination << endl;


    cout << "DrivingRoute:";
    for (size_t i = 0; i < bestDrivingRoute.size(); ++i) {
        cout << bestDrivingRoute[i];
        if (i < bestDrivingRoute.size() - 1) {
            cout << ",";
        }
    }
    cout << "(" << drivingTime << ")" << endl;

    cout << "ParkingNode:" << parkingNode << endl;

    cout << "WalkingRoute:";
    for (size_t i = 0; i < bestWalkingRoute.size(); ++i) {
        cout << bestWalkingRoute[i];
        if (i < bestWalkingRoute.size() - 1) {
            cout << ",";
        }
    }
    cout << "(" << walkingTime << ")" << endl;

    cout << "TotalTime:" << totalTime << endl;
}