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
    cout << "       ROUTE PLANNER - INPUT INFORMATION       \n";
    cout << "=============================================\n\n";

    cout << "Choose your input method:\n";
    cout << "1. Batch Mode (file input)\n";
    cout << "2. Interactive Menu (console input)\n";
    cout << "\nEnter your choice (1 or 2): ";

    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    if (choice == 1) {
        // Batch Mode Information
        cout << endl << "======================" << endl;
        cout << "BATCH MODE INSTRUCTIONS" << endl;
        cout << "======================" << endl << endl;

        cout << "1. BEST ROUTE\n";
        cout << "   Required format:\n";
        cout << "   Mode: driving\n";
        cout << "   Source: <integer_node_id>\n";
        cout << "   Destination: <integer_node_id>\n\n";

        cout << "2. RESTRICTED ROUTE\n";
        cout << "   Required format:\n";
        cout << "   Mode: driving\n";
        cout << "   Source: <integer_node_id>\n";
        cout << "   Destination: <integer_node_id>\n";
        cout << "   AvoidNodes: <comma_separated_integers> (optional)\n";
        cout << "   AvoidSegments: <comma_separated_pairs> e.g., (3,2),(7,8) (optional)\n";
        cout << "   IncludeNode: <integer_node_id> (optional)\n\n";

        cout << "3. ENVIRONMENTALLY-FRIENDLY ROUTE\n";
        cout << "   Required format:\n";
        cout << "   Mode: driving-walking\n";
        cout << "   Source: <integer_node_id>\n";
        cout << "   Destination: <integer_node_id>\n";
        cout << "   MaxWalkTime: <integer_minutes>\n";
        cout << "   AvoidNodes: <comma_separated_integers> (optional)\n";
        cout << "   AvoidSegments: <comma_separated_pairs> (optional)\n\n";

        cout << "USAGE INSTRUCTIONS:\n";
        cout << "1. Place your input file in the 'Build' folder\n";
        cout << "2. Run the program in batch mode:\n";
        cout << "   cd build\n";
        cout << "   make\n";
        cout << "   ./route_planner inputFile.txt outputFile.txt\n";
        cout << "3. Results will be saved to the specified output file\n";
        cout << "4. For empty optional fields, leave them blank\n";
        cout << "======================" << endl;
    }
    else if (choice == 2) {
        // Interactive Menu Information
        cout << endl << "============================" << endl;
        cout << "INTERACTIVE MENU INSTRUCTIONS" << endl;
        cout << "============================" << endl << endl;

        cout << "1. BEST INDEPENDENT ROUTE (DRIVING)\n";
        cout << "   - Mode has to be 'driving'\n";
        cout << "   - Source node: Enter an integer node ID\n";
        cout << "   - Destination node: Enter an integer node ID\n\n";

        cout << "2. RESTRICTED ROUTE PLANNING\n";
        cout << "   - Mode has to be 'driving'\n";
        cout << "   - Source node: Enter an integer node ID\n";
        cout << "   - Destination node: Enter an integer node ID\n";
        cout << "   - AvoidNodes: Enter integers separated by spaces (optional)\n";
        cout << "     Example: 3 5 7\n";
        cout << "   - AvoidSegments: Enter pairs with a comma inside and a space between (optional)\n";
        cout << "     Example: 3,2 7,8 1,4\n";
        cout << "   - IncludeNode: Enter an integer node ID (optional)\n\n";

        cout << "3. ENVIRONMENTALLY-FRIENDLY ROUTE (DRIVING + WALKING)\n";
        cout << "   - Mode has to be 'driving-walking'\n";
        cout << "   - Source node: Enter an integer node ID\n";
        cout << "   - Destination node: Enter an integer node ID\n";
        cout << "   - MaxWalkTime: Enter an integer (minutes)\n";
        cout << "   - AvoidNodes: Enter integers separated by spaces (optional)\n";
        cout << "     Example: 2 4 6\n";
        cout << "   - AvoidSegments: Enter pairs with a comma inside and a space between (optional)\n";
        cout << "     Example: 1,3 5,2 4,7\n\n";

        cout << "NOTES:\n";
        cout << "- For optional fields, you can press Enter to skip\n";
        cout << "- All node IDs must be valid integers from the graph\n";
        cout << "============================" << endl;
    }
    else {
        cout << "Invalid choice!\n";
    }

    // Return to menu after a delay
    cout << "\nReturning to main menu in 3 seconds...";
    cout.flush();
    for (int i = 3; i > 0; --i) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << " " << i << "...";
        cout.flush();
    }
    cout << endl << endl;

    int option = optionsMenu();
    handleMenuOption(option, g);
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
