#ifndef INPUT_H
#define INPUT_H

/**
* @file Input.h
 * @brief Input handling functions for route planning system
 */

#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include "../DataStructures/Graph.h"

using namespace std;

/**
 * @brief Reads input for basic route planning (driving mode only)
 * @param file
 * @param[out] mode Transportation mode (will be checked if it is "driving")
 * @param[out] source Source node ID
 * @param[out] destination Destination node ID
 * @return true if input was read successfully
 * @return false if file couldn't be opened or input was invalid
 *
 * @note Expects input file in format:
 * Mode:driving
 * Source:<int>
 * Destination:<int>
 */
bool InputBestRoute(const string &file, string &mode, int &source, int &destination);

/**
 * @brief Reads input for environmentally friendly route planning
 * @param file
 * @param[out] mode Transportation mode (checked if it is "driving-walking")
 * @param[out] source Source node ID
 * @param[out] destination Destination node ID
 * @param[out] maxWalkTime Maximum allowed walking time
 * @param[out] avoidNodes Vector of nodes to avoid
 * @param[out] avoidSegments Vector of segments to avoid
 * @return true if input was read successfully
 * @return false if file couldn't be opened or input was invalid
 *
 * @note Expects input file in format:
 * Mode:driving-walking
 * Source:<int>
 * Destination:<int>
 * MaxWalkTime:<int>
 * AvoidNodes:<int>,<int>,...
 * AvoidSegments:(int,int),(int,int),...
 */
bool InputEnvironmentalRoute(const string &file, string &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes,
                             vector<pair<int, int> > &avoidSegments);

/**
 * @brief Reads input for restricted route planning with included nodes
 * @param file
 * @param[out] mode Transportation mode (set to "driving")
 * @param[out] source Source node ID
 * @param[out] destination Destination node ID
 * @param[out] avoidNodes Vector of nodes to avoid
 * @param[out] avoidSegments Vector of segments to avoid
 * @param[out] includeNode Node that must be included in route
 * @return true if input was read successfully
 * @return false if file couldn't be opened or input was invalid
 *
 * @note Expects input file in format:
 * Mode:driving
 * Source:<int>
 * Destination:<int>
 * AvoidNodes:<int>,<int>,...
 * AvoidSegments:(int,int),(int,int),...
 * IncludeNode:<int>
 */
bool InputRestrictedRoute(const string &file, string &mode, int &source, int &destination, vector<int> &avoidNodes,
                          vector<pair<int, int> > &avoidSegments, int &includeNode);
#endif //INPUT_H
