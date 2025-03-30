#ifndef INTERACTIVEINPUT_H
#define INTERACTIVEINPUT_H
#include <string>
using namespace std;
#include <vector>

bool InterInputBestRoute(string &mode, int &source, int &destination);

bool InterInputRestrictedRoute(string &mode, int &source, int &destination, vector<int> &avoidNodes,
                          vector<pair<int, int> > &avoidSegments, int &includeNode);

bool InterInputEnvironmetalRoute(string &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes,
                             vector<pair<int, int> > &avoidSegments);




#endif //INTERACTIVEINPUT_H
