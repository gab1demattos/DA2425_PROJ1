#include "Map.h"
#include "Graph.h"
#include "Menu.h"

int main() {

    switch (int option = optionsMenu()) {
        case 0:
            cout << "Finding best and alternative independent routes..." << endl;
            break;
        case 1:
            cout << "Finding route based on the given restrictions..." << endl;
            break;
        case 3:
            cout << "Finding driving-walking route..." << endl;
            break;
        default:
            break;
    }

    //Graph<int>* graph = new Graph<int>();
    //createGraph(graph);

    return 0;
}
