/**
* @file EnvironmentallyFriendlyRoutePlanning.cpp
 * @brief Environmentally friendly route planning with driving and walking segments
 */

#include "EnvironmentallyFriendlyRoutePlanning.h"
#include <limits>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>

/**
 * @brief Relaxes an edge during Dijkstra's algorithm
 * @tparam T Node ID type (typically int)
 * @param edge Edge to relax
 * @return true if relaxation occurred (shorter path found), false otherwise
 *
 * @details Updates the destination vertex's distance if a shorter path is found
 * through this edge. Uses driving times for edge weights.
 */
template <class T>
bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDist() + edge->getDriving() < edge->getDest()->getDist()) { // we have found a better way to reach v
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getDriving()); // d[v] = d[u] + w(u,v)
        edge->getDest()->setPath(edge); // set the predecessor of v to u; in this case the edge from u to v
        return true;
    }
    return false;
}

template<class T>
void restrictedDijkstra(Graph<T> *g, const T &origin, const vector<T> &avoidNodes,
                        const vector<pair<T, T> > &avoidSegments) {
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
void EnvironmentallyFriendlyBestRoute(Graph<T> *g, const int &origin, const int &dest,
                                      const int &maxWalkTime, const vector<T> &avoidNodes,
                                      const vector<pair<T, T> > &avoidSegments,
                                      pair<vector<T>, int> &drivingRoute, T &parkingNode,
                                      pair<vector<T>, int> &walkingRoute, int &totalTime,
                                      vector<ApproximateSolution<T> > &approximateSolutions) {
    totalTime = INT_MAX;

    // ensure src and dest are not adj
    auto src = g->findVertex(origin);
    for (auto e: src->getAdj()) {
        if (e->getOrig()->getInfo() == dest) {
            cout << "Origin and destination are adjacent nodes." << endl;
            totalTime = -1; // means route is not possible bc nodes are adj
            return;
        }
    }

    // identify all parking nodes
    vector<Vertex<T> *> parkingNodes;
    for (auto v: g->getVertexSet()) {
        if (v->isParkingAvailable() && v->getInfo() != origin && v->getInfo() != dest)
            parkingNodes.push_back(v);
    }

    if (parkingNodes.empty()) {
        cout << "No available parking spots.\n";
        totalTime = -2; // means route is not possible bc there are no parking nodes
        return;
    }
    //////

    // Find all possible walking routes from dest to a parking node within maxTotalTime
    vector<pair<vector<T>, int> > validWalkingPaths;
    restrictedDijkstraWalking(g, dest, avoidNodes, avoidSegments);

    for (auto v : parkingNodes) {
        vector<T> walkingPath;
        int walkTime = 0;
        Vertex<T> *temp = v;

        while (temp->getPath() != nullptr) {
            auto edge = temp->getPath();
            walkTime += edge->getWalking();
            walkingPath.push_back(temp->getInfo());
            temp = edge->getOrig();
        }

        if (walkTime <= maxWalkTime) {
            walkingPath.push_back(dest);
            reverse(walkingPath.begin(), walkingPath.end());
            validWalkingPaths.push_back(make_pair(walkingPath, walkTime));
        }
    }

    // Find the shortest driving path from each valid parking node to origin
    vector<pair<vector<T>, int> > validDrivingPaths;
    for (auto &walkPath : validWalkingPaths) {
        T parkNode = walkPath.first.front();
        restrictedDijkstra(g, parkNode, avoidNodes, avoidSegments);

        vector<T> drivingPath;
        int driveTime = 0;
        Vertex<T> *v = g->findVertex(origin);

        while (v && v->getPath() != nullptr) {
            auto edge = v->getPath();
            driveTime += edge->getDriving();
            drivingPath.push_back(v->getInfo());
            v = edge->getOrig();
        }

        if (!drivingPath.empty()) {
            reverse(drivingPath.begin(), drivingPath.end());
            drivingPath.push_back(parkNode);
            validDrivingPaths.push_back(make_pair(drivingPath, driveTime));
            int total = driveTime + walkPath.second;

            if (total < totalTime || (total == totalTime && walkPath.second > walkingRoute.second)) {
                totalTime = total;
                drivingRoute = make_pair(drivingPath, driveTime);
                walkingRoute = walkPath;
                parkingNode = parkNode;
            }
        }
    }




    /////


    // no routes found
    if (totalTime == INT_MAX) {
        parkingNode = -1;
        totalTime = -3;

        // Call the new function to find approximate solutions
        //FindApproximateSolutions(g, drivingPaths, avoidNodes, avoidSegments, dest, approximateSolutions);
    }
}

// Add explicit instantiation
template void EnvironmentallyFriendlyBestRoute<int>(Graph<int> *, const int &, const int &, const int &,
                                                    const vector<int> &, const vector<pair<int, int> > &,
                                                    pair<vector<int>, int> &, int &, pair<vector<int>, int> &, int &,
                                                    vector<ApproximateSolution<int> > &);

/**
 * @brief Relax function for walking path Dijkstra
 * @tparam T Node ID type (typically int)
 * @param edge Edge to relax
 * @return true if relaxation occurred, false otherwise
 *
 * @note Uses walking times instead of driving times
 */
template<class T>
bool relaxWalking(Edge<T> *edge) {
    if (edge->getOrig()->getDist() + edge->getWalking() < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWalking());
        edge->getDest()->setPath(edge);
        return true;
    }
    return false;
}

template<class T>
void restrictedDijkstraWalking(Graph<T> *g, const T &origin, const vector<T> &avoidNodes,
                               const vector<pair<T, T> > &avoidSegments) {
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
            if (find(avoidNodes.begin(), avoidNodes.end(), e->getDest()->getInfo()) != avoidNodes.end())
                continue;
            if (find(avoidSegments.begin(), avoidSegments.end(),
                     make_pair(e->getOrig()->getInfo(), e->getDest()->getInfo())) != avoidSegments.end())
                continue;
            auto oldDist = e->getDest()->getDist();
            if (relaxWalking(e)) {
                if (oldDist == INT_MAX)
                    q.insert(e->getDest());
                else
                    q.decreaseKey(e->getDest());
            }
        }
    }
}


template<class T>
void FindApproximateSolutions(Graph<T> *g, const vector<pair<vector<T>, int> > &drivingPaths,
                              const vector<T> &avoidNodes, const vector<pair<T, T> > &avoidSegments,
                              int destination, vector<ApproximateSolution<T> > &approximateSolutions) {
    // Find all possible approximate solutions
    vector<ApproximateSolution<T> > allApproximates;

    for (const auto &drivingPath: drivingPaths) {
        T parkNode = drivingPath.first.back();
        restrictedDijkstraWalking(g, parkNode, avoidNodes, avoidSegments);

        vector<T> walkingPath;
        walkingPath.push_back(parkNode);
        int walkTime = 0;
        Vertex<T> *v = g->findVertex(destination);

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
         [](const ApproximateSolution<T> &a, const ApproximateSolution<T> &b) {
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
