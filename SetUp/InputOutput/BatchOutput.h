#ifndef BATCHOUTPUT_H
#define BATCHOUTPUT_H

#include <vector>
#include "../DataStructures/Graph.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"

void BatchOutputBestRoute(int source, int destination, const pair<vector<int>, int> &solBestRoute,
                                 const pair<vector<int>, int> &solAlternativeRoute, const string& outfile);


template<class T>
void BatchOutputRestrictedRoute(int source, int destination, vector<T> bestRestrictedRoute,
                                int totalTime, bool flag, const string& outfile);


void BatchOutputEnvironmentallyFriendlyRoute(int source, int destination,
                                                    const std::pair<std::vector<int>, int> &solBestDrivingRoute,
                                                    const std::pair<std::vector<int>, int> &solBestWalkingRoute,
                                                    const int &parkingNode, const int &totalTime, int maxWalkTime,
                                                    const vector<ApproximateSolution<int> > &approximateSolutions, const string& outfile);




#endif //BATCHOUTPUT_H
