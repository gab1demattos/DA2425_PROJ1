#include "Menu.h"


int options() {

    cout << "----------------------------------------------" << endl;
    cout << "             CHOOSE AN OPTION" << endl;
    cout << "----------------------------------------------" << endl << endl;

    int choice;

    do {
        cout << "1: Best Route and Alternative Independent Route " << endl;
        cout << "2: Restricted Route Planning " << endl;
        cout << "3: Environmentally-Friendly Route Planning" << endl;
        cout << "4: Exit" << endl;
        cout << "Option: ";
        cin >> choice;
        cout << endl << endl;

        switch (choice) {
            case 1:
                // Implement T2.1: Fastest Route
                    break;
            case 2:
                // Implement T2.2: Restricted Route
                    break;
            case 3:
                // Implement T3.1: Environmentally-Friendly Route
                    break;
            case 4:
                std::cout << "Exiting...\n";
            break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
    return 0;
}