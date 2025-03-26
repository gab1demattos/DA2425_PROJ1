#ifndef INPUT_H
#define INPUT_H


#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#include "../DataStructures/Graph.h"

using namespace std;

bool InputBestRoute(string &mode, int &source, int &destination);

bool InputEnvironmentalRoute(string &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes,
                             vector<pair<int, int> > &avoidSegments);

bool InputRestrictedRoute(string &mode, int &source, int &destination, vector<int> &avoidNodes,
                          vector<pair<int, int> > &avoidSegments, int &includeNode);
#endif //INPUT_H
