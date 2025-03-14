#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "Routes.h"
using namespace std;

int optionsMenu();

template<class T>
void optionBestRoute(Graph<T> *g);

void optionRestrictedRoute();

void optionEnvironmentalRoute();

bool isModeDriving(const string& mode);

#endif //MENU_H
