#ifndef ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H
#define ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H

#include "Graph.h"\

template <class T>
void restrictedDijkstra(Graph<T> * g, const int &origin);

template <class T>
pair<vector<T>,int> EnvironmentallyFriendlyBestRoute(Graph<T> * g, const int &origin, const int &dest);

#endif //ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H
