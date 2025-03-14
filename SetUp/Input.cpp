#include "Input.h"
#include <sstream>
#include <fstream>

bool fileExists(const string& filename) {
    ifstream f;
    f.open(filename);
    if (f.is_open()) {
        f.close();
        return true;
    }
    return false;
}

vector<string> readInputFile(const string& filename) {
    vector<string> lines;
    ifstream ifs;

    if (fileExists(filename)) {
        ifs.open(filename); // opening file
        if (ifs.is_open()) {
            string line;
            while (getline(ifs, line))  // reading each line
                lines.push_back(line);  // and storing it in vector 'lines'
            ifs.close();    // close file
        }
    }

    return lines;
}


template <class T>
Vertex<T>* readLocationFromFile(const string& line) {
    stringstream ss(line);
    string name, code, value1, value2;
    T id;
    bool parking = false;

    getline(ss, name, ',');
    getline(ss, value1, ',');     // id (string)
    id = stoi(value1);           // convert id from string to int
    getline(ss, code, ',');
    getline(ss, value2, ',');    // parking (string)
    if (value2 == "1") parking = true;
    else if (value2 == "0") parking = false;

    Vertex<T>* location = new Vertex<T>(id);
    location->setCode(code);
    location->setParking(parking);
    location->setLocation(name);

    return location;
}

template <class T>
Edge<T>* readDistancesFromFile(const string& line, Graph<T>* graph) {
    stringstream ss(line);
    string loc1, loc2, value1, value2;
    int drivingTime, walkTime;

    getline(ss, loc1, ',');
    getline(ss, loc2, ',');

    getline(ss, value1, ',');   // driving time (string)
    if (value1 == "X") drivingTime = 0;
    else drivingTime = stoi(value1);     // convert from string to int

    getline(ss, value2, ',');    // parking (string)
    walkTime = stoi(value2);     // convert to int

    Vertex<T>* orig = graph->findVertexByCode(loc1);
    Vertex<T>* dest = graph->findVertexByCode(loc2);

    return new Edge<T>(orig, dest, drivingTime, walkTime);
}
