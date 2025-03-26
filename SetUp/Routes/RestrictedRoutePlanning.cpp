#include "RestrictedRoutePlanning.h"
#include "../DataStructures/Graph.h"

#include <vector>
#include <utility>
#include <algorithm>
#include <climits>
#include <cstdint>

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
void restrictedDijkstra(Graph<T> *g, const int &origin, const vector<T> &avoidNodes,
                        const vector<pair<T, T> > &avoidSegments, const T &includeNode) {
    // check if includeNode exists in the graph
    auto includeVertex = g->findVertex(includeNode);
    bool includeNodeExists = (includeVertex != nullptr);

    // initialize all vertices
    initializeVertices(g);

    // start vertex
    auto startVertex = g->findVertex(origin);
    startVertex->setDist(0);

    // first run of Dijkstra to find the shortest paths without considering includeNode
    runDijkstra(g, startVertex, avoidNodes, avoidSegments);

    // if includeNode exists and was not found in the first run, run Dijkstra again to include it
    if (includeNodeExists) {
        bool includeNodeFound = (includeVertex->getDist() != INT_MAX);

        if (!includeNodeFound) {
            // reset vertices and run Dijkstra from startVertex to includeVertex
            initializeVertices(g);
            startVertex->setDist(0);
            runDijkstra(g, startVertex, avoidNodes, avoidSegments);

            // if includeVertex is still not reachable, return (no valid path)
            if (includeVertex->getDist() == INT_MAX) {
                std::cout << "RestrictedDrivingRoute:none" << std::endl;
                return;
            }

            // reset vertices and run Dijkstra from includeVertex to all other nodes
            initializeVertices(g);
            includeVertex->setDist(0);
            runDijkstra(g, includeVertex, avoidNodes, avoidSegments);
        }
    }
}

template<class T>
void RestrictedRoutePlanning(Graph<T> *g, const int &origin, const int &dest, const vector<T> &avoidNodes,
                             const vector<pair<T, T> > &avoidSegments, const T &includeNode, vector<T> &route,
                             int &totalTime) {
    // First find path from origin to includeNode
    restrictedDijkstra(g, origin, avoidNodes, avoidSegments, includeNode);
    Vertex<T> *includeVertex = g->findVertex(includeNode);
    if (includeVertex == nullptr || includeVertex->getDist() == INT8_MAX) {
        std::cout << "RestrictedDrivingRoute:None" << std::endl;
        return;
    }

    // Reconstruct first part of path (origin to includeNode)
    vector<T> firstPart;
    int firstPartTime = 0;
    for (Vertex<T> *v = includeVertex; v != nullptr; v = v->getPath() ? v->getPath()->getOrig() : nullptr) {
        firstPart.push_back(v->getInfo());
        if (v->getPath() != nullptr) {
            firstPartTime += v->getPath()->getDriving();
        }
    }

    // Then find path from includeNode to destination
    restrictedDijkstra(g, includeNode, avoidNodes, avoidSegments, dest);
    Vertex<T> *destVertex = g->findVertex(dest);
    if (destVertex == nullptr || destVertex->getDist() == INT_MAX) {
        std::cout << "RestrictedDrivingRoute:None" << std::endl;
        return;
    }

    // Reconstruct second part of path (includeNode to destination)
    vector<T> secondPart;
    int secondPartTime = 0;
    for (Vertex<T> *v = destVertex; v != nullptr && v->getInfo() != includeNode; v = v->getPath()
             ? v->getPath()->getOrig()
             : nullptr) {
        secondPart.push_back(v->getInfo());
        if (v->getPath() != nullptr) {
            secondPartTime += v->getPath()->getDriving();
        }
    }

    // Combine paths (reverse first part + second part)
    route.insert(route.end(), firstPart.rbegin(), firstPart.rend());
    route.insert(route.end(), secondPart.rbegin(), secondPart.rend());

    // Remove duplicate includeNode if present
    if (!route.empty() && !secondPart.empty() && route.back() == secondPart.back()) {
        route.pop_back();
    }

    totalTime += firstPartTime + secondPartTime;
}

template void RestrictedRoutePlanning<int>(Graph<int> *g, const int &origin, const int &dest,
                                           const vector<int> &avoidNodes, const vector<pair<int, int> > &avoidSegments,
                                           const int &includeNode, std::vector<int> &route, int &totalTime);
