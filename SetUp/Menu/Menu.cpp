#include "Menu.h"

#include <chrono>

#include "../Routes/IndependentRoutePlanning.h"
#include "../Routes/RestrictedRoutePlanning.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"

#include <fstream>
#include <thread>
#include "../InputOutput/InteractiveInput.h"
#include "../InputOutput/Input.h"
#include "../InputOutput/Output.h"

int optionsMenu() {
    cout << endl << "Hello user!" << endl;
    cout << "Welcome to the Route Planning Tool!" << endl << endl;

    cout << "If you have doubts about the input format, feel free to check the Info section." << endl;
    cout << endl << "Here are the options..." << endl << endl;
    cout.flush();
    for (int i = 2; i > 0; --i) {
        this_thread::sleep_for(chrono::seconds(1));
        cout.flush();
    }


    cout << "----------------------------------------------" << endl;
    cout << "             CHOOSE AN OPTION" << endl;
    cout << "----------------------------------------------" << endl << endl;

    int i;

    do {
        cout << "1: Best Route and Alternative Independent Route " << endl;
        cout << "2: Restricted Route Planning " << endl;
        cout << "3: Environmentally-Friendly Route Planning" << endl;
        cout << "4: Info ! " << endl;
        cout << "5: Exit" << endl;
        cout << "Option: ";
        cin >> i;
        cout << endl << endl;

        if (i > 5) cout << "Invalid input." << endl;
    } while (i > 5);
    return i;
}


template<class T>
void optionBestRoute(Graph<T> *g) {
    string mode;
    int source, destination;

    if (!InterInputBestRoute(mode, source, destination)) {
        cout << "Invalid input. Please try again." << endl;
        return;
    }
    pair<vector<T>, int> solBestRoute = BestRoute(g, source, destination);

    pair<vector<T>, int> solAlternativeRoute = AlternativeRoute(g, solBestRoute, source, destination);

    if (OutputBestRoute(g, source, destination, solBestRoute, solAlternativeRoute)) {
        int option = optionsMenu();
        handleMenuOption(option, g);
    }
}

// Explicit instantiation for the required type (e.g., int)
template void optionBestRoute<int>(Graph<int> *g);


template<class T>
void optionRestrictedRoute(Graph<T> *g) {
    string mode;
    int source, destination;
    vector<int> avoidNodes;
    vector<pair<int, int> > avoidSegments;
    int includeNode;
    vector<T> route;
    int totalTime;
    bool flag;

    if (!InterInputRestrictedRoute(mode, source, destination, avoidNodes, avoidSegments, includeNode)) {
        cout << "Invalid input. Please try again." << endl;
        return;
    }

    RestrictedRoutePlanning(g, source, destination, avoidNodes, avoidSegments, includeNode, route, totalTime, flag);

    if (OutputRestrictedRoute(g, source, destination, route, totalTime, avoidNodes, avoidSegments)) {
        int option = optionsMenu();
        handleMenuOption(option, g);
    }
}

template void optionRestrictedRoute<int>(Graph<int> *g);


template<class T>
void optionEnvironmentalRoute(Graph<T> *g) {
    string mode;
    int source, destination, maxWalkTime, parkingNode, totalTime;
    vector<int> avoidNodes;
    vector<pair<int, int> > avoidSegments;
    pair<vector<int>, int> drivingRoute, walkingRoute;
    vector<ApproximateSolution<int> > approximateSolutions;

    if (!InterInputEnvironmetalRoute(mode, source, destination, maxWalkTime, avoidNodes, avoidSegments)) {
        cout << "Invalid input. Please try again." << endl;
        return;
    }

    EnvironmentallyFriendlyBestRoute(g, source, destination, maxWalkTime, avoidNodes, avoidSegments,
                                     drivingRoute, parkingNode, walkingRoute, totalTime,
                                     approximateSolutions);

    bool shouldShowMenu = OutputBestEnvironmentallyFriendlyRoute(g, source, destination,
                                                                 drivingRoute, walkingRoute,
                                                                 parkingNode, totalTime, maxWalkTime,
                                                                 approximateSolutions);

    if (shouldShowMenu) {
        int option = optionsMenu();
        handleMenuOption(option, g);
    }
}

template void optionEnvironmentalRoute<int>(Graph<int> *g);


void optionInfo(Graph<int> *g) {
    cout << endl << "=============================================\n";
    cout << "       ROUTE PLANNER - INPUT INFO        \n";
    cout << "=============================================\n\n";

    cout << "1. BEST ROUTE AND ALTERNATIVE INDEPENDENT ROUTE (DRIVING)\n";
    cout << endl;
    cout << "   Mode: driving\n";
    cout << "   Source: <node_number>\n";
    cout << "   Destination: <node_number>\n";

    cout << endl << "2. RESTRICTED ROUTE PLANNING\n";
    cout << endl;
    cout << "   Mode: driving\n";
    cout << "   Source: <node_number>\n";
    cout << "   Destination: <node_number>\n";
    cout << "   AvoidNodes: <comma_separated_node_numbers> (optional)\n";
    cout << "   AvoidSegments: <comma_separated_pairs> e.g., (3,2),(7,8) (optional)\n";
    cout << "   IncludeNode: <node_number> (optional)\n";

    cout << endl << "3. ENVIRONMENTALLY-FRIENDLY ROUTE PLANNING (DRIVING + WALKING)\n";
    cout << endl;
    cout << "   Mode: driving-walking\n";
    cout << "   Source: <node_number>\n";
    cout << "   Destination: <node_number>\n";
    cout << "   MaxWalkTime: <minutes> (maximum walking time allowed)\n";
    cout << "   AvoidNodes: <comma_separated_node_numbers> (optional)\n";
    cout << "   AvoidSegments: <comma_separated_pairs> (optional)\n";

    cout << endl << "NOTES:\n";
    cout <<
            "- Please put the input in the 'Input' folder of the project before running. If it isn't to your liking go change it now!\n";
    cout << "  The input files have their name correspond to the option you will choose so be aware of that." << endl;
    cout << "- For empty optional fields, leave them blank.\n";
    cout << "=============================================\n\n";

    cout << "======================" << endl;
    cout << "BATCH MODE INFO" << endl;
    cout << "======================" << endl << endl;
    cout << "Usage:\n";
    cout << "1. Interactive Menu Mode:\n";
    cout << "   ./route_planner\n\n";
    cout << "2. Batch Mode:\n";
    cout << "   ./route_planner input.txt output.txt\n\n";
    cout << "Example:\n";
    cout << "   ./route_planner Input/input.txt Output/output.txt\n\n";
    cout << "Notes:\n";
    cout << "- Batch mode processes input file and writes results to output file\n";
    cout << "- Input file should be in the Input folder\n";
    cout << "- Output will be written to the specified output file\n";
    cout << "- Program exits after processing in batch mode\n";
    cout << "======================" << endl;

    cout << "Are you ready to go back to the menu? [y/n] ";
    char response;
    cin >> response;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    if (response == 'y' || response == 'Y') {
        cout << "Redirecting you to the menu in 3 seconds...";
        cout.flush();
        for (int i = 3; i > 0; --i) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << " " << i << "...";
            cout.flush();
        }
        cout << endl << endl;

        int option = optionsMenu();
        handleMenuOption(option, g);
    } else {
        cout << endl << "Ok! Goodbye!" << endl;
        cout << "Exiting in... ";
        cout.flush();
        for (int i = 3; i > 0; --i) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << " " << i << "...";
            cout.flush();
        }
        cout << endl << endl;
    }
}


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
            optionInfo(g);
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            break;
    }
}
