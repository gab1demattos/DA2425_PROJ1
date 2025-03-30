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
#include <iostream>
#include "InputOutput/BatchInput.h"

/**
 * @brief Main program execution
 * @return int Exit status (0 for success)
 *
 * @details Program flow:
 * 1. Loads graph data from CSV files
 * 2. If command line arguments are provided, use batch mode
 * 3. Otherwise, show interactive menu
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
int main(int argc, char *argv[]) {
    Graph<int> graph;

    // read locations and add vertices to the graph
    readLocations("../Data/PortoLocations.csv", graph);

    // read distances and add edges to the graph
    readDistances("../Data/PortoDistances.csv", graph);

    if (argc == 3) {
        std::string inputFile = argv[1];
        std::string outputFile = argv[2];
        runBatchMode(inputFile, outputFile, &graph);
        std::cout << "Batch mode processing completed successfully." << std::endl;
        return 0;
    }

    // Interactive menu mode
    switch (optionsMenu()) {
        case 1:
            std::cout << "Finding best and alternative independent routes..." << std::endl << std::endl;
            optionBestRoute(&graph);
            break;
        case 2:
            std::cout << "Finding route based on the given restrictions..." << std::endl << std::endl;
            optionRestrictedRoute(&graph);
            break;
        case 3:
            std::cout << "Finding environmentally-friendly route..." << std::endl << std::endl;
            optionEnvironmentalRoute(&graph);
            break;
        case 4:
            optionInfo(&graph);
            break;
        case 5:
            std::cout << "Exiting..." << std::endl;
            return 0;
        default:
            break;
    }

    return 0;
}
