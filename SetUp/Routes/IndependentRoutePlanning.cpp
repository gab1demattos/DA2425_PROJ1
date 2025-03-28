#include "IndependentRoutePlanning.h"

#include <limits>
#include <vector>
#include <utility>
#include <algorithm>

#include "../InputOutput/Output.h"

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
bool relax(Edge<T> *edge) {
    // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDist() + edge->getDriving() < edge->getDest()->getDist()) {
        // we have found a better way to reach v
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getDriving()); // d[v] = d[u] + w(u,v)
        edge->getDest()->setPath(edge); // set the predecessor of v to u; in this case the edge from u to v
        return true;
    }
    return false;
}

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
void dijkstra(Graph<T> *g, const int &origin) {
    // Initialize the vertices
    for (auto v: g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    auto s = g->findVertex(origin);
    s->setDist(0);

    MutablePriorityQueue<Vertex<T> > q;
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        for (auto e: v->getAdj()) {
            auto oldDist = e->getDest()->getDist();
            if (relax(e)) {
                if (oldDist == INF) {
                    q.insert(e->getDest());
                } else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

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
pair<vector<T>, int> BestRoute(Graph<T> *g, const int &origin, const int &dest) {
    dijkstra(g, origin);

    std::vector<T> res;
    auto v = g->findVertex(dest);
    if (v == nullptr || v->getDist() == INF) {
        // missing or disconnected
        return make_pair(res, 0);
    }

    // Reconstruct the path and calculate the total travel time
    int totalTime = 0;
    res.push_back(v->getInfo());
    while (v->getPath() != nullptr) {
        auto edge = v->getPath();
        totalTime += edge->getDriving(); // Add the driving time of the current edge
        v = edge->getOrig();
        res.push_back(v->getInfo());
    }
    reverse(res.begin(), res.end());

    if (res.empty() || res[0] != origin) {
        std::cout << "Origin not found!!" << std::endl;
    }

    return make_pair(res, totalTime);
}

// Add explicit instantiation
template pair<vector<int>, int> BestRoute<int>(Graph<int> *, const int &, const int &);

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
                                        int destination) {
    // Create a copy of the graph to avoid modifying the original
    Graph<T> modifiedGraph = *g;

    // Remove intermediate nodes of the primary route (except source and destination)
    for (size_t i = 1; i < primaryRoute.first.size() - 1; ++i) {
        modifiedGraph.removeVertex(primaryRoute.first[i]);
    }

    // Remove intermediate segments of the primary route
    for (size_t i = 0; i < primaryRoute.first.size() - 1; ++i) {
        modifiedGraph.removeEdge(primaryRoute.first[i], primaryRoute.first[i + 1]);
    }

    // Find the alternative route on the modified graph
    pair<vector<int>, int> alternativeRoute = BestRoute(&modifiedGraph, source, destination);

    if (alternativeRoute.first.empty() || alternativeRoute.second < primaryRoute.second) {
        // No valid alternative route exists
        alternativeRoute.first.clear(); // Mark as invalid
    }

    return alternativeRoute;
}

// Add explicit instantiation
template pair<vector<int>, int> AlternativeRoute<int>(Graph<int> *, const pair<vector<int>, int> &, int, int);
