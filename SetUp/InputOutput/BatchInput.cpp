#include "BatchInput.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Input.h"
#include <vector>
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"
#include "../Routes/RestrictedRoutePlanning.h"
#include "../Routes/IndependentRoutePlanning.h"
using namespace std;

// Explicit template instantiation for int type
template void runBatchMode<int>(const string& infile, const string& outfile, Graph<int> *g);
/*
// function to combine all lines of a file into one line
string fileToSingleLine(const string& filename) {
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
    return oss.str();
}
*/
/*
template <class T>
void runBatchMode(const string& infile, const string& outfile, Graph<T> *g){
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

    string line = fileToSingleLine(infile);
    if (line.find("driving-walking") != string::npos){
        if (!InputEnvironmentalRoute(infile, mode, source, destination, maxWalkTime, avoidNodes, avoidSegments)) {
            return;
        }

        // Update the function call to include approximateSolutions
        EnvironmentallyFriendlyBestRoute(g, source, destination, maxWalkTime, avoidNodes, avoidSegments,
                                         drivingRoute, parkingNode, walkingRoute, totalTime,
                                         approximateSolutions);

    }
    else {
        if (line.find("AvoidNodes") != string::npos){

            if (!InputRestrictedRoute(infile, mode, source, destination, avoidNodes, avoidSegments, includeNode)) {
                return; // Stop if input is invalid
            }
            RestrictedRoutePlanning(g, source, destination, avoidNodes, avoidSegments, includeNode, route, totalTime);

        }
        else {

            if (!InputBestRoute(infile, mode, source, destination)){
              return;
            }
            pair<vector<T>, int> solBestRoute = BestRoute(g, source, destination);
    		pair<vector<T>, int> solAlternativeRoute = AlternativeRoute(g, solBestRoute, source, destination);


        }

    }
}
*/
