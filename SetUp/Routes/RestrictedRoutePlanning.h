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
 * @details Runs Dijkstra's algorithm while:
 * 1. Skipping nodes in avoidNodes
 * 2. Skipping segments in avoidSegments
 * Uses driving times for edge weights.
 */
template<class T>
void runDijkstra(Graph<T> *g, Vertex<T> *start, const vector<T> &avoidNodes, const vector<pair<T, T> > &avoidSegments);

/**
 * @brief Restricted Dijkstra that ensures path includes specific node (if requested)
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param origin Starting node ID
 * @param avoidNodes List of nodes to avoid
 * @param avoidSegments List of segments to avoid
 * @param includeNode Node that must be included in path
 *
 * @details Performs two-phase search:
 * 1. First from origin to includeNode
 * 2. Then from includeNode to destination
 * Returns early if includeNode is unreachable.
 */
template<class T>
void restrictedDijkstra(Graph<T> *g, const int &origin, const vector<T> &avoidNodes,
                        const vector<pair<T, T> > &avoidSegments, const T &includeNode);

/**
 * @brief Finds restricted route that must include specific node (if requested)
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param origin Source node ID
 * @param dest Destination node ID
 * @param avoidNodes List of nodes to avoid
 * @param avoidSegments List of segments to avoid
 * @param includeNode Node that must be included in route
 * @param[out] route Resulting path (empty if none found)
 * @param[out] totalTime Total driving time (0 if no route)
 *
 * @details Combines two path segments:
 * 1. origin → includeNode
 * 2. includeNode → destination
 * Handles edge cases:
 * - Unreachable includeNode
 * - Unreachable destination
 * - Duplicate nodes at path junctions
 */
template<class T>
void RestrictedRoutePlanning(Graph<T> *g, const int &origin, const int &dest, const vector<T> &avoidNodes,
                             const vector<pair<T, T> > &avoidSegments, const T &includeNode, vector<T> &route,
                             int &totalTime);

#endif //RESTRICTEDROUTEPLANNING_H
