#ifndef RESTRICTEDROUTEPLANNING_H
#define RESTRICTEDROUTEPLANNING_H
#include "../DataStructures/Graph.h"

template<class T>
void RestrictedRoutePlanning(Graph<T> *g, const int &origin, const int &dest, const vector<T> &avoidNodes,
                             const vector<pair<T, T> > &avoidSegments, const T &includeNode, vector<T> &route,
                             int &totalTime);

#endif //RESTRICTEDROUTEPLANNING_H
