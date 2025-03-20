#include "IndependentRoutePlanning.h"
#include <queue>
#include <limits>
#include <vector>
#include <utility> // for std::pair
#include <algorithm>

#include "Output.h"

template <class T>
bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDist() + edge->getDriving() < edge->getDest()->getDist()) { // we have found a better way to reach v
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getDriving()); // d[v] = d[u] + w(u,v)
        edge->getDest()->setPath(edge); // set the predecessor of v to u; in this case the edge from u to v
        return true;
    }
    return false;
}


template <class T>
void dijkstra(Graph<T> * g, const int &origin) {

    // Initialize the vertices
    for(auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    auto s = g->findVertex(origin);
    s->setDist(0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        for(auto e : v->getAdj()) {
            auto oldDist = e->getDest()->getDist();
            if (relax(e)) {
                if (oldDist == INF) {
                    q.insert(e->getDest());
                }
                else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

template <class T>
void BestRoute(Graph<T> * g, const int &origin, const int &dest) {
    dijkstra(g, origin);

    std::vector<T> res;
    auto v = g->findVertex(dest);
    if (v == nullptr || v->getDist() == INF) { // missing or disconnected
        outputBestRoute(origin, dest, res, 0);
        return;
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

    outputBestRoute(origin, dest, res, totalTime);
}

// Add explicit instantiation
template void BestRoute<int>(Graph<int>*, const int&, const int&);

