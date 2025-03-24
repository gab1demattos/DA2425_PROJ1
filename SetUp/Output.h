#ifndef OUTPUT_H
#define OUTPUT_H
#include <vector>

void OutputBestRoute(int source, int destination, const std::pair<std::vector<int>,int>& solBestRoute, const std::pair<std::vector<int>,int>& solALternativeRoute);

void OutputBestEnvironmentallyFriendlyRoute(int source, int destination, const std::pair<std::vector<int>,int>& solBestDrivingRoute, const std::pair<std::vector<int>,int>& solBestWalkingRoute, const int &parkingNode, const int &totalTime);

template <class T>
void OutputRestrictedRoute(int source, int destination, std::vector<T> bestRestrictedRoute, int totalTime);



#endif
//OUTPUT_H
