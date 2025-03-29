#include "IndependentRoutePlanning.h"

#include <climits>
#include <vector>
#include <utility>
#include <algorithm>

#include "../InputOutput/Output.h"

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
void dijkstra(Graph<T> *g, const int &origin) {
    // Initialize the vertices
    for (auto v: g->getVertexSet()) {
        v->setDist(INT_MAX);
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
pair<vector<T>, int> BestRoute(Graph<T> *g, const int &origin, const int &dest) {
    dijkstra(g, origin);

    std::vector<T> res;
    auto v = g->findVertex(dest);
    if (v == nullptr || v->getDist() == INT_MAX) {
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

template<class T>
pair<vector<int>, int> AlternativeRoute(Graph<T> *g, const pair<vector<int>, int> &primaryRoute, int source,
                                        int destination) {
    // If primary route is empty or invalid, return empty alternative
    if (primaryRoute.first.empty() || primaryRoute.second == 0) {
        return make_pair(vector<int>(), 0);
    }

    // Create a new graph with the same nodes
    Graph<T> modifiedGraph;
    for (auto v: g->getVertexSet()) {
        modifiedGraph.addVertex(v->getInfo());
        // Copy node attributes
        auto newVertex = modifiedGraph.findVertex(v->getInfo());
        if (newVertex != nullptr) {
            newVertex->setLocation(v->getLocation());
            newVertex->setCode(v->getCode());
            newVertex->setParking(v->isParkingAvailable());
        }
    }

    // Copy all edges except those in the primary route
    for (auto v: g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            bool inPrimary = false;
            for (size_t i = 0; i < primaryRoute.first.size() - 1; ++i) {
                if (v->getInfo() == primaryRoute.first[i] &&
                    e->getDest()->getInfo() == primaryRoute.first[i + 1]) {
                    inPrimary = true;
                    break;
                }
            }
            if (!inPrimary) {
                modifiedGraph.addEdge(v->getInfo(), e->getDest()->getInfo(),
                                      e->getDriving(), e->getWalking());
            }
        }
    }

    // Find alternative route
    pair<vector<int>, int> alternativeRoute = BestRoute(&modifiedGraph, source, destination);

    // Check if alternative route is valid
    if (alternativeRoute.first.empty() || alternativeRoute.second <= primaryRoute.second) {
        // No valid alternative route exists or it's not longer than primary
        return make_pair(vector<int>(), 0);
    }

    return alternativeRoute;
}

// Add explicit instantiation
template pair<vector<int>, int> AlternativeRoute<int>(Graph<int> *, const pair<vector<int>, int> &, int, int);
