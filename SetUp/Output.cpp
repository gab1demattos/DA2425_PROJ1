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
void outputBestRoute(int source, int destination, const vector<int>& bestRoute, int totalCost) {
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
}