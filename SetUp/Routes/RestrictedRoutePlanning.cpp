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
#include <iostream>

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
    std::cout << "DEBUG: Starting Dijkstra from vertex " << start->getInfo() << std::endl;

    MutablePriorityQueue<Vertex<T> > q;
    q.insert(start);

    while (!q.empty()) {
        auto v = q.extractMin();
        for (auto e: v->getAdj()) {
            // Skip walking-only routes (driving time is INT_MAX)
            if (e->getDriving() == INT_MAX) {
                std::cout << "DEBUG: Skipping walking-only route " << e->getOrig()->getInfo() << "->" << e->getDest()->getInfo() << std::endl;
                continue;
            }

            // skip restricted nodes
            if (std::find(avoidNodes.begin(), avoidNodes.end(), e->getDest()->getInfo()) != avoidNodes.end()) {
                std::cout << "DEBUG: Skipping restricted node " << e->getDest()->getInfo() << std::endl;
                continue;
            }
            // skip restricted segments
            if (std::find(avoidSegments.begin(), avoidSegments.end(),
                          std::make_pair(e->getOrig()->getInfo(), e->getDest()->getInfo())) != avoidSegments.end()) {
                std::cout << "DEBUG: Skipping restricted segment " << e->getOrig()->getInfo() << "->" << e->getDest()->getInfo() << std::endl;
                continue;
            }

            auto oldDist = e->getDest()->getDist();
            if (relax(e)) {
                std::cout << "DEBUG: Updated distance to " << e->getDest()->getInfo() << " from " << oldDist << " to " << e->getDest()->getDist() << std::endl;
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
    const T INVALID_NODE = INT_MAX;
    bool hasIncludeNode = (includeNode != INVALID_NODE && g->findVertex(includeNode) != nullptr);

    if (!hasIncludeNode) {
        // Handle case without include node
        initializeVertices(g);
        auto startVertex = g->findVertex(origin);
        if (!startVertex) {
            flag = false;
            return;
        }
        startVertex->setDist(0);
        runDijkstra(g, startVertex, avoidNodes, avoidSegments);

        Vertex<T> *destVertex = g->findVertex(dest);
        if (!destVertex || destVertex->getDist() == INT_MAX) {
            flag = false;
            return;
        }

        route.clear();
        totalTime = 0;
        for (Vertex<T> *v = destVertex; v != nullptr; v = v->getPath() ? v->getPath()->getOrig() : nullptr) {
            route.insert(route.begin(), v->getInfo());
            if (v->getPath() != nullptr) {
                totalTime += v->getPath()->getDriving();
            }
        }
    } else {
        // Case with include node
        route.clear();
        totalTime = 0;

        // Phase 1: Find path from origin to include node
        // Add destination to avoid nodes to ensure we don't go through it
        vector<T> phase1AvoidNodes = avoidNodes;
        phase1AvoidNodes.push_back(dest);

        initializeVertices(g);
        auto startVertex = g->findVertex(origin);
        startVertex->setDist(0);
        runDijkstra(g, startVertex, phase1AvoidNodes, avoidSegments);

        Vertex<T> *includeVertex = g->findVertex(includeNode);
        if (!includeVertex || includeVertex->getDist() == INT_MAX) {
            flag = false;
            return;
        }

        // Store the first path
        vector<T> firstPart;
        int firstPartTime = includeVertex->getDist();
        for (Vertex<T> *v = includeVertex; v != nullptr; v = v->getPath() ? v->getPath()->getOrig() : nullptr) {
            firstPart.insert(firstPart.begin(), v->getInfo());
        }

        // Phase 2: Find path from include node to destination
        initializeVertices(g);
        includeVertex->setDist(0);
        runDijkstra(g, includeVertex, avoidNodes, avoidSegments);

        Vertex<T> *destVertex = g->findVertex(dest);
        if (!destVertex || destVertex->getDist() == INT_MAX) {
            flag = false;
            return;
        }

        // Store the second path
        vector<T> secondPart;
        int secondPartTime = destVertex->getDist();
        for (Vertex<T> *v = destVertex; v != nullptr; v = v->getPath() ? v->getPath()->getOrig() : nullptr) {
            secondPart.insert(secondPart.begin(), v->getInfo());
        }

        // Combine paths
        route = firstPart;
        if (!secondPart.empty()) {
            route.insert(route.end(), secondPart.begin() + 1, secondPart.end());
        }

        totalTime = firstPartTime + secondPartTime;
    }
}

template void RestrictedRoutePlanning<int>(Graph<int> *g, const int &origin, const int &dest,
                                           const vector<int> &avoidNodes, const vector<pair<int, int> > &avoidSegments,
                                           const int &includeNode, std::vector<int> &route, int &totalTime, bool &flag);
