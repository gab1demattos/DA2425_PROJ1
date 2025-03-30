#include "BatchInput.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Input.h"
#include <vector>
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"
#include "../Routes/RestrictedRoutePlanning.h"
#include "../Routes/IndependentRoutePlanning.h"
using namespace std;

// Explicit template instantiation for int type
template void runBatchMode<int>(const string& infile, const string& outfile, Graph<int> *g);

