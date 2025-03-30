#ifndef RESTRICTEDROUTEPLANNING_H
#define RESTRICTEDROUTEPLANNING_H

/**
* @file RestrictedRoutePlanning.h
 * @brief Route planning with node/segment restrictions and required nodes
 */

#include "../DataStructures/Graph.h"

/**
 * @brief Core Dijkstra execution with restrictions (avoidNodes and avoidSegments)
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param start Starting vertex
 * @param avoidNodes List of nodes to avoid
 * @param avoidSegments List of segments (node pairs) to avoid
 *
 * @details Runs Dijkstra's algorithm to find shortest paths while:
 * 1. Skipping nodes in avoidNodes list
 * 2. Skipping segments in avoidSegments list
 * 3. Using driving times as edge weights
 * 4. Skipping walking-only routes (where driving time is INT_MAX)
 * 5. Maintaining a priority queue for efficient vertex selection
 * 6. Relaxing edges to update shortest path distances
 */
template<class T>
void runDijkstra(Graph<T> *g, Vertex<T> *start, const vector<T> &avoidNodes, const vector<pair<T, T> > &avoidSegments);


/**
 * @brief Finds restricted route that must include specific node (if requested)
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param origin Source node ID
 * @param dest Destination node ID
 * @param avoidNodes List of nodes to avoid
 * @param avoidSegments List of segments to avoid
 * @param includeNode Node that must be included in route (INT_MAX if not required)
 * @param[out] route Resulting path as vector of node IDs (empty if no valid route found)
 * @param[out] totalTime Total driving time in seconds (0 if no valid route)
 * @param[out] flag Success indicator (true if valid route found, false otherwise)
 *
 * @details Finds shortest driving route from origin to destination while:
 * 1. Avoiding specified nodes and segments
 * 2. Including required node (if specified) by finding optimal path:
 *    origin → includeNode → destination
 * 3. Using Dijkstra's algorithm with driving times as edge weights
 * 4. Skipping walking-only routes
 * 
 * Handles edge cases:
 * - Invalid/unreachable origin or destination nodes
 * - Unreachable required node
 * - No valid path exists meeting all constraints
 * - Required node same as origin/destination
 */
template<class T>
void RestrictedRoutePlanning(Graph<T> *g, const int &origin, const int &dest, const vector<T> &avoidNodes,
                             const vector<pair<T, T> > &avoidSegments, const T &includeNode, vector<T> &route,
                             int &totalTime, bool &flag);

#endif //RESTRICTEDROUTEPLANNING_H
