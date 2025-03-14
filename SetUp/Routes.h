

#ifndef ROUTES_H
#define ROUTES_H
#include "Graph.h"

template<class T>
void bestRoute(Vertex<T> *src, Vertex<T> *dest);

template<class T>
void restrictedRoute(Vertex<T> *src, Vertex<T> *dest, vector<int> &avoidNodes, vector<pair<int, int>> &avoidSegments, Vertex<T> *includeNode);


template<class T>
void environmentalRoute(Vertex<T> *src, Vertex<T> *dest, vector<int> &avoidNodes, vector<pair<int, int>> &avoidSegments, Vertex<T> *includeNode);

#endif //ROUTES_H
