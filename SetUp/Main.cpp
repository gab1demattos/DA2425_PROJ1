#include "Map.h"
#include "Graph.h"
#include "IndependentRoutePlanning.h"
#include "Menu.h"
#include "readCSV.h"

int main() {
    // --- Example of a graph for testing the BestRoute function
    Graph<int> g1;
    g1.addVertex(1);
    g1.addVertex(2);
    g1.addVertex(3);
    g1.addVertex(4);
    g1.addEdge(1, 2, 5, 10); // Edge from 1 to 2 with driving time 5
    g1.addEdge(2, 3, 3, 6);  // Edge from 2 to 3 with driving time 3
    g1.addEdge(1, 3, 9, 18); // Edge from 1 to 3 with driving time 9
    g1.addEdge(3, 4, 2, 4);  // Edge from 3 to 4 with driving time 2

    int source = 1;
    int destination = 4;

    // Find the best route
    auto result = BestRoute(&g1, source, destination);

    // Output the result
    std::cout << "Best Route: ";
    for (size_t i = 0; i < result.first.size(); ++i) {
        std::cout << result.first[i];
        if (i < result.first.size() - 1) std::cout << ",";
    }
    std::cout << "(" << result.second << ")" << std::endl;
    // ---------------------------------------------------- Output: Best Route: 1,2,3,4(10)

    Graph<int> graph;

    // read locations and add vertices to the graph
    readLocations("../Data/Locations.csv", graph);

    // read distances and add edges to the graph
    readDistances("../Data/Distances.csv", graph);

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
