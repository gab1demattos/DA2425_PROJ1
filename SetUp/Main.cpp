#include "Map.h"
#include "Graph.h"
#include "IndependentRoutePlanning.h"
#include "Menu.h"
#include "readCSV.h"

int main() {
    Graph<int> graph;

    // read locations and add vertices to the graph
    readLocations("../Data/Locations.csv", graph);

    // read distances and add edges to the graph
    readDistances("../Data/Distances.csv", graph);

    cout << "Best Route: ";
    for (auto e: BestRoute(&graph, 3, 8).first) {
        cout << e << ',';
    }
    cout << "(" << BestRoute(&graph, 3, 8).second << ")" << endl;

    switch (int option = optionsMenu()) {
        case 1:
            cout << "Finding best and alternative independent routes..." << endl;
            //optionBestRoute(graph);
            break;
        case 2:
            cout << "Finding route based on the given restrictions..." << endl;
            //optionRestrictedRoute(graph);
            break;
        case 3:
            cout << "Finding driving-walking route..." << endl;
            //optionEnvironmentalRoute(graph);
            break;
        case 4:
            cout << "Exiting..." << endl;
        default:
            break;
    }


    return 0;
}
