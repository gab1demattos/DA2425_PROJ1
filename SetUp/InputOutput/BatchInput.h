#ifndef BATCHINPUT_H
#define BATCHINPUT_H
#include <string>
#include <fstream>
#include "../DataStructures/Graph.h"
#include <iostream>
#include <sstream>
#include "Input.h"
#include <vector>

#include "BatchOutput.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"
#include "../Routes/RestrictedRoutePlanning.h"
#include "../Routes/IndependentRoutePlanning.h"

std::string fileToSingleLine(const std::string& filename);

template <class T>
void runBatchMode(const std::string& infile, const std::string& outfile, Graph<T> *g);

#endif //BATCHINPUT_H
