#include "Menu.h"


int optionsMenu() {

    cout << "----------------------------------------------" << endl;
    cout << "             CHOOSE AN OPTION" << endl;
    cout << "----------------------------------------------" << endl << endl;

    int i;

    do {
        cout << "1: Best Route and Alternative Independent Route " << endl;
        cout << "2: Restricted Route Planning " << endl;
        cout << "3: Environmentally-Friendly Route Planning" << endl;
        cout << "4: Exit" << endl;
        cout << "Option: ";
        cin >> i;
        cout << endl << endl;

        if (i > 4) cout << "Invalid input." << endl;
    } while (i > 4);
    return i;
}