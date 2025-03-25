#include "EnvironmentallyFriendlyRoutePlanning.h"
#include <queue>
#include <limits>
#include <vector>
#include <utility> // for std::pair
#include <algorithm>
#include <climits>

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
void restrictedDijkstra(Graph<T> * g, const T &origin, const vector<T> &avoidNodes, const vector<pair<T,T> > &avoidSegments) {

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
void EnvironmentallyFriendlyBestRoute(Graph<T>* g, const int& origin, const int& dest,
                                    const int& maxWalkTime, const vector<T>& avoidNodes,
                                    const vector<pair<T,T>>& avoidSegments,
                                    pair<vector<T>,int>& drivingRoute, T& parkingNode,
                                    pair<vector<T>,int>& walkingRoute, int& totalTime,
                                    vector<ApproximateSolution<T>>& approximateSolutions) {

  	totalTime = INT_MAX;

    // ensure src and dest are not adj
    auto src = g->findVertex(origin);
    for (auto e : src->getAdj()) {
        if (e->getOrig()->getInfo() == dest) {
            cout << "Origin and destination are adjacent nodes." << endl;
            totalTime = -1;    // means route is not possible bc nodes are adj
            return;
        }
    }

    // identify all parking nodes
    vector<Vertex<T> *> parkingNodes;
    for (auto v : g->getVertexSet()) {
        if (v->isParkingAvailable() && v->getInfo() != origin && v->getInfo() != dest)
            parkingNodes.push_back(v);
    }

    if (parkingNodes.empty()) {
        cout << "No available parking spots.\n";
        totalTime = -2;    // means route is not possible bc there are no parking nodes
        return;
    }


    // find shortest path from origin to each parking node
    restrictedDijkstra(g, origin, avoidNodes, avoidSegments);
    vector<pair<vector<T>, int> > drivingPaths;
    for (auto v : parkingNodes) {
        vector<T> drivingPath;
        int driveTime = 0;
        Vertex<T> *temp = v;

        while (temp->getPath() != nullptr) {
            auto edge = temp->getPath();
            driveTime += edge->getDriving();
            drivingPath.push_back(temp->getInfo());
            temp = edge->getOrig();
        }

        drivingPath.push_back(origin);
        reverse(drivingPath.begin(), drivingPath.end());
        drivingPaths.push_back(make_pair(drivingPath, driveTime));
    }


    // find shortest path from each parking node to dest
    vector<pair<vector<T>, int> > walkingPaths;
    for (auto drivingPath : drivingPaths) {
        T parkNode = drivingPath.first.back();
        restrictedDijkstra(g, parkNode, avoidNodes, avoidSegments);

        vector<T> walkingPath; // start from parking node
        walkingPath.push_back(parkNode);
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
			int total = drivingPath.second + walkTime;

            if (total < totalTime || (total == totalTime && walkTime > walkingRoute.second)) {
                totalTime = total;
                drivingRoute = make_pair(drivingPath.first, drivingPath.second);
                walkingRoute = make_pair(walkingPath, walkTime);
                parkingNode = parkNode;
            }
        }
    }

    // no routes found
    if (totalTime == INT_MAX) {
        parkingNode = -1;
        totalTime = -3;

        // Call the new function to find approximate solutions
        FindApproximateSolutions(g, drivingPaths, avoidNodes, avoidSegments, dest, approximateSolutions);
    }

}

// Add explicit instantiation
template void EnvironmentallyFriendlyBestRoute<int>(Graph<int>*, const int&, const int&, const int&, const vector<int>&, const vector<pair<int,int> >&, pair<vector<int>,int>&, int&, pair<vector<int>,int>&, int&, vector<ApproximateSolution<int>>& );

template <class T>
void FindApproximateSolutions(Graph<T>* g, const vector<pair<vector<T>,int>>& drivingPaths,
                            const vector<T>& avoidNodes, const vector<pair<T,T>>& avoidSegments,
                            int destination, vector<ApproximateSolution<T>>& approximateSolutions) {
    // Find all possible approximate solutions
    vector<ApproximateSolution<T>> allApproximates;

    for (const auto& drivingPath : drivingPaths) {
        T parkNode = drivingPath.first.back();
        restrictedDijkstra(g, parkNode, avoidNodes, avoidSegments);

        vector<T> walkingPath;
        walkingPath.push_back(parkNode);
        int walkTime = 0;
        Vertex<T>* v = g->findVertex(destination);

        while (v && v->getPath() != nullptr) {
            auto edge = v->getPath();
            walkTime += edge->getWalking();
            walkingPath.push_back(v->getInfo());
            v = edge->getOrig();
        }

        reverse(walkingPath.begin() + 1, walkingPath.end());

        ApproximateSolution<T> sol;
        sol.drivingRoute = drivingPath.first;
        sol.drivingTime = drivingPath.second;
        sol.parkingNode = parkNode;
        sol.walkingRoute = walkingPath;
        sol.walkingTime = walkTime;
        sol.totalTime = drivingPath.second + walkTime;

        allApproximates.push_back(sol);
    }

    // Sort by total time, then by walking time
    sort(allApproximates.begin(), allApproximates.end(),
        [](const ApproximateSolution<T>& a, const ApproximateSolution<T>& b) {
            if (a.totalTime != b.totalTime) return a.totalTime < b.totalTime;
            return a.walkingTime < b.walkingTime;
        });

    // Take top 2 solutions
    if (!allApproximates.empty()) {
        approximateSolutions.push_back(allApproximates[0]);
        if (allApproximates.size() > 1) {
            approximateSolutions.push_back(allApproximates[1]);
        }
    }
}