#include "readCSV.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <sstream>

#include "../DataStructures/Graph.h"

/**
 * @brief Reads location data from CSV file and populates the graph
 * @param filename Path to the CSV file containing location data
 * @param graph Graph object to populate with vertex data
 *
 * @details Expected CSV format:
 * Location,Id,Code,Parking
 *
 * Where:
 * - Location: Full location name
 * - Id: Unique node identifier (integer)
 * - Code: Short location code (string)
 * - Parking: 1 if parking available, 0 otherwise
 *
 * @note Skips the header line automatically
 * @note Creates vertices with associated location metadata
 */
void readLocations(const std::string &filename, Graph<int> &graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    // skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string location, idStr, code, parkingStr;

        std::getline(ss, location, ',');
        std::getline(ss, idStr, ',');
        std::getline(ss, code, ',');
        std::getline(ss, parkingStr, ',');

        int id = std::stoi(idStr);
        bool parking = (parkingStr == "1");

        // add vertex to the graph
        graph.addVertex(id);
        if (Vertex<int> *vertex = graph.findVertex(id)) {
            vertex->setLocation(location);
            vertex->setCode(code);
            vertex->setParking(parking);
        }
    }

    file.close();
}

/**
 * @brief Reads distance data from CSV file and populates graph edges
 * @param filename Path to the CSV file containing distance data
 * @param graph Graph object to populate with edge data
 *
 * @details Expected CSV format:
 * Location1,Location2,Driving,Walking
 *
 * Where:
 * - Location1: Source location code
 * - Location2: Destination location code
 * - Driving: Driving time in minutes or 'X' if not drivable
 * - Walking: Walking time in minutes
 *
 * @note Skips the header line automatically
 * @note 'X' in Driving column is converted to INT_MAX (unreachable)
 * @note Creates bidirectional edges with both driving and walking times
 * @note Only adds edges between vertices that exist in the graph
 */
void readDistances(const std::string &filename, Graph<int> &graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    // skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string loc1, loc2, drivingStr, walkingStr;

        std::getline(ss, loc1, ',');
        std::getline(ss, loc2, ',');
        std::getline(ss, drivingStr, ',');
        std::getline(ss, walkingStr, ',');

        int driving = (drivingStr == "X") ? INT_MAX : std::stoi(drivingStr);
        int walking = std::stoi(walkingStr);

        // find vertices by code
        Vertex<int> *v1 = graph.findVertexByCode(loc1);
        Vertex<int> *v2 = graph.findVertexByCode(loc2);

        if (v1 && v2) {
            // add bidirectional edge with driving and walking times
            graph.addBidirectionalEdge(v1->getInfo(), v2->getInfo(), driving, walking);
        }
    }

    file.close();
}
