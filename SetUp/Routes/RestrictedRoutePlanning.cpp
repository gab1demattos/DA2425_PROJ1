/**
* @file RestrictedRoutePlanning.cpp
 * @brief Route planning with node/segment restrictions and required nodes
 */

#include "RestrictedRoutePlanning.h"
#include "../DataStructures/Graph.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>
#include <cstdint>

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
 * @brief Helper function that initializes all vertices for Dijkstra's algorithm
 * @tparam T Node ID type (typically int)
 * @param g Graph object
 *
 * @details Sets all vertices to:
 * - Distance = INT_MAX
 * - Path = nullptr
 * - Visited = false
 */
template<class T>
void initializeVertices(Graph<T> *g) {
    for (auto v: g->getVertexSet()) {
        v->setDist(INT_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }
}

template<class T>
void runDijkstra(Graph<T> *g, Vertex<T> *start, const vector<T> &avoidNodes, const vector<pair<T, T> > &avoidSegments) {
    MutablePriorityQueue<Vertex<T> > q;
    q.insert(start);

    while (!q.empty()) {
        auto v = q.extractMin();
        for (auto e: v->getAdj()) {
            // skip restricted nodes
            if (std::find(avoidNodes.begin(), avoidNodes.end(), e->getDest()->getInfo()) != avoidNodes.end())
                continue;
            // skip restricted segments
            if (std::find(avoidSegments.begin(), avoidSegments.end(),
                          std::make_pair(e->getOrig()->getInfo(), e->getDest()->getInfo())) != avoidSegments.end()) {
                continue;
            }
            auto oldDist = e->getDest()->getDist();
            if (relax(e)) {
                if (oldDist == INT_MAX) {
                    q.insert(e->getDest());
                } else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

template<class T>
void RestrictedRoutePlanning(Graph<T> *g, const int &origin, const int &dest, const vector<T> &avoidNodes,
                             const vector<pair<T, T> > &avoidSegments, const T &includeNode, vector<T> &route,
                             int &totalTime, bool &flag) {
    flag = true;
    // Determine if we have a valid includeNode (not 32760)
    const T INVALID_NODE = INT_MAX; // Or whatever your magic number is
    bool hasIncludeNode = (includeNode != INVALID_NODE && g->findVertex(includeNode) != nullptr);

    if (!hasIncludeNode) {
        // CASE 1: No include node specified - find direct path with restrictions
        initializeVertices(g);
        auto startVertex = g->findVertex(origin);
        if (!startVertex) {
            //std::cout << "RestrictedDrivingRoute:None" << std::endl;
            flag = false;
            return;
        }
        startVertex->setDist(0);

        runDijkstra(g, startVertex, avoidNodes, avoidSegments);

        Vertex<T> *destVertex = g->findVertex(dest);
        if (!destVertex || destVertex->getDist() == INT_MAX) {
            flag = false;
            //std::cout << "RestrictedDrivingRoute:None" << std::endl;
            return;
        }

        // Reconstruct path
        route.clear();
        totalTime = 0;
        for (Vertex<T> *v = destVertex; v != nullptr; v = v->getPath() ? v->getPath()->getOrig() : nullptr) {
            route.insert(route.begin(), v->getInfo());
            if (v->getPath() != nullptr) {
                totalTime += v->getPath()->getDriving();
            }
        }
    } else {
        // CASE 2: With include node - two-phase approach
        route.clear();
        totalTime = 0;

        // Phase 1: Origin → IncludeNode
        initializeVertices(g);
        auto startVertex = g->findVertex(origin);
        startVertex->setDist(0);
        runDijkstra(g, startVertex, avoidNodes, avoidSegments);

        Vertex<T> *includeVertex = g->findVertex(includeNode);
        if (!includeVertex || includeVertex->getDist() == INT_MAX) {
            flag = false;
            return;
        }

        // Reconstruct first part of path
        vector<T> firstPart;
        int firstPartTime = includeVertex->getDist();
        for (Vertex<T> *v = includeVertex; v != nullptr; v = v->getPath() ? v->getPath()->getOrig() : nullptr) {
            firstPart.push_back(v->getInfo());
        }

        // Phase 2: IncludeNode → Destination
        initializeVertices(g);
        includeVertex->setDist(0);
        runDijkstra(g, includeVertex, avoidNodes, avoidSegments);

        Vertex<T> *destVertex = g->findVertex(dest);
        if (!destVertex || destVertex->getDist() == INT_MAX) {
            flag = false;
            return;
        }

        // Reconstruct second part of path
        vector<T> secondPart;
        int secondPartTime = destVertex->getDist();
        for (Vertex<T> *v = destVertex; v != nullptr && v->getInfo() != includeNode; v = v->getPath()
                         ? v->getPath()->getOrig()
                         : nullptr) {
            secondPart.push_back(v->getInfo());
        }

        // Combine paths
        route.insert(route.end(), firstPart.rbegin(), firstPart.rend()); // first part is built backwards, so reverse it
        route.insert(route.end(), secondPart.begin(), secondPart.end());
        // second part is already built in correct order

        // Remove duplicate includeNode if present
        if (!route.empty() && route.back() == includeNode) {
            route.pop_back();
        }

        totalTime = firstPartTime + secondPartTime;
    }
}

template void RestrictedRoutePlanning<int>(Graph<int> *g, const int &origin, const int &dest,
                                           const vector<int> &avoidNodes, const vector<pair<int, int> > &avoidSegments,
                                           const int &includeNode, std::vector<int> &route, int &totalTime, bool &flag);
