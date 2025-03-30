#include "InteractiveInput.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <climits>
using namespace std;

bool checkSourceDest(int &source, int &destination, string line) {
    cout << "Enter Source: ";
    getline(cin, line);
    regex intRegex("^\\d+$");
    if (!regex_match(line, intRegex)) {
        return false; // Invalid input
    }
    source = stoi(line);

    cout << "Enter Destination: ";
    getline(cin, line);
    if (!regex_match(line, intRegex)) {
        return false; // Invalid input
    }
    destination = stoi(line);
    return true;
}

bool parseNodes(vector<int> &avoidNodes, string line) {
    cout << "Enter Avoid Nodes (separated by spaces): ";
    getline(cin, line);

    // check if it's in the right format
    if (!line.empty()) {
        regex nodesRegex("^\\d+( \\d+)*$");
        if (!regex_match(line, nodesRegex)) {
            return false;
        }

        istringstream iss(line);
        int node;
        while (iss >> node) {
            avoidNodes.push_back(node);
        }
    }
    return true;
}

bool parseSegments(vector<pair<int, int> > &avoidSegments, string line) {
    cout << "Enter Avoid Segments (comma inside pairs, space between pairs): ";
    getline(cin, line);

    if (!line.empty()) {
        regex segmentsRegex("^\\d+,\\d+( \\d+,\\d+)*$");
        if (!regex_match(line, segmentsRegex)) {
            return false;
        }

        istringstream issSegments(line);
        string segment;
        while (issSegments >> segment) {
            replace(segment.begin(), segment.end(), ',', ' ');
            istringstream segmentStream(segment);
            int first, second;
            segmentStream >> first >> second;
            avoidSegments.push_back(make_pair(first, second));
        }
    }
    return true;
}

bool InterInputBestRoute(string &mode, int &source, int &destination) {
    cout << "Enter Mode: ";
    cin >> mode;
    if (mode != "driving" && mode != "Driving") {
        return false;
    }

    string line;
    cin.ignore();
    if (!checkSourceDest(source, destination, line)) {
        return false;
    }
    cout << endl;
    return true;
}

bool InterInputRestrictedRoute(string &mode, int &source, int &destination, vector<int> &avoidNodes,
                               vector<pair<int, int> > &avoidSegments, int &includeNode) {
    cout << "Enter Mode: ";
    cin >> mode;
    if (mode != "driving" && mode != "Driving") {
        return false;
    }

    string line;
    cin.ignore();

    if (!checkSourceDest(source, destination, line)) {
        return false;
    }

    if (!parseNodes(avoidNodes, line)) {
        return false;
    }

    if (!parseSegments(avoidSegments, line)) {
        return false;
    }

    cout << "Enter Include Node: ";

    getline(cin, line);
    if (line.empty()) {
        includeNode = INT_MAX;
    } else {
        includeNode = stoi(line);
    }
    return true;
}

bool InterInputEnvironmetalRoute(string &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes,
                                 vector<pair<int, int> > &avoidSegments) {
    cout << "Enter Mode: ";
    cin >> mode;
    if (mode != "driving-walking" && mode != "Driving-walking") {
        return false;
    }

    string line;
    cin.ignore();

    if (!checkSourceDest(source, destination, line)) {
        return false;
    }

    cout << "Enter Max Walk Time: ";
    getline(cin, line);

    regex intRegex("^\\d+$");
    if (!regex_match(line, intRegex)) {
        return false;
    }
    maxWalkTime = stoi(line);

    if (!parseNodes(avoidNodes, line)) {
        return false;
    }

    if (!parseSegments(avoidSegments, line)) {
        return false;
    }
    return true;
}
