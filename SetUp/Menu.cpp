#include "Menu.h"
#include "IndependentRoutePlanning.h"

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

    InputBestRoute(mode, source, destination);

    pair<vector<T>,int> solBestRoute = BestRoute(g,source, destination);

    pair<vector<T>,int> solAlternativeRoute = AlternativeRoute(g, solBestRoute, source, destination);

    OutputBestRoute(source, destination, solBestRoute, solAlternativeRoute);
}

// Explicit instantiation for the required type (e.g., int)
template void optionBestRoute<int>(Graph<int> *g);

template<class T>
void optionRestrictedRoute(Graph<T> *g) {
    /*string mode;
    int source, destination, includeNode;
    vector<int> avoidNodes;
    vector<pair<int, int>> avoidSegments;

    cout << "Mode: ";
    cin >> mode;
    if (!isModeDriving(mode))
        cout << "Invalid input." << endl;

    cout << "Source : ";
    cin >> source;

    cout << "Destination : ";
    cin >> destination;

    cout << "Enter nodes separated by spaces, then press ENTER. Enter -1 to skip" << endl;
    cout << "AvoidNodes: ";
    string input;
    cin.ignore();
    getline(cin, input);
    stringstream ss(input);
    int node;
    while (ss >> node) {
        if (node == -1) break;
        avoidNodes.push_back(node);
    }

    cout << "AvoidSegments: ";
    // to do

    cout << "IncludeNode : ";
    cin >> includeNode;

    restrictedRoute(g->findVertex(source), g->findVertex(destination), avoidNodes, avoidSegments, g->findVertex(includeNode));
*/
}

template<class T>
void optionEnvironmentalRoute(Graph<T> *g) {
    /*string mode;
    int source, destination, maxWalkTime;
    vector<int> avoidNodes;
    vector<pair<int, int>> avoidSegments;

    cout << "Mode: ";
    cin >> mode;

    cout << "Source : ";
    cin >> source;

    cout << "Destination : ";
    cin >> destination;

    cout << "MaxWalkTime : ";
    cin >> maxWalkTime;

    cout << "AvoidNodes: " << endl;
    string input;
    cin.ignore();
    getline(cin, input);
    stringstream ss(input);
    int node;
    while (ss >> node) {
        if (node == -1) break;
        avoidNodes.push_back(node);
    }

    cout << "AvoidSegments: " << endl;
    // to do

    environmentalRoute(g->findVertex(source), g->findVertex(destination), maxWalkTime, avoidNodes, avoidSegments);
    */
}
