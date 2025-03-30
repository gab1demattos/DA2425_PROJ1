#include "BatchOutput.h"
#include <vector>
#include <sstream>
#include <fstream>
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"
using namespace std;

void BatchOutputBestRoute(int source, int destination, const pair<vector<int>, int> &solBestRoute,
                          const pair<vector<int>, int> &solAlternativeRoute, const string &outfile) {
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
void BatchOutputRestrictedRoute(int source, int destination, vector<T> bestRestrictedRoute,
                                int totalTime, bool flag, const string &outfile) {
    ofstream outFile(outfile);
    stringstream ss;

    ss << "Source:" << source << endl;
    ss << "Destination:" << destination << endl;
    ss << "RestrictedDrivingRoute:";
    if (flag == false) {
        ss << "none" << endl;
    } else {
        for (size_t i = 0; i < bestRestrictedRoute.size(); ++i) {
            ss << bestRestrictedRoute[i];
            if (i < bestRestrictedRoute.size() - 1) {
                ss << ",";
            }
        }

        ss << "(" << totalTime << ")" << endl;
    }

    outFile << ss.str();
}

// Explicit template instantiation
template void BatchOutputRestrictedRoute<int>(int source, int destination, std::vector<int> bestRestrictedRoute,
                                              int totalTime, bool flag, const std::string &outfile);

void BatchOutputEnvironmentallyFriendlyRoute(int source, int destination,
                                             const std::pair<std::vector<int>, int> &solBestDrivingRoute,
                                             const std::pair<std::vector<int>, int> &solBestWalkingRoute,
                                             const int &parkingNode, const int &totalTime, int maxWalkTime,
                                             const vector<ApproximateSolution<int> > &approximateSolutions,
                                             const string &outfile) {
    ofstream outFile(outfile);
    stringstream ss;

    vector<int> bestDrivingRoute = solBestDrivingRoute.first;
    int drivingTime = solBestDrivingRoute.second;

    vector<int> bestWalkingRoute = solBestWalkingRoute.first;
    int walkingTime = solBestWalkingRoute.second;

    // Output the source and destination
    ss << "Source:" << source << endl;
    ss << "Destination:" << destination << endl;


    ss << "DrivingRoute:";
    if (bestDrivingRoute.empty()) {
        ss << "None" << endl;
    } else {
        for (size_t i = 0; i < bestDrivingRoute.size(); ++i) {
            ss << bestDrivingRoute[i];
            if (i < bestDrivingRoute.size() - 1) {
                ss << ",";
            }
        }
        ss << "(" << drivingTime << ")" << endl;
    }

    ss << "ParkingNode:";
    if (parkingNode == -1) {
        ss << "None" << endl;
    } else {
        ss << parkingNode << endl;
    }


    ss << "WalkingRoute:";
    if (bestWalkingRoute.empty()) {
        ss << "None" << endl;
    } else {
        for (size_t i = 0; i < bestWalkingRoute.size(); ++i) {
            ss << bestWalkingRoute[i];
            if (i < bestWalkingRoute.size() - 1) {
                ss << ",";
            }
        }
        ss << "(" << walkingTime << ")" << endl;
    }

    ss << "TotalTime:";

    if (totalTime < 0) {
        ss << "" << endl;
        ss << "Message: ";
        if (totalTime == -1) {
            ss << "There are no possible routes because nodes are adj" << endl;
        } else if (totalTime == -2) {
            ss << "There are no parking spots available" << endl;
        } else if (totalTime == -3) {
            ss << "There are no possible routes with max. walking time given" << endl;
        }

        if (!approximateSolutions.empty()) {
            ss << endl << "Approximate Solutions:" << endl;
            ss << "Source:" << source << endl;
            ss << "Destination:" << destination << endl;

            for (size_t i = 0; i < approximateSolutions.size(); ++i) {
                const auto &sol = approximateSolutions[i];
                ss << "DrivingRoute" << i + 1 << ":";
                for (size_t j = 0; j < sol.drivingRoute.size(); ++j) {
                    ss << sol.drivingRoute[j];
                    if (j < sol.drivingRoute.size() - 1) ss << ",";
                }
                ss << "(" << sol.drivingTime << ")" << endl;

                ss << "ParkingNode" << i + 1 << ":" << sol.parkingNode << endl;

                ss << "WalkingRoute" << i + 1 << ":";
                for (size_t j = 0; j < sol.walkingRoute.size(); ++j) {
                    ss << sol.walkingRoute[j];
                    if (j < sol.walkingRoute.size() - 1) ss << ",";
                }
                ss << "(" << sol.walkingTime << ")";
                ss << endl;

                ss << "TotalTime" << i + 1 << ":" << sol.totalTime << endl;
            }
        }
    } else {
        ss << totalTime << endl;
    }
    outFile << ss.str();
}








