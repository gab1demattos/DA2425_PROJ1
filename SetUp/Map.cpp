#include "Map.h"

template <class T>
vector<Edge<T>*> getDistancesInfo(const string& filename, Graph<T> *graph) {
    const vector<string> distLines = readInputFile(filename);
    vector<Edge<T>*> distances;
    for (const string& line : distLines)
        distances.push_back(readDistancesFromFile<T>(line, graph));
    return distances;
}


template <class T>
vector<Vertex<T>*> getLocationsInfo(const string& filename) {
    const vector<string> locLines = readInputFile(filename);
    vector<Vertex<T>*> locations;
    for (const string& line : locLines)
        locations.push_back(readLocationFromFile<T>(line));
    return locations;
}