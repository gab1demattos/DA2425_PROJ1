#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <vector>
#include <string>
#include "../DataStructures/Graph.h"

class Visualizer {
public:
    static void visualizeRoute(Graph<int> *graph, const std::vector<int> &route, int totalCost);

    static void visualizeComparison(Graph<int> *graph,
                                    const std::vector<int> &bestRoute, int bestCost,
                                    const std::vector<int> &altRoute, int altCost);

    static void visualizeRestrictedRoute(Graph<int> *graph,
                                         const vector<int> &route,
                                         int totalTime,
                                         const vector<int> &avoidedNodes,
                                         const vector<pair<int, int> > &avoidedSegments);
};

#endif
