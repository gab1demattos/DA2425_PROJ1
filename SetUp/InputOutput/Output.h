/**
* @file Output.h
 * @brief Output handling functions for route planning system results
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"


/**
 * @brief Outputs the best route solution with alternative option
 * @param graph Pointer to the graph object
 * @param source Source node ID
 * @param destination Destination node ID
 * @param solBestRoute Best route solution (path and total time)
 * @param solAlternativeRoute Alternative route solution (path and time)
 * @return true if user wants to return to menu, false to exit
 *
 * @note Output format:
 * Source:<id>
 * Destination:<id>
 * BestDrivingRoute:<path>(<time>)
 * AlternativeRoute:<path>(<time>) or "None"
 */
bool OutputBestRoute(Graph<int> *graph, int source, int destination, const std::pair<std::vector<int>, int> &solBestRoute,
                     const std::pair<std::vector<int>, int> &solAlternativeRoute);

/**
 * @brief Outputs the best environmentally friendly route solution
 * @param graph Pointer to the graph object
 * @param source Source node ID
 * @param destination Destination node ID
 * @param solBestDrivingRoute Best driving route (path and time)
 * @param solBestWalkingRoute Best walking route (path and time)
 * @param parkingNode ID of parking node used
 * @param totalTime Total combined time
 * @param maxWalkTime Maximum walking time specified
 * @param approximateSolutions Vector of approximate solutions (used if no exact solution)
 * @return true if user wants to return to menu, false to exit
 *
 * @note Output format:
 * Source:<id>
 * Destination:<id>
 * DrivingRoute:<path>(<time>) or "None"
 * ParkingNode:<id> or "None"
 * WalkingRoute:<path>(<time>) or "None"
 * TotalTime:<time> or ""
 * Message: <error message> (if no solution)
 */
bool OutputBestEnvironmentallyFriendlyRoute(Graph<int> *graph, int source, int destination,
                                            const std::pair<std::vector<int>, int> &solBestDrivingRoute,
                                            const std::pair<std::vector<int>, int> &solBestWalkingRoute,
                                            const int &parkingNode, const int &totalTime, int maxWalkTime,
                                            const vector<ApproximateSolution<int> > &approximateSolutions);

/**
 * @brief Outputs a restricted route solution
 * @tparam T Node ID type (typically int)
 * @param graph Pointer to the graph object
 * @param source Source node ID
 * @param destination Destination node ID
 * @param bestRestrictedRoute Vector of nodes in the restricted route
 * @param totalTime Total time of the restricted route
 * @param avoidNodes Vector of nodes to avoid
 * @param avoidSegments Vector of segments to avoid
 * @return true if user wants to return to menu, false to exit
 *
 * @note Output format:
 * Source:<id>
 * Destination:<id>
 * RestrictedDrivingRoute:<path>(<time>)
 */
template<class T>
bool OutputRestrictedRoute(Graph<T> *graph, int source, int destination, vector<T> bestRestrictedRoute, int totalTime,
                           const vector<T> &avoidNodes,
                           const vector<pair<T, T> > &avoidSegments);

/**
 * @brief Outputs approximate solutions when no exact route is found
 * @param graph Pointer to graph object
 * @param source Source node ID
 * @param destination Destination node ID
 * @param maxWalkTime Maximum walking time specified by user
 * @param solutions Vector of approximate solutions
 * @return true if user wants to return to menu, false to exit
 *
 * @note Output format for each solution:
 * DrivingRoute<X>:<path>(<time>)
 * ParkingNode<X>:<id>
 * WalkingRoute<X>:<path>(<time>)
 * TotalTime<X>:<time>
 */
bool OutputApproximateSolutions(Graph<int> *graph, int source, int destination,
                                int maxWalkTime,
                                const vector<ApproximateSolution<int> > &solutions);

#endif
//OUTPUT_H
