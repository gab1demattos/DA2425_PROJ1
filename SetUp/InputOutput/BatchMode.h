#ifndef BATCHMODE_H
#define BATCHMODE_H

#include "../DataStructures/Graph.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility>

class BatchMode {
public:
    /**
     * @brief Processes the batch mode input and generates output
     * @param graph Reference to the graph object
     * @param inputFile Path to the input file
     * @param outputFile Path to the output file
     * @return true if processing was successful
     * 
     * @note Input file format:
     * Mode:driving|driving-walking
     * Source:<int>
     * Destination:<int>
     * MaxWalkTime:<int> (for driving-walking mode)
     * AvoidNodes:<int>,<int>,... (optional)
     * AvoidSegments:(int,int),(int,int),... (optional)
     * IncludeNode:<int> (for restricted mode)
     */
    static bool processBatchMode(Graph<int>& graph, const std::string& inputFile, const std::string& outputFile);

private:
    static bool validateInputFile(const std::string& inputFile);
    static bool validateOutputFile(const std::string& outputFile);
    static void writeOutput(const std::string& outputFile, const std::string& result);
    static bool processBestRoute(Graph<int>& graph, std::ifstream& inFile, std::ofstream& outFile);
    static bool processRestrictedRoute(Graph<int>& graph, std::ifstream& inFile, std::ofstream& outFile);
    static bool processEnvironmentalRoute(Graph<int>& graph, std::ifstream& inFile, std::ofstream& outFile);
    static bool processBestRouteWithSourceDest(Graph<int>& graph, std::ifstream& inFile, std::ofstream& outFile, int source, int destination);
    static bool processRestrictedRouteWithSourceDest(Graph<int>& graph, std::ifstream& inFile, std::ofstream& outFile, int source, int destination);
};

#endif // BATCHMODE_H 