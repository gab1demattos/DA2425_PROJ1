#include "Map.h"
#include "Graph.h"
#include "IndependentRoutePlanning.h"
#include "Menu.h"
#include "readCSV.h"

int main() {
    Graph<int> graph;

    // read locations and add vertices to the graph
    readLocations("../Data/PortoLocations.csv", graph);

    // read distances and add edges to the graph
    readDistances("../Data/PortoDistances.csv", graph);

    // Print the graph for debugging
    //printGraph(graph);

    // std::cout << "Best Route: ";
    // for (size_t i = 0; i < BestRoute(&graph, 3, 8).first.size(); ++i) {
    //     std::cout << BestRoute(&graph, 3, 8).first[i];
    //    if (i < BestRoute(&graph, 3, 8).first.size() - 1) std::cout << ",";
    // }
    // std::cout << "(" << BestRoute(&graph, 3, 8).second << ")" << std::endl;

    switch (int option = optionsMenu()) {
        case 1:
            cout << "Finding best and alternative independent routes..." << endl;
            optionBestRoute(&graph);
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
