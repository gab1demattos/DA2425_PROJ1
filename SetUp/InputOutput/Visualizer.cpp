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
