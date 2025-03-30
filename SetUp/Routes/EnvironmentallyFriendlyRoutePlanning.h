/**
* @file EnvironmentallyFriendlyRoutePlanning.h
 * @brief Environmentally friendly route planning with driving and walking segments
 */

#ifndef ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H
#define ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H

#include "../DataStructures/Graph.h"

/**
 * @struct ApproximateSolution
 * @brief Stores alternative route information
 * @var drivingRoute Path of driving segment
 * @var drivingTime Driving time in minutes
 * @var parkingNode Parking node ID
 * @var walkingRoute Path of walking segment
 * @var walkingTime Walking time in minutes
 * @var totalTime Combined total time
 */
template<class T>
struct ApproximateSolution {
    vector<T> drivingRoute;
    int drivingTime;
    T parkingNode;
    vector<T> walkingRoute;
    int walkingTime;
    int totalTime;
};

/**
 * @brief Finds approximate solutions when no exact route meets requirements
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param approxWalkingpaths Precomputed walking paths from parking nodes to destination without the walking time limit
 * @param avoidNodes List of nodes to avoid
 * @param avoidSegments List of segments (node pairs) to avoid
 * @param destination Target node ID
 * @param destination Source node ID
 * @param[out] approximateSolutions Vector to store found solutions
 *
 * @details Finds top 2 alternative routes sorted by:
 * 1. Total time (ascending)
 * 2. Walking time (ascending)
 */
template<class T>
void FindApproximateSolutions(Graph<T> *g, const vector<pair<vector<T>, int> > &approxWalkingpaths,
                              const vector<T> &avoidNodes, const vector<pair<T, T> > &avoidSegments,
                              int destination, int origin, vector<ApproximateSolution<T> > &approximateSolutions);

/**
 * @brief Finds the best environmentally friendly route (driving + walking)
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param origin Starting node ID
 * @param dest Destination node ID
 * @param maxWalkTime Maximum allowed walking time in minutes
 * @param avoidNodes Vector of nodes to avoid
 * @param avoidSegments Vector of segments (node pairs) to avoid
 * @param[out] drivingRoute Resulting driving route (path and time)
 * @param[out] parkingNode Parking node ID used
 * @param[out] walkingRoute Resulting walking route (path and time)
 * @param[out] totalTime Total route time
 * @param[out] approximateSolutions Alternative solutions if no exact route found
 *
 * @details Finds route with:
 * 1. Driving segment to parking node
 * 2. Walking segment to destination
 * Returns -1 if origin/dest are adjacent, -2 if no parking, -3 if no valid route
 */
template<class T>
void EnvironmentallyFriendlyBestRoute(Graph<T> *g, const int &origin, const int &dest,
                                      const int &maxWalkTime, const vector<T> &avoidNodes,
                                      const vector<pair<T, T> > &avoidSegments,
                                      pair<vector<T>, int> &drivingRoute, T &parkingNode,
                                      pair<vector<T>, int> &walkingRoute, int &totalTime,
                                      vector<ApproximateSolution<T> > &approximateSolutions);

/**
 * @brief Modified Dijkstra's algorithm with node and segment restrictions
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param origin Starting node ID
 * @param avoidNodes Vector of nodes to avoid
 * @param avoidSegments Vector of segments (node pairs) to avoid
 *
 * @details Finds shortest paths while avoiding specified nodes and segments.
 * Uses driving times for edge weights.
 */
template<class T>
void restrictedDijkstra(Graph<T> *g, const T &origin, const vector<T> &avoidNodes,
                        const vector<pair<T, T> > &avoidSegments);

/**
 * @brief Dijkstra's algorithm for walking paths with restrictions
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 * @param origin Starting node ID
 * @param avoidNodes Vector of nodes to avoid
 * @param avoidSegments Vector of segments (node pairs) to avoid
 *
 * @details Finds shortest walking paths while avoiding specified nodes/segments
 */
template<class T>
void restrictedDijkstraWalking(Graph<T> *g, const T &origin, const vector<T> &avoidNodes,
                               const vector<pair<T, T> > &avoidSegments);

#endif //ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H
