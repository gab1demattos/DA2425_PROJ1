/**
* @file InteractiveInput.h
 * @brief Interactive menu input handling functions
 */

#ifndef INTERACTIVEINPUT_H
#define INTERACTIVEINPUT_H

#include <string>
#include <vector>
#include <utility>
#include "../DataStructures/Graph.h"


/**
 * @brief Handles interactive input for the best route
 * @param[out] mode Mode of transportation
 * @param[out] source Source node ID
 * @param[out] destination Destination node ID
 * @return True if the input is valid, false otherwise.
 */
bool InterInputBestRoute(string &mode, int &source, int &destination, Graph<int> *g);

/**
 * @brief Handles interactive input for the restricted route
 * @param[out] mode Mode of transportation
 * @param[out] source Source node ID
 * @param[out] destination Destination node ID
 * @param[out] avoidNodes Vector of nodes to avoid
 * @param[out] avoidSegments Vector of segments to avoid (node pairs)
 * @param[out] includeNode Node that must be included in route (INT_MAX if not required)
 * @return True if the input is valid, false otherwise.
 */
bool InterInputRestrictedRoute(string &mode, int &source, int &destination, vector<int> &avoidNodes,
                          vector<pair<int, int> > &avoidSegments, int &includeNode, Graph<int> *g);

/**
 * @brief Handles interactive input for the environmentally-friendly route
 * @param[out] mode Mode of transportation
 * @param[out] source Source node ID
 * @param[out] destination Destination node ID
 * @param[out] maxWalkTime The maximum walking time.
 * @param[out] avoidNodes Vector of nodes to avoid
 * @param[out] avoidSegments Vector of segments to avoid (node pairs)
 * @return True if the input is valid, false otherwise.
 */
bool InterInputEnvironmetalRoute(string &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes,
                             vector<pair<int, int> > &avoidSegments, Graph<int> *g);


#endif // INTERACTIVEINPUT_H
