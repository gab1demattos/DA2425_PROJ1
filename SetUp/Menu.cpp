#include "Menu.h"
#include "IndependentRoutePlanning.h"
#include "EnvironmentallyFriendlyRoutePlanning.h"
#include "RestrictedRoutePlanning.h"

#include <sstream>
#include <fstream>

#include "Input.h"
#include "Output.h"


int optionsMenu() {

    cout << "----------------------------------------------" << endl;
    cout << "             CHOOSE AN OPTION" << endl;
    cout << "----------------------------------------------" << endl << endl;

    int i;

    do {
        cout << "1: Best Route and Alternative Independent Route " << endl;
        cout << "2: Restricted Route Planning " << endl;
        cout << "3: Environmentally-Friendly Route Planning" << endl;
        cout << "4: Exit" << endl;
        cout << "Option: ";
        cin >> i;
        cout << endl << endl;

        if (i > 4) cout << "Invalid input." << endl;
    } while (i > 4);
    return i;
}

template<class T>
void optionBestRoute(Graph<T> *g) {
    string mode;
    int source, destination;

    // Get input values
    if (!InputBestRoute(mode, source, destination)) {
        return; // Stop if input is invalid
    }

    pair<vector<T>,int> solBestRoute = BestRoute(g,source, destination);

    pair<vector<T>,int> solAlternativeRoute = AlternativeRoute(g, solBestRoute, source, destination);

    bool shouldShowMenu = OutputBestRoute(source, destination, solBestRoute, solAlternativeRoute);

    if (shouldShowMenu) {
        int option = optionsMenu();
        handleMenuOption(option, g);
    }
}

// Explicit instantiation for the required type (e.g., int)
template void optionBestRoute<int>(Graph<int> *g);


template<class T>
void optionRestrictedRoute(Graph<T> *g){
    string mode;
    int source, destination;
    vector<int> avoidNodes;
    vector<pair<int, int> > avoidSegments;
    int includeNode;
    vector<T> route;
    int totalTime;

    // Get input values
    if (!InputRestrictedRoute(mode, source, destination, avoidNodes, avoidSegments, includeNode)){
        return; // Stop if input is invalid
    }

    RestrictedRoutePlanning(g, source, destination, avoidNodes, avoidSegments, includeNode, route, totalTime);
    bool shouldShowMenu = OutputRestrictedRoute(source, destination, route, totalTime);

    if (shouldShowMenu) {
        int option = optionsMenu();
        handleMenuOption(option, g);
    }
}

template void optionRestrictedRoute<int>(Graph<int> *g);

template<class T>
void optionEnvironmentalRoute(Graph<T>* g) {
    string mode;
    int source, destination, maxWalkTime, parkingNode, totalTime;
    vector<int> avoidNodes;
    vector<pair<int, int>> avoidSegments;
    pair<vector<int>,int> drivingRoute, walkingRoute;
    vector<ApproximateSolution<int>> approximateSolutions;

    if (!InputEnvironmentalRoute(mode, source, destination, maxWalkTime, avoidNodes, avoidSegments)) {
        return;
    }

    // Update the function call to include approximateSolutions
    EnvironmentallyFriendlyBestRoute(g, source, destination, maxWalkTime, avoidNodes, avoidSegments,
                                   drivingRoute, parkingNode, walkingRoute, totalTime,
                                   approximateSolutions);

    bool shouldShowMenu = OutputBestEnvironmentallyFriendlyRoute(source, destination,
                                                              drivingRoute, walkingRoute,
                                                              parkingNode, totalTime, maxWalkTime,
                                                              approximateSolutions);

    if (shouldShowMenu) {
        int option = optionsMenu();
        handleMenuOption(option, g);
    }
}

template void optionEnvironmentalRoute<int>(Graph<int> *g);

template<class T>
void handleMenuOption(int option, Graph<T> *g) {
    switch (option) {
        case 1:
            optionBestRoute(g);
        break;
        case 2:
            optionRestrictedRoute(g);
        break;
        case 3:
            optionEnvironmentalRoute(g);
        break;
        case 4:
            cout << "Exiting..." << endl;
        break;
        default:
            break;
    }
}