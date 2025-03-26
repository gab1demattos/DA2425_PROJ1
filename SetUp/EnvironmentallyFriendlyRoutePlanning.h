#ifndef ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H
#define ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H

#include "Graph.h"\

template <class T>
struct ApproximateSolution {
    vector<T> drivingRoute;
    int drivingTime;
    T parkingNode;
    vector<T> walkingRoute;
    int walkingTime;
    int totalTime;
};

template <class T>
void restrictedDijkstra(Graph<T> * g, const int &origin);

template <class T>
void FindApproximateSolutions(Graph<T>* g, const vector<pair<vector<T>,int>>& drivingPaths,
                            const vector<T>& avoidNodes, const vector<pair<T,T>>& avoidSegments,
                            int destination, vector<ApproximateSolution<T>>& approximateSolutions);

template <class T>
void EnvironmentallyFriendlyBestRoute(Graph<T>* g, const int& origin, const int& dest,
                                    const int& maxWalkTime, const vector<T>& avoidNodes,
                                    const vector<pair<T,T>>& avoidSegments,
                                    pair<vector<T>,int>& drivingRoute, T& parkingNode,
                                    pair<vector<T>,int>& walkingRoute, int& totalTime,
                                    vector<ApproximateSolution<T>>& approximateSolutions);
#endif //ENVIRONMENTALLYFRIENDLYROUTEPLANNING_H
