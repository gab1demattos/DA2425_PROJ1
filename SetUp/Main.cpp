#include "Map.h"
#include "Graph.h"
#include "Menu.h"

int main() {

    switch (int option = optionsMenu()) {
        case 1:
            cout << "Finding best and alternative independent routes..." << endl;
            optionBestRoute();
            break;
        case 2:
            cout << "Finding route based on the given restrictions..." << endl;
            optionRestrictedRoute();
            break;
        case 3:
            cout << "Finding driving-walking route..." << endl;
            optionEnvironmentalRoute();
            break;
        default:
            break;
    }

    //Graph<int>* graph = new Graph<int>();
    //createGraph(graph);

    return 0;
}
