#include "Graph.h"
#include "IndependentRoutePlanning.h"
#include "Menu.h"
#include "readCSV.h"

int main(int argc, char const *argv[]) {
    Graph<int> graph;

    // read locations and add vertices to the graph
    readLocations("../Data/PortoLocations.csv", graph);

    // read distances and add edges to the graph
    readDistances("../Data/PortoDistances.csv", graph);

    // Print the graph for debugging
    //printGraph(graph);

    switch (int option = optionsMenu()) {
        case 1:
            cout << "Finding best and alternative independent routes..." << endl << endl;
            optionBestRoute(&graph);
            break;
        case 2:
            cout << "Finding route based on the given restrictions..." << endl;
            optionRestrictedRoute(&graph);
            break;
        case 3:
            cout << "Finding driving-walking route..." << endl;
            optionEnvironmentalRoute(&graph);
            break;
        case 4:
            optionInputInfo(&graph);
            break;
        case 5:
            cout << "Exiting..." << endl;
        default:
            break;
    }

    return 0;
}
