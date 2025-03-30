#include "BatchInput.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Input.h"
#include <vector>
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"
using namespace std;

template <class T>
void checkRouteType(string line, const string& file, Graph<T> *g){
    string mode;
    int source;
    int destination;
    vector<int> avoidNodes;
    vector<pair<int, int> > avoidSegments;
    int includeNode;
    int maxWalkTime;
    vector<T> route;
    int totalTime;
    pair<vector<int>, int> drivingRoute, walkingRoute;
    vector<ApproximateSolution<int> > approximateSolutions;
    T parkingNode;


    if (line.find("driving-walking") != string::npos){
        if (!InputEnvironmentalRoute(file, mode, source, destination, maxWalkTime, avoidNodes, avoidSegments)) {
            return;
        }

        // Update the function call to include approximateSolutions
        EnvironmentallyFriendlyBestRoute(g, source, destination, maxWalkTime, avoidNodes, avoidSegments,
                                         drivingRoute, parkingNode, walkingRoute, totalTime,
                                         approximateSolutions);

    }
    else {
        if (line.find("AvoidNodes") != string::npos){

            if (!InputRestrictedRoute(file, mode, source, destination, avoidNodes, avoidSegments, includeNode)) {
                return; // Stop if input is invalid
            }
            RestrictedRoutePlanning(g, source, destination, avoidNodes, avoidSegments, includeNode, route, totalTime);

        }
        else {

            if (!InputBestRoute(file, mode, source, destination)){
              return;
            }
            pair<vector<T>, int> solBestRoute = BestRoute(g, source, destination);
    		pair<vector<T>, int> solAlternativeRoute = AlternativeRoute(g, solBestRoute, source, destination);


        }

    }
}

// function to combine all lines of a file into one line
template <class T>
void fileToSingleLine(const string& filename, Graph<T> *g) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    ostringstream oss;
    string line;
    bool firstLine = true;

    while (getline(file, line)) {
        if (!firstLine) {
            oss << " ";  // Add space between lines
        }
        oss << line;
        firstLine = false;
    }
    file.close();
    checkRouteType(oss.str(), filename, g);
}

