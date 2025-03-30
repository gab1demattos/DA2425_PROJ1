#ifndef INTERACTIVEINPUT_H
#define INTERACTIVEINPUT_H
#include <string>
using namespace std;
#include <vector>

bool InterInputBestRoute(string &mode, int &source, int &destination);

bool InterInputRestrictedRoute(string &mode, int &source, int &destination, vector<int> &avoidNodes,
                          vector<pair<int, int> > &avoidSegments, int &includeNode);






#endif //INTERACTIVEINPUT_H
