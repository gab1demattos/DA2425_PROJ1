#ifndef READCSV_H
#define READCSV_H

#include <string>
#include "Graph.h"

void readLocations(const std::string& filename, Graph<int>& graph);

void readDistances(const std::string& filename, Graph<int>& graph);

#endif //READCSV_H
