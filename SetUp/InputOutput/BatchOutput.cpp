#include "BatchOutput.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "../DataStructures/Graph.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"
using namespace std;



template<class T>
bool BatchOutputRestrictedRoute(int source, int destination, vector<T> bestRestrictedRoute, int totalTime,
                           const vector<T> &avoidNodes,
                           const vector<pair<T, T> > &avoidSegments, const string& outfile);


bool BatchOutputEnvironmentallyFriendlyRoute(int source, int destination,
                                            const std::pair<std::vector<int>, int> &solBestDrivingRoute,
                                            const std::pair<std::vector<int>, int> &solBestWalkingRoute,
                                            const int &parkingNode, const int &totalTime, int maxWalkTime,
                                            const vector<ApproximateSolution<int> > &approximateSolutions, const string& outfile);
