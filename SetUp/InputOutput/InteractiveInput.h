#ifndef INTERACTIVEINPUT_H
#define INTERACTIVEINPUT_H

#include <string>
#include <vector>
#include <utility>
#include "../DataStructures/Graph.h"

bool checkSourceDest(int &source, int &destination, std::string line, Graph<int> *g);

bool parseNodes(std::vector<int> &avoidNodes, std::string line, Graph<int> *g);

bool parseSegments(std::vector<std::pair<int, int> > &avoidSegments, std::string line, Graph<int> *g);

bool InterInputBestRoute(std::string &mode, int &source, int &destination, Graph<int> *g);

bool InterInputRestrictedRoute(std::string &mode, int &source, int &destination, std::vector<int> &avoidNodes,
                               std::vector<std::pair<int, int> > &avoidSegments, int &includeNode, Graph<int> *g);

bool InterInputEnvironmetalRoute(std::string &mode, int &source, int &destination, int &maxWalkTime,
                                 std::vector<int> &avoidNodes,
                                 std::vector<std::pair<int, int> > &avoidSegments, Graph<int> *g);

#endif // INTERACTIVEINPUT_H
