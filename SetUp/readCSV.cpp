#include "readCSV.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Graph.h"

void readLocations(const std::string& filename, Graph<int>& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the header line
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

        // Add vertex to the graph
        graph.addVertex(id);
        Vertex<int>* vertex = graph.findVertex(id);
        if (vertex) {
            vertex->setLocation(location);
            vertex->setCode(code);
            vertex->setParking(parking);
        }
    }

    file.close();
}

void readDistances(const std::string& filename, Graph<int>& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string loc1, loc2, drivingStr, walkingStr;

        std::getline(ss, loc1, ',');
        std::getline(ss, loc2, ',');
        std::getline(ss, drivingStr, ',');
        std::getline(ss, walkingStr, ',');

        int driving = (drivingStr == "X") ? INF : std::stoi(drivingStr);
        int walking = std::stoi(walkingStr);

        // Find vertices by code
        Vertex<int>* v1 = graph.findVertexByCode(loc1);
        Vertex<int>* v2 = graph.findVertexByCode(loc2);

        if (v1 && v2) {
            // Add bidirectional edge with driving and walking times
            graph.addBidirectionalEdge(v1->getInfo(), v2->getInfo(), driving, walking);
        }
    }

    file.close();
}
