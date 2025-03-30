#ifndef BATCHINPUT_H
#define BATCHINPUT_H
#include <string>
#include <fstream>
#include "DataStructures/Graph.h"

template <class T>
void checkRouteType(std::string line, const string& file, Graph<T> *g);

template <class T>
void fileToSingleLine(const std::string& filename, Graph<T> *g);


#endif //BATCHINPUT_H
