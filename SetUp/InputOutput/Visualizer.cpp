#include "Visualizer.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Visualizer::visualizeRoute(Graph<int> *graph, const vector<int> &route, int totalCost) {
    if (route.empty()) {
        cout << "  No route to visualize\n";
        return;
    }

    cout << "\n  Route Visualization:\n";
    cout << "  -------------------\n";

    for (size_t i = 0; i < route.size(); i++) {
        Vertex<int> *v = graph->findVertex(route[i]);
        if (!v) {
            cout << "  [ERROR: Vertex " << route[i] << " not found in graph]\n";
            continue;
        }

        string location = v->getLocation();
        if (location.empty()) location = "Unnamed Location";

        cout << "  [" << route[i] << "] " << location;

        if (i != route.size() - 1) {
            Vertex<int> *next = graph->findVertex(route[i + 1]);
            if (!next) {
                cout << "\n    |\n    ↓ [ERROR: Next vertex " << route[i + 1] << " not found]\n";
                continue;
            }

            bool edgeFound = false;
            int drivingTime = 0;

            // Find the edge between current and next nodes
            for (auto edge: v->getAdj()) {
                if (edge->getDest()->getInfo() == next->getInfo()) {
                    drivingTime = edge->getDriving();
                    edgeFound = true;
                    break;
                }
            }

            if (!edgeFound) {
                cout << "\n    |\n    ↓ [ERROR: No edge to vertex " << route[i + 1] << "]\n";
            } else {
                cout << "\n    |\n    ↓ " << drivingTime << " min\n";
            }
        }
    }

    cout << "\n  Total time: " << totalCost << " minutes\n";
}

void Visualizer::visualizeComparison(Graph<int> *graph,
                                     const vector<int> &bestRoute, int bestCost,
                                     const vector<int> &altRoute, int altCost) {
    cout << "\n  === Route Comparison ===\n";

    cout << "\n  -- Best Route --\n";
    visualizeRoute(graph, bestRoute, bestCost);

    if (!altRoute.empty()) {
        cout << "\n  -- Alternative Route --\n";
        visualizeRoute(graph, altRoute, altCost);

        cout << "\n  Comparison:\n";
        cout << "  • Best route: " << bestCost << " minutes\n";
        cout << "  • Alternative: " << altCost << " minutes (";
        if (bestCost < altCost) {
            cout << altCost - bestCost << " minutes slower)";
        } else {
            cout << bestCost - altCost << " minutes faster)";
        }
    } else {
        cout << "\n  No alternative route available\n";
    }
    cout << "\n";
}

void Visualizer::visualizeRestrictedRoute(Graph<int> *graph,
                                          const vector<int> &route,
                                          int totalTime,
                                          const vector<int> &avoidedNodes,
                                          const vector<pair<int, int> > &avoidedSegments) {
    if (route.empty()) {
        cout << "  No valid route found (avoided nodes/segments block all paths)\n";
        return;
    }

    cout << "\n  Restricted Route Visualization:\n";
    cout << "  ------------------------------\n";

    // Display avoidance info first
    if (!avoidedNodes.empty()) {
        cout << "  Avoided Nodes: ";
        for (int node: avoidedNodes) cout << node << " ";
        cout << "\n";
    }
    if (!avoidedSegments.empty()) {
        cout << "  Avoided Segments: ";
        for (auto &seg: avoidedSegments) cout << "(" << seg.first << "→" << seg.second << ") ";
        cout << "\n";
    }

    // Visualize the actual route
    for (size_t i = 0; i < route.size(); i++) {
        Vertex<int> *v = graph->findVertex(route[i]);
        string location = v ? v->getLocation() : "Unknown";

        cout << "  [" << route[i] << "] " << location;

        if (i != route.size() - 1) {
            // Get driving time between current and next node
            Vertex<int> *current = graph->findVertex(route[i]);
            Vertex<int> *next = graph->findVertex(route[i + 1]);
            int drivingTime = 0;

            for (auto edge: current->getAdj()) {
                if (edge->getDest()->getInfo() == next->getInfo()) {
                    drivingTime = edge->getDriving();
                    break;
                }
            }
            cout << "\n    |\n    ↓ " << drivingTime << " min\n";
        }
    }
    cout << "\n  Total time: " << totalTime << " minutes (with restrictions)\n";
}

void Visualizer::visualizeEcoRoute(Graph<int> *graph,
                                   const vector<int> &drivingRoute,
                                   int drivingTime,
                                   int parkingNode,
                                   const vector<int> &walkingRoute,
                                   int walkingTime,
                                   int totalTime) {
    cout << "\n  Eco-Friendly Route:\n";
    cout << "  ------------------\n";

    // Driving portion
    cout << "  DRIVING (" << drivingTime << " min):\n";
    for (size_t i = 0; i < drivingRoute.size(); i++) {
        Vertex<int> *v = graph->findVertex(drivingRoute[i]);
        cout << "  [" << drivingRoute[i] << "] " << v->getLocation();
        if (i != drivingRoute.size() - 1) {
            // Get driving time to next node
            int time = 0;
            for (auto e: v->getAdj()) {
                if (e->getDest()->getInfo() == drivingRoute[i + 1]) {
                    time = e->getDriving();
                    break;
                }
            }
            cout << "\n    |\n    ↓ " << time << " min\n";
        }
    }

    // Parking node
    Vertex<int> *park = graph->findVertex(parkingNode);
    cout << "\n  PARK at [" << parkingNode << "] " << park->getLocation();

    // Walking portion
    cout << "\n\n  WALKING (" << walkingTime << " min):\n";
    for (size_t i = 0; i < walkingRoute.size(); i++) {
        Vertex<int> *v = graph->findVertex(walkingRoute[i]);
        cout << "  [" << walkingRoute[i] << "] " << v->getLocation();
        if (i != walkingRoute.size() - 1) {
            // Get walking time to next node
            int time = 0;
            for (auto e: v->getAdj()) {
                if (e->getDest()->getInfo() == walkingRoute[i + 1]) {
                    time = e->getWalking();
                    break;
                }
            }
            cout << "\n    |\n    ↓ " << time << " min\n";
        }
    }

    cout << "\n  TOTAL TIME: " << totalTime << " minutes\n";
}

void Visualizer::visualizeApproximateSolutions(Graph<int> *graph,
                                               const vector<ApproximateSolution<int> > &solutions) {
    cout << "\n  Alternative Options:\n";
    cout << "  -------------------\n";

    for (size_t i = 0; i < solutions.size(); i++) {
        cout << "  OPTION " << i + 1 << ":\n";
        visualizeEcoRoute(graph,
                          solutions[i].drivingRoute,
                          solutions[i].drivingTime,
                          solutions[i].parkingNode,
                          solutions[i].walkingRoute,
                          solutions[i].walkingTime,
                          solutions[i].totalTime);
        cout << endl;
    }
}
