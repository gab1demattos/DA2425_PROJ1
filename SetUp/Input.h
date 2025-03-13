#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#include "Graph.h"

using namespace std;

vector<string> readInputFile(const string& filename);

template <class T>
Vertex<T>* readLocationFromFile(const string& line);

template <class T>
Edge<T>* readDistancesFromFile(const string& line, Graph<T>* graph);


#endif //INPUT_H
