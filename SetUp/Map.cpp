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

template <class T>
void createGraph(Graph<T> *graph) {
    vector<Edge<int>*> edges = getDistancesInfo<int>("Data/Distances.csv", graph);
    vector<Vertex<int>*> vertices = getLocationsInfo<int>("Data/Locations.csv");

    for (Vertex<int>* vertex : vertices)
        graph->addVertex(vertex->getInfo());

    for (Edge<int>* edge : edges)
        graph->addEdge(edge->getOrig()->getInfo(), edge->getDest()->getInfo(), edge->getDriving(), edge->getWalking());
}