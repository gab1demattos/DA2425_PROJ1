/**
* @file BatchInput.h
 * @brief Batch mode input handling functions
 */

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

/**
 * @brief Converts the contents of a file to a single line string
 * @param filename The name of the file to be read
 * @return A single line string containing the contents of the file
 * @throws std::runtime_error if the file cannot be opened
 */
std::string fileToSingleLine(const std::string& filename);

/**
 * @brief Runs the batch mode for route planning
 * @tparam T Node ID type (typically int)
 * @param infile The input file containing the route planning parameters
 * @param outfile The output file to write the results
 * @param g Pointer to the graph object
 * @details Reads input file, processes requested route, and writes results to output file
 */
template <class T>
void runBatchMode(const std::string& infile, const std::string& outfile, Graph<T> *g);

#endif //BATCHINPUT_H
