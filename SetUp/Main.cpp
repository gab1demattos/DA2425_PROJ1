#include "Map.h"
#include "Graph.h"
#include "Menu.h"
#include "readCSV.h"

int main() {
    Graph<int> graph;

    // read locations and add vertices to the graph
    readLocations("../Data/Locations.csv", graph);

    // read distances and add edges to the graph
    readDistances("../Data/Distances.csv", graph);

    options();
    return 0;
}
