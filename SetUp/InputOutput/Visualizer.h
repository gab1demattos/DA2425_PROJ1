/**
* @file Visualizer.h
 * @brief Header file for route visualizations
 */

#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <vector>
#include <string>
#include "../DataStructures/Graph.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"

/**
 * @brief Visualizes routes and comparisons in the console
 */
class Visualizer {
public:
    /**
     * @brief Visualizes a single route
     * @param graph Pointer to graph object
     * @param route Vector of node IDs representing the route
     * @param totalCost Total time of the route
     */
    static void visualizeRoute(Graph<int> *graph, const std::vector<int> &route, int totalCost);

    /**
     * @brief Visualizes comparison between two routes
     * @param graph Pointer to graph object
     * @param bestRoute Vector of node IDs for best route
     * @param bestCost Total time of best route
     * @param altRoute Vector of node IDs for alternative route
     * @param altCost Total time of alternative route
     */
    static void visualizeComparison(Graph<int> *graph,
                                    const std::vector<int> &bestRoute, int bestCost,
                                    const std::vector<int> &altRoute, int altCost);

    /**
     * @brief Visualizes restricted route with restrictions
     * @param graph Pointer to graph object
     * @param route Vector of node IDs representing the route
     * @param totalTime Total time of the route
     * @param avoidedNodes Vector of avoided node IDs
     * @param avoidedSegments Vector of avoided segment pairs
     */
    static void visualizeRestrictedRoute(Graph<int> *graph,
                                         const vector<int> &route,
                                         int totalTime,
                                         const vector<int> &avoidedNodes,
                                         const vector<pair<int, int> > &avoidedSegments);

    /**
    * @brief Visualizes environmentally-friendly route
    * @param graph Pointer to graph object
    * @param drivingRoute Vector of node IDs for driving portion
    * @param drivingTime Time for driving portion
    * @param parkingNode Node ID where parking occurs
    * @param walkingRoute Vector of node IDs for walking portion
    * @param walkingTime Time for walking portion
    * @param totalTime Total time of complete route
    */
    static void visualizeEcoRoute(Graph<int> *graph,
                                  const vector<int> &drivingRoute,
                                  int drivingTime,
                                  int parkingNode,
                                  const vector<int> &walkingRoute,
                                  int walkingTime,
                                  int totalTime);

    /**
     * @brief Visualizes approximate solutions when exact route isn't possible
     * @param graph Pointer to graph object
     * @param solutions Vector of approximate solutions
     */
    static void visualizeApproximateSolutions(Graph<int> *graph,
                                              const vector<ApproximateSolution<int> > &solutions);
};

#endif
