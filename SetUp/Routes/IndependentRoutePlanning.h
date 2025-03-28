#ifndef INDEPENDENTROUTEPLANNING_H
#define INDEPENDENTROUTEPLANNING_H

/**
* @file IndependentRoutePlanning.h
 * @brief Independent route planning functionality (best route and alternatives)
 */

#include "../DataStructures/Graph.h"

/**
 * @brief Standard Dijkstra's algorithm implementation
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param origin Starting node ID
 *
 * @details Computes shortest paths from origin to all other nodes
 * using driving times as edge weights.
 */
template<class T>
void dijkstra(Graph<T> *g, const int &origin);

/**
 * @brief Finds the best route between two nodes
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param origin Source node ID
 * @param dest Destination node ID
 * @return Pair containing:
 *   - vector of node IDs representing the path
 *   - total driving time (0 if no path exists)
 *
 * @note Returns empty vector if no path exists
 * @note Reconstructs path by following parent pointers from destination
 */
template<class T>
pair<vector<T>, int> BestRoute(Graph<T> *g, const int &origin, const int &dest);

/**
 * @brief Finds an alternative route different from the primary route
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param primaryRoute The primary route to avoid
 * @param source Source node ID
 * @param destination Destination node ID
 * @return Pair containing:
 *   - vector of node IDs representing alternative path
 *   - total driving time (empty if no valid alternative)
 *
 * @details Creates a modified graph by:
 * 1. Removing intermediate nodes of primary route
 * 2. Removing edges of primary route
 * 3. Finding best route on modified graph
 *
 * @note Returns empty vector if no valid alternative exists
 * @note Alternative must be longer than primary route
 */
template<class T>
pair<vector<int>, int> AlternativeRoute(Graph<T> *g, const pair<vector<int>, int> &primaryRoute, int source,
                                        int destination);

/**
 * @brief Relaxes an edge during Dijkstra's algorithm
 * @tparam T Node ID type (typically int)
 * @param edge Edge to relax
 * @return true if relaxation occurred (shorter path found), false otherwise
 *
 * @details Updates the destination vertex's distance if a shorter path is found
 * through this edge. Uses driving times for edge weights.
 */
template<class T>
bool relax(Edge<T> *edge);

#endif //INDEPENDENTROUTEPLANNING_H
