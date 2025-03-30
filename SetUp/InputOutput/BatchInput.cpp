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

std::string fileToSingleLine(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::ostringstream oss;
    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (!firstLine) {
            oss << " ";  // Add space between lines
        }
        oss << line;
        firstLine = false;
    }
    return oss.str();
}

template <class T>
void runBatchMode(const std::string& infile, const std::string& outfile, Graph<T> *g) {
    std::string mode;
    int source;
    int destination;
    std::vector<int> avoidNodes;
    std::vector<std::pair<int, int> > avoidSegments;
    int includeNode;
    int maxWalkTime;
    std::vector<T> route;
    int totalTime;
    std::pair<std::vector<int>, int> drivingRoute, walkingRoute;
    std::vector<ApproximateSolution<int> > approximateSolutions;
    T parkingNode;
    bool flag;

    std::string line = fileToSingleLine(infile);
    if (line.find("driving-walking") != std::string::npos) {
        if (!InputEnvironmentalRoute(infile, mode, source, destination, maxWalkTime, avoidNodes, avoidSegments)) {
            return;
        }

        EnvironmentallyFriendlyBestRoute(g, source, destination, maxWalkTime, avoidNodes, avoidSegments,
                                       drivingRoute, parkingNode, walkingRoute, totalTime,
                                       approximateSolutions);
        BatchOutputEnvironmentallyFriendlyRoute(source, destination, drivingRoute, walkingRoute, parkingNode, totalTime, maxWalkTime, approximateSolutions, outfile);
    }
    else {
        if (line.find("AvoidNodes") != std::string::npos) {
            if (!InputRestrictedRoute(infile, mode, source, destination, avoidNodes, avoidSegments, includeNode)) {
                return;
            }
            RestrictedRoutePlanning(g, source, destination, avoidNodes, avoidSegments, includeNode, route, totalTime, flag);
            BatchOutputRestrictedRoute(source, destination, route, totalTime, flag, outfile);
        }
        else {
            if (!InputBestRoute(infile, mode, source, destination)) {
                return;
            }
            std::pair<std::vector<T>, int> solBestRoute = BestRoute(g, source, destination);
            std::pair<std::vector<T>, int> solAlternativeRoute = AlternativeRoute(g, solBestRoute, source, destination);
            BatchOutputBestRoute(source, destination, solBestRoute, solAlternativeRoute, outfile);
        }
    }
}


// Explicit template instantiation for int type
template void runBatchMode<int>(const string& infile, const string& outfile, Graph<int> *g);

