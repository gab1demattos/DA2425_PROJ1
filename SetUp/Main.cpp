#include "DataStructures/Graph.h"
#include "Menu/Menu.h"
#include "ReadData/readCSV.h"

/**
 * @brief Main program execution
 * @return int Exit status (0 for success)
 *
 * @details Program flow:
 * 1. Initializes graph with Porto location data
 * 2. Presents menu options
 * 3. Executes selected routing algorithm
 *
 * @note Data files required:
 * - ../Data/PortoLocations.csv
 * - ../Data/PortoDistances.csv
 *
 * @see Graph
 * @see optionsMenu()
 * @see optionBestRoute()
 * @see optionRestrictedRoute()
 * @see optionEnvironmentalRoute()
 */
int main() {
    Graph<int> graph;

    // read locations and add vertices to the graph
    readLocations("../Data/PortoLocations.csv", graph);

    // read distances and add edges to the graph
    readDistances("../Data/PortoDistances.csv", graph);

    switch (optionsMenu()) {
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
