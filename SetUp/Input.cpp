#include "Input.h"

#include <sstream>
#include <fstream>

vector<string> readInputFile(const string& filename) {
    vector<string> lines;

    ifstream ifs;
    ifs.open(filename); // opening file

    if (ifs.is_open()) {
        string line;
        while (getline(ifs, line))  // reading each line
            lines.push_back(line);  // and storing it in vector 'lines'
        ifs.close();    // close file
    }
    return lines;
}


void readLocations(const string& filename, Graph<int>& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        string name, code, idStr, parkingStr;
        int location_id;
        bool parking;

        getline(ss, name, ',');
        getline(ss, idStr, ',');
        location_id = stoi(idStr);
        getline(ss, code, ',');
        getline(ss, parkingStr, ',');
        parking = (parkingStr == "1");

        Vertex<int>* location = new Vertex<int>(location_id);
        location->setCode(code);
        location->setParking(parking);
        location->setLocation(name);
        graph.addVertex(location_id);
    }

    file.close();
}


void readDistances(const string& filename, Graph<int>& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        string loc1, loc2, driveTimeStr, walkTimeStr;
        int drivingTime, walkingTime;

        getline(ss, loc1, ',');
        getline(ss, loc2, ',');
        getline(ss, driveTimeStr, ',');
        getline(ss, walkTimeStr, ',');

        walkingTime = stoi(walkTimeStr);

        Vertex<int>* orig = graph.findVertexByCode(loc1);
        Vertex<int>* dest = graph.findVertexByCode(loc2);

        if (orig && dest) {
            // Only add driving edge if it is not "X"
            if (driveTimeStr != "X") {
                drivingTime = stoi(driveTimeStr);
                graph.addEdge(orig->getInfo(), dest->getInfo(), drivingTime, walkingTime);
            } else {
                // If "X", only add the walking edge
                graph.addEdge(orig->getInfo(), dest->getInfo(), 0, walkingTime);
            }
        }
    }

    file.close();
}

