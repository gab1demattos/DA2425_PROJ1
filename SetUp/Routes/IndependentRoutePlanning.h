#ifndef INDEPENDENTROUTEPLANNING_H
#define INDEPENDENTROUTEPLANNING_H

#include "../DataStructures/Graph.h"

template <class T>
void dijkstra(Graph<T> * g, const int &origin);

template <class T>
pair<vector<T>,int> BestRoute(Graph<T> * g, const int &origin, const int &dest);

template <class T>
pair<vector<int>,int> AlternativeRoute(Graph<T>* g, const pair<vector<int>,int>& primaryRoute, int source, int destination);

#endif //INDEPENDENTROUTEPLANNING_H