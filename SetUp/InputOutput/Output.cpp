#include "Output.h"
#include <chrono>
#include <iostream>
#include <thread>
#include "Visualizer.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"

using namespace std;

bool OutputBestRoute(Graph<int> *graph, int source, int destination, const pair<vector<int>, int> &solBestRoute,
                     const pair<vector<int>, int> &solAlternativeRoute) {
    bool showMenu = false;

    vector<int> bestRoute = solBestRoute.first;
    int totalCost = solBestRoute.second;

    vector<int> alternativeRoute = solAlternativeRoute.first;
    int alternativeTime = solAlternativeRoute.second;

    // Output the source and destination
    cout << "Source:" << source << endl;
    cout << "Destination:" << destination << endl;

    // Output the best driving route
    cout << "BestDrivingRoute:";
    for (size_t i = 0; i < bestRoute.size(); ++i) {
        cout << bestRoute[i];
        if (i < bestRoute.size() - 1) {
            cout << ",";
        }
    }
    cout << "(" << totalCost << ")" << endl;

    if (alternativeRoute.empty()) {
        cout << "AlternativeRoute:None" << endl;
    } else {
        cout << "AlternativeRoute:";
        for (size_t i = 0; i < alternativeRoute.size(); ++i) {
            cout << alternativeRoute[i];
            if (i < alternativeRoute.size() - 1) {
                cout << ",";
            }
        }
        cout << "(" << alternativeTime << ")" << endl;
    }

    Visualizer::visualizeComparison(graph, bestRoute, totalCost, alternativeRoute, alternativeTime);

    cout << endl;
    cout << "Hope the solution was to your liking!" << endl;

    cout << "Are you ready to go back to the menu? [y/n] ";
    char response;
    cin >> response;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    if (response == 'y' || response == 'Y') {
        cout << "Redirecting you to the menu in 3 seconds...";
        cout.flush();
        for (int i = 3; i > 0; --i) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << " " << i << "...";
            cout.flush();
        }
        cout << endl << endl;
        showMenu = true;
    } else {
        cout << endl << "Ok! Goodbye!" << endl;
        cout << "Exiting in... ";
        cout.flush();
        for (int i = 3; i > 0; --i) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << " " << i << "...";
            cout.flush();
        }
        cout << endl << endl;
    }

    return showMenu;
}

template<class T>
bool OutputRestrictedRoute(Graph<T> *graph, int source, int destination, vector<T> bestRestrictedRoute, int totalTime,
                           const vector<T> &avoidNodes,
                           const vector<pair<T, T> > &avoidSegments) {
    bool showMenu = false;

    // output the source and destination
    cout << endl << "Source:" << source << endl;
    cout << "Destination:" << destination << endl;

    cout << "RestrictedDrivingRoute:";

    for (size_t i = 0; i < bestRestrictedRoute.size(); ++i) {
        cout << bestRestrictedRoute[i];
        if (i < bestRestrictedRoute.size() - 1) {
            cout << ",";
        }
    }

    cout << "(" << totalTime << ")" << endl;

    Visualizer::visualizeRestrictedRoute(graph, bestRestrictedRoute, totalTime, avoidNodes, avoidSegments);

    cout << endl;
    cout << "Hope the solution was to your liking!" << endl;
    cout << "Do you want to go back to the menu? [y/n] ";
    char response;
    cin >> response;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    if (response == 'y' || response == 'Y') {
        cout << "Redirecting you to the menu in 3 seconds...";
        cout.flush();
        for (int i = 3; i > 0; --i) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << " " << i << "...";
            cout.flush();
        }
        cout << endl << endl;
        showMenu = true;
    } else {
        cout << endl << "Ok! Goodbye!" << endl;
        cout << "Exiting in... ";
        cout.flush();
        for (int i = 3; i > 0; --i) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << " " << i << "...";
            cout.flush();
        }
        cout << endl << endl;
    }

    return showMenu;
}

template bool OutputRestrictedRoute<int>(Graph<int> *graph, int source, int destination,
                                         vector<int> bestRestrictedRoute, int totalTime,
                                         const vector<int> &avoidNodes,
                                         const vector<pair<int, int> > &avoidSegments);


bool OutputApproximateSolutions(Graph<int> *graph, int source, int destination,
                                int maxWalkTime, const vector<ApproximateSolution<int> > &solutions) {
    bool showMenu = false;

    cout << endl << "Source:" << source << endl;
    cout << "Destination:" << destination << endl;

    for (size_t i = 0; i < solutions.size(); ++i) {
        const auto &sol = solutions[i];
        cout << "DrivingRoute" << i + 1 << ":";
        for (size_t j = 0; j < sol.drivingRoute.size(); ++j) {
            cout << sol.drivingRoute[j];
            if (j < sol.drivingRoute.size() - 1) cout << ",";
        }
        cout << "(" << sol.drivingTime << ")" << endl;

        cout << "ParkingNode" << i + 1 << ":" << sol.parkingNode << endl;

        cout << "WalkingRoute" << i + 1 << ":";
        for (size_t j = 0; j < sol.walkingRoute.size(); ++j) {
            cout << sol.walkingRoute[j];
            if (j < sol.walkingRoute.size() - 1) cout << ",";
        }
        cout << "(" << sol.walkingTime << ")";
        cout << endl;

        cout << "TotalTime" << i + 1 << ":" << sol.totalTime << endl;
    }

    Visualizer::visualizeApproximateSolutions(graph, solutions);

    cout << endl;
    cout << "Hope the solution was to your liking!" << endl;
    cout << "Do you want to go back to the menu? [y/n] ";
    char response;
    cin >> response;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    if (response == 'y' || response == 'Y') {
        cout << "Redirecting you to the menu in 3 seconds...";
        cout.flush();
        for (int i = 3; i > 0; --i) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << " " << i << "...";
            cout.flush();
        }
        cout << endl << endl;
        showMenu = true;
    } else {
        cout << endl << "Ok! Goodbye!" << endl;
        cout << "Exiting in... ";
        cout.flush();
        for (int i = 3; i > 0; --i) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << " " << i << "...";
            cout.flush();
        }
        cout << endl << endl;
    }
    return showMenu;
}

