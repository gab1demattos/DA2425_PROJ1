#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>

#include "Graph.h"
using namespace std;

int optionsMenu();

template<class T>
void optionBestRoute(Graph<T> *g);

template<class T>
void optionRestrictedRoute(Graph<T> *g);

template<class T>
void optionEnvironmentalRoute(Graph<T> *g);

void optionInputInfo(Graph<int> *g);

template<class T>
void handleMenuOption(int option, Graph<T> *g);

#endif //MENU_H
