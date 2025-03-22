#include "EnvironmentallyFriendlyRoutePlanning.h"
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
void restrictedDijkstra(Graph<T> * g, const int &origin, const vector<T> &avoidNodes, const vector<pair<T,T> > &avoidSegments) {

    // Initialize the vertices
    for(auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    auto s = g->findVertex(origin);
    s->setDist(0);

    MutablePriorityQueue<Vertex<T> > q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        for(auto e : v->getAdj()) {
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
pair<vector<T>,int> EnvironmentallyFriendlyBestRoute(Graph<T> * g, const int &origin, const int &dest, const int &maxWalkTime, const vector<T> &avoidNodes, const vector<pair<T,T> > &avoidSegments) {

    // identify all parking nodes
    vector<Vertex<T> *> parkingNodes;
    for (auto v : g->getVertexSet()) {
        if (v->isParkingAvailable() && v->getInfo() != origin && v->getInfo() != dest)
            parkingNodes.push_back(v);
    }

    // find shortest path from origin to each parking node
    restrictedDijkstra(g, origin, avoidNodes, avoidSegments);
    vector<pair<vector<T>, int> > drivingPaths;
    for (auto v : parkingNodes) {
        vector<T> drivingPath;
        int drivingTime = 0;
        Vertex<T> *temp = v;

        while (temp->getPath() != nullptr) {
            auto edge = temp->getPath();
            drivingTime += edge->getDriving();
            drivingPath.push_back(temp->getInfo());
            temp = edge->getOrig();
        }

        drivingPath.push_back(origin);
        reverse(drivingPath.begin(), drivingPath.end());
        drivingPaths.push_back(make_pair(drivingPath, drivingTime));
    }


    // find shortest path from each parking node to dest
    vector<pair<vector<T>, int> > walkingPaths;
    for (auto &drivingPath : drivingPaths) {
        T parkingNode = drivingPath.first.back();
        restrictedDijkstra(g, parkingNode, avoidNodes, avoidSegments);

        vector<T> walkingPath = {parkingNode}; // start from parking node
        int walkTime = 0;
        Vertex<T> *v = g->findVertex(dest);

        while (v && v->getPath() != nullptr) {
            auto edge = v->getPath();
            walkTime += edge->getWalking();
            walkingPath.push_back(v->getInfo());
            v = edge->getOrig();
        }

        if (walkTime <= maxWalkTime) {
            reverse(walkingPath.begin() + 1, walkingPath.end());
            walkingPaths.push_back(make_pair(walkingPath, walkTime));
        }
    }

}


// Add explicit instantiation
template pair<vector<int>,int> EnvironmentallyFriendlyBestRoute<int>(Graph<int>*, const int&, const int&, const int&, const vector<int>&, const vector<pair<int,int> >&);