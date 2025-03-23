#ifndef INPUT_H
#define INPUT_H


#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#include "Graph.h"

using namespace std;

bool InputBestRoute(string & mode, int & source, int & destination);

bool InputEnvironmentalRoute(string & mode, int & source, int & destination, int & maxWalkTime, vector<int> & avoidNodes, vector<pair<int, int> > & avoidSegments);

#endif //INPUT_H
