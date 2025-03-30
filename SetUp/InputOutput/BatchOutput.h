#ifndef BATCHOUTPUT_H
#define BATCHOUTPUT_H

#include <vector>
#include "../DataStructures/Graph.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"

inline void BatchOutputBestRoute(int source, int destination, const pair<vector<int>, int> &solBestRoute,
                                 const pair<vector<int>, int> &solAlternativeRoute, const string& outfile){
    ofstream outFile(outfile);
    stringstream ss;

    vector<int> bestRoute = solBestRoute.first;
    int totalCost = solBestRoute.second;

    vector<int> alternativeRoute = solAlternativeRoute.first;
    int alternativeTime = solAlternativeRoute.second;

    // write the source and destination
    ss << "Source:" << source << endl;
    ss << "Destination:" << destination << endl;

    // write the best driving route
    ss << "BestDrivingRoute:";
    for (size_t i = 0; i < bestRoute.size(); ++i) {
        ss << bestRoute[i];
        if (i < bestRoute.size() - 1) {
            ss << ",";
        }
    }
    ss << "(" << totalCost << ")" << endl;

    if (alternativeRoute.empty()) {
        ss << "AlternativeRoute:None" << endl;
    } else {
        ss << "AlternativeRoute:";
        for (size_t i = 0; i < alternativeRoute.size(); ++i) {
            ss << alternativeRoute[i];
            if (i < alternativeRoute.size() - 1) {
                ss << ",";
            }
        }
        ss << "(" << alternativeTime << ")" << endl;
    }
    outFile << ss.str();
}

template<class T>
bool BatchOutputRestrictedRoute(int source, int destination, vector<T> bestRestrictedRoute, int totalTime,
                           const vector<T> &avoidNodes,
                           const vector<pair<T, T> > &avoidSegments, const string& outfile);


bool BatchOutputEnvironmentallyFriendlyRoute(int source, int destination,
                                            const std::pair<std::vector<int>, int> &solBestDrivingRoute,
                                            const std::pair<std::vector<int>, int> &solBestWalkingRoute,
                                            const int &parkingNode, const int &totalTime, int maxWalkTime,
                                            const vector<ApproximateSolution<int> > &approximateSolutions, const string& outfile);





#endif //BATCHOUTPUT_H
