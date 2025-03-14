#include "Map.h"
#include "Graph.h"
#include "Menu.h"

int main() {

    //Graph<int>* graph = new Graph<int>();
    //createGraph(graph);

    switch (int option = optionsMenu()) {
        case 1:
            cout << "Finding best and alternative independent routes..." << endl;
            //optionBestRoute(graph);
            break;
        case 2:
            cout << "Finding route based on the given restrictions..." << endl;
            //optionRestrictedRoute(graph);
            break;
        case 3:
            cout << "Finding driving-walking route..." << endl;
            //optionEnvironmentalRoute(graph);
            break;
        default:
            break;
    }


    return 0;
}
