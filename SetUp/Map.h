#ifndef MAP_H
#define MAP_H

#include "Input.h"
#include "Graph.h"
#include <vector>
#include <string>
#include <iostream>

template <class T>
vector<Edge<T>*> getDistancesInfo(const string& filename, Graph<T> *graph);

template <class T>
vector<Vertex<T>*> getLocationsInfo(const string& filename);

template <class T>
void createGraph(Graph<T> *graph);

#endif //MAP_H
