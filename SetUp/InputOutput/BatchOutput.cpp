#include "BatchOutput.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "../DataStructures/Graph.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"
using namespace std;






bool BatchOutputEnvironmentallyFriendlyRoute(int source, int destination,
                                            const std::pair<std::vector<int>, int> &solBestDrivingRoute,
                                            const std::pair<std::vector<int>, int> &solBestWalkingRoute,
                                            const int &parkingNode, const int &totalTime, int maxWalkTime,
                                            const vector<ApproximateSolution<int> > &approximateSolutions, const string& outfile);