bool OutputBestEnvironmentallyFriendlyRoute(Graph<int> *graph, int source, int destination,
                                            const pair<vector<int>, int> &solBestDrivingRoute,
                                            const pair<vector<int>, int> &solBestWalkingRoute, const int &parkingNode,
                                            const int &totalTime, int maxWalkTime,
                                            const vector<ApproximateSolution<int> > &approximateSolutions) {
    bool showMenu = false;

    vector<int> bestDrivingRoute = solBestDrivingRoute.first;
    int drivingTime = solBestDrivingRoute.second;

    vector<int> bestWalkingRoute = solBestWalkingRoute.first;
    int walkingTime = solBestWalkingRoute.second;

    // Output the source and destination
    cout << "Source:" << source << endl;
    cout << "Destination:" << destination << endl;


    cout << "DrivingRoute:";
    if (bestDrivingRoute.empty()) {
        cout << "None" << endl;
    } else {
        for (size_t i = 0; i < bestDrivingRoute.size(); ++i) {
            cout << bestDrivingRoute[i];
            if (i < bestDrivingRoute.size() - 1) {
                cout << ",";
            }
        }
        cout << "(" << drivingTime << ")" << endl;
    }

    cout << "ParkingNode:";
    if (parkingNode == -1) {
        cout << "None" << endl;
    } else {
        cout << parkingNode << endl;
    }


    cout << "WalkingRoute:";
    if (bestWalkingRoute.empty()) {
        cout << "None" << endl;
    } else {
        for (size_t i = 0; i < bestWalkingRoute.size(); ++i) {
            cout << bestWalkingRoute[i];
            if (i < bestWalkingRoute.size() - 1) {
                cout << ",";
            }
        }
        cout << "(" << walkingTime << ")" << endl;
    }

    cout << "TotalTime:";

    if (totalTime < 0) {
        cout << "" << endl;
        cout << "Message: ";
        if (totalTime == -1) {
            cout << "There are no possible routes because nodes are adj" << endl;
        } else if (totalTime == -2) {
            cout << "There are no parking spots available" << endl;
        } else if (totalTime == -3) {
            cout << "There are no possible routes with max. walking time given" << endl;

            // NEW UX PROMPT
            cout << "\nDo you want an approximate solution to your problem? [y/n] ";
            char response;
            cin >> response;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

            if (response == 'y' || response == 'Y') {
                if (!approximateSolutions.empty()) {
                    showMenu = OutputApproximateSolutions(graph, source, destination, maxWalkTime,
                                                          approximateSolutions);
                } else {
                    cout << "No approximate solutions found." << endl;
                }
            } else {
                cout << "\nOh :/. No worries though!" << endl;
                cout << "Redirecting you to the menu in 3 seconds...";
                cout.flush();

                for (int i = 3; i > 0; --i) {
                    this_thread::sleep_for(chrono::seconds(1));
                    cout << " " << i << "...";
                    cout.flush();
                }
                cout << endl << endl;
                showMenu = true;
            }
        }
    } else {
        cout << totalTime << endl;

        Visualizer::visualizeEcoRoute(graph,
                                      solBestDrivingRoute.first,
                                      solBestDrivingRoute.second,
                                      parkingNode,
                                      solBestWalkingRoute.first,
                                      solBestWalkingRoute.second,
                                      totalTime);

        cout << endl;
        cout << "Hope the solution was to your liking!" << endl;
        cout << "Do you want to go back to the menu? [y/n] ";
        char response;
        cin >> response;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        if (response == 'y' || response == 'Y') {
            cout << "Redirecting you to the menu in 3 seconds...";
            cout.flush();
            for (int i = 3; i > 0; --i) {
                this_thread::sleep_for(chrono::seconds(1));
                cout << " " << i << "...";
                cout.flush();
            }
            cout << endl << endl;
            showMenu = true;
        } else {
            cout << endl << "Ok! Goodbye!" << endl;
            cout << "Exiting in... ";
            cout.flush();
            for (int i = 3; i > 0; --i) {
                this_thread::sleep_for(chrono::seconds(1));
                cout << " " << i << "...";
                cout.flush();
            }
            cout << endl << endl;
        }
    }

    return showMenu;
}
