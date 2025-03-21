#ifndef INDEPENDENTROUTEPLANNING_H
#define INDEPENDENTROUTEPLANNING_H

#include "Graph.h"

template <class T>
void dijkstra(Graph<T> * g, const int &origin);

template <class T>
pair<vector<T>,int> BestRoute(Graph<T> * g, const int &origin, const int &dest);


#endif //INDEPENDENTROUTEPLANNING_H
