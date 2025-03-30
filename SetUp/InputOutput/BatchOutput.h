/**
* @file BatchOutput.h
 * @brief Outputs the results of batch mode route planning to a file
 */


#ifndef BATCHOUTPUT_H
#define BATCHOUTPUT_H

#include <vector>
#include "../DataStructures/Graph.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"

/**
 * @brief Outputs the best route and alternative route to a file
 * @param source Source node ID
 * @param destination Destination node ID
 * @param solBestRoute The best route and its total cost
 * @param solAlternativeRoute The alternative route and its total cost
 * @param outfile Output file to write the results
 */
void BatchOutputBestRoute(int source, int destination, const pair<vector<int>, int> &solBestRoute,
                                 const pair<vector<int>, int> &solAlternativeRoute, const string& outfile);

/**
 * @brief Outputs the restricted route to a file
 * @tparam T T Node ID type (typically int)
 * @param source Source node ID
 * @param destination Destination node ID
 * @param bestRestrictedRoute The best restricted route
 * @param totalTime Total time of the route
 * @param flag Indicates if the route is valid
 * @param outfile Output file to write the results
 */
template<class T>
void BatchOutputRestrictedRoute(int source, int destination, vector<T> bestRestrictedRoute,
                                int totalTime, bool flag, const string& outfile);


/**
 * @brief Outputs environmentally friendly route results to file in batch mode
 * @param source Source node ID
 * @param destination Destination node ID
 * @param solBestDrivingRoute Pair containing driving route path and time
 * @param solBestWalkingRoute Pair containing walking route path and time
 * @param parkingNode Node ID where parking occurs
 * @param totalTime Total time of the complete route
 * @param maxWalkTime Maximum walking time specified
 * @param approximateSolutions Vector of alternative solutions if primary fails
 * @param outfile Output file path
 */
void BatchOutputEnvironmentallyFriendlyRoute(int source, int destination,
                                                    const std::pair<std::vector<int>, int> &solBestDrivingRoute,
                                                    const std::pair<std::vector<int>, int> &solBestWalkingRoute,
                                                    const int &parkingNode, const int &totalTime, int maxWalkTime,
                                                    const vector<ApproximateSolution<int> > &approximateSolutions, const string& outfile);




#endif //BATCHOUTPUT_H
