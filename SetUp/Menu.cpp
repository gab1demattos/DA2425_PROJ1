#include "Menu.h"

#include <sstream>


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

    cout << "Mode: ";
    cin >> mode;
    if (!isModeDriving(mode))
        cout << "Invalid input." << endl;

    cout << "Source : ";
    cin >> source;

    cout << "Destination : ";
    cin >> destination;

    bestRoute(g->findVertex(source), g->findVertex(destination));
}

void optionRestrictedRoute() {
    string mode;
    int source, destination, includeNode;
    vector<int> avoidNodes;
    //vector<pair<int, int>> avoidSegments;

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

}

void optionEnvironmentalRoute() {
    string mode;
    int source, destination, maxWalkTime;
    vector<int> avoidNodes;
    //vector<pair<int, int>> avoidSegments;

    cout << "Mode: ";
    cin >> mode;
    if (!isModeDriving(mode))
        cout << "Invalid input." << endl;

    cout << "Source : ";
    cin >> source;

    cout << "Destination : ";
    cin >> destination;

    cout << "IncludeNode : ";
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
}


// ???
bool isModeDriving(const string& mode) {
    string res;
    for (const char c : mode)
        res += static_cast<char>(tolower(c));
    return res == "driving";
}
