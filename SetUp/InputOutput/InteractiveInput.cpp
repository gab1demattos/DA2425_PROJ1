#include "InteractiveInput.h"
#include <iostream>
#include <sstream>
#include <regex>
using namespace std;

bool InterInputBestRoute(string &mode, int &source, int &destination){
  cout << "Enter Mode: ";
  cin >> mode;
  if (mode != "driving" && mode != "Driving"){
    //cout << "Invalid mode! Please try again (only driving is accepted)." << endl;
    return false;
  }
  cout << "Enter Source: ";
  cin >> source;

  cout << "Enter Destination: ";
  cin >> destination;
  cout << endl;
  return true;
}

bool InterInputRestrictedRoute(string &mode, int &source, int &destination, vector<int> &avoidNodes,
                          vector<pair<int, int> > &avoidSegments, int &includeNode) {
    cout << "Enter Mode: ";
    cin >> mode;
    if (mode != "driving" && mode != "Driving"){
        //cout << "Invalid mode! Please try again (only driving is accepted)." << endl;
        return false;
    }
    cout << "Enter Source: ";
    cin >> source;

    cout << "Enter Destination: ";
    cin >> destination;

    cout << "Enter Avoid Nodes (separated by spaces): ";
    string line;
    cin.ignore(); // ignore the newline character left in the input buffer
    getline(cin, line);

    // check if it's in the right format
    if (!line.empty()) {
        // check if it's in the right format
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

    cout << "Enter Include Node: ";
    getline(cin, line);
    if (line.empty()) {
        includeNode = INT_MAX;
    } else {
        includeNode = stoi(line);
    }
    return true;
}