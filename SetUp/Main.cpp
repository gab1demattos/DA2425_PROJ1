/**
* \mainpage Route Planning Tool - Design of Algorithms
 *
 * This project uses Dijkstra's Algorithm in order to find the best route from a given source node
 * to a given destination node. Supports three routing modes with graph restrictions and
 * environmental constraints.
 *
 * Key Features
 * 1. Independent Route Planning - Classic shortest-path (time-based).
 * 2. Restricted Route Planning - Calculates shortest path taking in account segments and nodes to avoid,
 * as well as nodes to include in the route.
 * 3. Environmentally-Friendly Route Planning - Hybrid driving/walking route where the user can choose the
 * maximum time they are willing to walk after parking.
 *
 * Usage
 * 1. Load graph data from `Locations.csv` and `Distances.csv`.
 * 2. Select a routing mode via the interactive menu.
 * 3. Input source/destination nodes and constraints (if applicable).
 * 4. View the computed path and total time.
 *
 * @author Francisca Portugal, Gabriela de Mattos, Maria Luiza Vieira
 * @date 29/03/2025
 */

#include "DataStructures/Graph.h"
#include "Menu/Menu.h"
#include "ReadData/readCSV.h"

/**
 * @brief Main program execution
 * @return int Exit status (0 for success)
 *
 * @details Program flow:
 * 1. Loads graph data from CSV files
 * 2. Displays interactive menu
 * 3. Processes user-selected routing algorithm
 *
 * @note Required data files:
 * - ../Data/PortoLocations.csv
 * - ../Data/PortoDistances.csv
 *
 * @see Graph for underlying data structure
 * @see optionsMenu() for UI logic
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
