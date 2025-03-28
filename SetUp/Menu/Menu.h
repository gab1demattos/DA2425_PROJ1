#ifndef MENU_H
#define MENU_H

/**
* @file Menu.h
 * @brief User interface and menu handling for route planning system
 */

#include <iostream>
#include <vector>
#include "../DataStructures/Graph.h"
using namespace std;

/**
 * @brief Displays the main menu options and gets user selection
 * @return Selected menu option (1-5)
 *
 * @note Menu options:
 * 1. Best Route and Alternative Independent Route
 * 2. Restricted Route Planning
 * 3. Environmentally-Friendly Route Planning
 * 4. Input Info
 * 5. Exit
 */
int optionsMenu();

/**
 * @brief Handles the Best Route planning option
 * @tparam T Node ID type (typically int)
 * @param g Pointer to the graph object
 *
 * @details Flow:
 * 1. Gets input using InputBestRoute()
 * 2. Calculates best route using BestRoute()
 * 3. Finds alternative route using AlternativeRoute()
 * 4. Displays results using OutputBestRoute()
 * 5. Returns to menu if requested
 */
template<class T>
void optionBestRoute(Graph<T> *g);

/**
 * @brief Handles the Restricted Route planning option
 * @tparam T Node ID type (typically int)
 * @param g Pointer to the graph object
 *
 * @details Flow:
 * 1. Gets input using InputRestrictedRoute()
 * 2. Calculates restricted route using RestrictedRoutePlanning()
 * 3. Displays results using OutputRestrictedRoute()
 * 4. Returns to menu if requested
 */
template<class T>
void optionRestrictedRoute(Graph<T> *g);

/**
 * @brief Handles the Environmentally Friendly Route planning option
 * @tparam T Node ID type (typically int)
 * @param g Pointer to the graph object
 *
 * @details Flow:
 * 1. Gets input using InputEnvironmentalRoute()
 * 2. Calculates route using EnvironmentallyFriendlyBestRoute()
 * 3. Displays results using OutputBestEnvironmentallyFriendlyRoute()
 * 4. Shows approximate solutions if no exact route found
 * 5. Returns to menu if requested
 */
template<class T>
void optionEnvironmentalRoute(Graph<T> *g);

/**
 * @brief Displays input format information to the user
 * @param g Pointer to the graph object (for maintaining context)
 *
 * @note Shows detailed format requirements for:
 * - Best Route input
 * - Restricted Route input
 * - Environmentally Friendly Route input
 * Includes notes about optional fields and file locations
 */
void optionInputInfo(Graph<int> *g);

/**
 * @brief Routes execution to the appropriate menu option handler
 * @tparam T Node ID type (typically int)
 * @param option Selected menu option (1-5)
 * @param g Pointer to the graph object
 *
 * @details Calls the corresponding function based on user selection:
 * 1 → optionBestRoute()
 * 2 → optionRestrictedRoute()
 * 3 → optionEnvironmentalRoute()
 * 4 → optionInputInfo()
 * 5 → Exits program
 */
template<class T>
void handleMenuOption(int option, Graph<T> *g);

#endif //MENU_H
