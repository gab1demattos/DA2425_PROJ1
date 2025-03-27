#ifndef OUTPUT_H
#define OUTPUT_H
#include <vector>

#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"

bool OutputBestRoute(Graph<int> *graph, int source, int destination,
                     const std::pair<std::vector<int>, int> &solBestRoute,
                     const std::pair<std::vector<int>, int> &solALternativeRoute);

bool OutputBestEnvironmentallyFriendlyRoute(int source, int destination,
                                            const std::pair<std::vector<int>, int> &solBestDrivingRoute,
                                            const std::pair<std::vector<int>, int> &solBestWalkingRoute,
                                            const int &parkingNode, const int &totalTime, int maxWalkTime,
                                            const vector<ApproximateSolution<int> > &approximateSolutions);

template<class T>
bool OutputRestrictedRoute(int source, int destination, std::vector<T> bestRestrictedRoute, int totalTime);


#endif
//OUTPUT_H
