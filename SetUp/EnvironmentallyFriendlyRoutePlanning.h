#ifndef ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H
#define ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H

#include "Graph.h"\

template <class T>
void restrictedDijkstra(Graph<T> * g, const int &origin);

template <class T>
void EnvironmentallyFriendlyBestRoute(Graph<T> * g, const int &origin, const int &dest, const int &maxWalkTime, const vector<T> &avoidNodes, const vector<pair<T,T> > &avoidSegments, pair<vector<T>,T> &drivingRoute, T &parkingNode, pair<vector<T>,T> &walkingRoute, int &totalTime);

#endif //ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H
