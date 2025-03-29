#include "BatchMode.h"
#include "../Routes/IndependentRoutePlanning.h"
#include "../Routes/RestrictedRoutePlanning.h"
#include "../Routes/EnvironmentallyFriendlyRoutePlanning.h"
#include <iostream>
#include <sstream>
#include <regex>

bool BatchMode::processBatchMode(Graph<int>& graph, const std::string& inputFile, const std::string& outputFile) {
    std::cout << "Starting batch mode processing..." << std::endl;
    
    if (!validateInputFile(inputFile)) {
        std::cerr << "Invalid input file structure. Ignoring batch mode." << std::endl;
        return false;
    }

    std::cout << "Input file validated successfully." << std::endl;

    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);
    std::string mode, line;

    // Read mode from first line
    std::getline(inFile, line);
    std::cout << "Read line: " << line << std::endl;
    
    mode = line.substr(line.find(':') + 1); // Extract mode after "Mode:"
    std::cout << "Extracted mode: " << mode << std::endl;

    bool success = false;
    if (mode == "driving") {
        std::cout << "Processing best route mode..." << std::endl;
        success = processBestRoute(graph, inFile, outFile);
    } else if (mode == "driving-walking") {
        std::cout << "Processing environmental route mode..." << std::endl;
        success = processEnvironmentalRoute(graph, inFile, outFile);
    } else {
        std::cerr << "Invalid mode specified: " << mode << std::endl;
        return false;
    }

    return success;
}

bool BatchMode::validateInputFile(const std::string& inputFile) {
    std::cout << "Validating input file: " << inputFile << std::endl;
    
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Could not open input file." << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); // First line should be Mode
    std::cout << "First line: " << line << std::endl;
    
    if (line.find("Mode:") == std::string::npos) {
        std::cerr << "First line does not contain 'Mode:'." << std::endl;
        return false;
    }

    return true;
}

bool BatchMode::validateOutputFile(const std::string& outputFile) {
    std::ofstream file(outputFile);
    if (!file.is_open()) {
        return false;
    }
    return true;
}

void BatchMode::writeOutput(const std::string& outputFile, const std::string& result) {
    std::ofstream outFile(outputFile);
    if (outFile.is_open()) {
        outFile << result;
    }
}

bool BatchMode::processBestRoute(Graph<int>& graph, std::ifstream& inFile, std::ofstream& outFile) {
    std::cout << "Processing best route..." << std::endl;
    
    std::string line;
    int source, destination;

    // Read source
    std::getline(inFile, line);
    std::cout << "Source line: " << line << std::endl;
    source = std::stoi(line.substr(line.find(':') + 1));
    std::cout << "Source: " << source << std::endl;

    // Read destination
    std::getline(inFile, line);
    std::cout << "Destination line: " << line << std::endl;
    destination = std::stoi(line.substr(line.find(':') + 1));
    std::cout << "Destination: " << destination << std::endl;

    // Process route and get results
    std::cout << "Calling BestRoute..." << std::endl;
    auto bestRoute = BestRoute(&graph, source, destination);
    std::cout << "Calling AlternativeRoute..." << std::endl;
    auto altRoute = AlternativeRoute(&graph, bestRoute, source, destination);

    // Format output according to Output.h specifications
    std::stringstream ss;
    ss << "Source:" << source << "\n";
    ss << "Destination:" << destination << "\n";
    
    // Format best route
    ss << "BestDrivingRoute:";
    for (const auto& node : bestRoute.first) {
        ss << node << ",";
    }
    ss.seekp(-1, std::ios_base::end); // Remove last comma
    ss << "(" << bestRoute.second << ")\n";

    // Format alternative route
    ss << "AlternativeRoute:";
    if (!altRoute.first.empty()) {
        for (const auto& node : altRoute.first) {
            ss << node << ",";
        }
        ss.seekp(-1, std::ios_base::end); // Remove last comma
        ss << "(" << altRoute.second << ")\n";
    } else {
        ss << "None\n";
    }

    outFile << ss.str();
    std::cout << "Best route processing completed." << std::endl;
    return true;
}

bool BatchMode::processRestrictedRoute(Graph<int>& graph, std::ifstream& inFile, std::ofstream& outFile) {
    std::string line;
    int source, destination, includeNode;
    std::vector<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidSegments;

    // Read source and destination
    std::getline(inFile, line);
    source = std::stoi(line.substr(line.find(':') + 1));
    std::getline(inFile, line);
    destination = std::stoi(line.substr(line.find(':') + 1));

    // Read avoid nodes if present
    std::getline(inFile, line);
    if (line.find("AvoidNodes:") != std::string::npos) {
        std::string nodes = line.substr(line.find(':') + 1);
        std::istringstream iss(nodes);
        std::string node;
        while (std::getline(iss, node, ',')) {
            avoidNodes.push_back(std::stoi(node));
        }
    }

    // Read avoid segments if present
    std::getline(inFile, line);
    if (line.find("AvoidSegments:") != std::string::npos) {
        std::string segments = line.substr(line.find(':') + 1);
        std::regex pattern("\\((\\d+),(\\d+)\\)");
        auto begin = std::sregex_iterator(segments.begin(), segments.end(), pattern);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            int first = std::stoi((*it)[1]);
            int second = std::stoi((*it)[2]);
            avoidSegments.emplace_back(first, second);
        }
    }

    // Read include node
    std::getline(inFile, line);
    includeNode = std::stoi(line.substr(line.find(':') + 1));

    // Process route and get results
    std::vector<int> restrictedRoute;
    int totalTime;
    RestrictedRoutePlanning(&graph, source, destination, avoidNodes, avoidSegments, includeNode, restrictedRoute, totalTime);

    // Format output according to Output.h specifications
    std::stringstream ss;
    ss << "Source:" << source << "\n";
    ss << "Destination:" << destination << "\n";
    ss << "RestrictedDrivingRoute:";
    if (!restrictedRoute.empty()) {
        for (const auto& node : restrictedRoute) {
            ss << node << ",";
        }
        ss.seekp(-1, std::ios_base::end); // Remove last comma
        ss << "(" << totalTime << ")\n";
    } else {
        ss << "None\n";
    }

    outFile << ss.str();
    return true;
}

bool BatchMode::processEnvironmentalRoute(Graph<int>& graph, std::ifstream& inFile, std::ofstream& outFile) {
    std::string line;
    int source, destination, maxWalkTime;
    std::vector<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidSegments;

    // Read source and destination
    std::getline(inFile, line);
    source = std::stoi(line.substr(line.find(':') + 1));
    std::getline(inFile, line);
    destination = std::stoi(line.substr(line.find(':') + 1));

    // Read max walk time
    std::getline(inFile, line);
    maxWalkTime = std::stoi(line.substr(line.find(':') + 1));

    // Read avoid nodes if present
    std::getline(inFile, line);
    if (line.find("AvoidNodes:") != std::string::npos) {
        std::string nodes = line.substr(line.find(':') + 1);
        std::istringstream iss(nodes);
        std::string node;
        while (std::getline(iss, node, ',')) {
            avoidNodes.push_back(std::stoi(node));
        }
    }

    // Read avoid segments if present
    std::getline(inFile, line);
    if (line.find("AvoidSegments:") != std::string::npos) {
        std::string segments = line.substr(line.find(':') + 1);
        std::regex pattern("\\((\\d+),(\\d+)\\)");
        auto begin = std::sregex_iterator(segments.begin(), segments.end(), pattern);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            int first = std::stoi((*it)[1]);
            int second = std::stoi((*it)[2]);
            avoidSegments.emplace_back(first, second);
        }
    }

    // Process route and get results
    std::pair<std::vector<int>, int> drivingRoute;
    int parkingNode;
    std::pair<std::vector<int>, int> walkingRoute;
    int totalTime;
    std::vector<ApproximateSolution<int>> approximateSolutions;

    EnvironmentallyFriendlyBestRoute(&graph, source, destination, maxWalkTime, avoidNodes, avoidSegments,
                                    drivingRoute, parkingNode, walkingRoute, totalTime, approximateSolutions);

    // Format output according to Output.h specifications
    std::stringstream ss;
    ss << "Source:" << source << "\n";
    ss << "Destination:" << destination << "\n";
    
    // Format driving route
    ss << "DrivingRoute:";
    if (!drivingRoute.first.empty()) {
        for (const auto& node : drivingRoute.first) {
            ss << node << ",";
        }
        ss.seekp(-1, std::ios_base::end); // Remove last comma
        ss << "(" << drivingRoute.second << ")\n";
    } else {
        ss << "None\n";
    }

    // Format parking node
    ss << "ParkingNode:" << (parkingNode != -1 ? std::to_string(parkingNode) : "None") << "\n";

    // Format walking route
    ss << "WalkingRoute:";
    if (!walkingRoute.first.empty()) {
        for (const auto& node : walkingRoute.first) {
            ss << node << ",";
        }
        ss.seekp(-1, std::ios_base::end); // Remove last comma
        ss << "(" << walkingRoute.second << ")\n";
    } else {
        ss << "None\n";
    }

    // Format total time
    ss << "TotalTime:" << (totalTime > 0 ? std::to_string(totalTime) : "") << "\n";

    // If no exact solution found, output approximate solutions
    if (!approximateSolutions.empty()) {
        ss << "\nApproximate Solutions:\n";
        for (size_t i = 0; i < approximateSolutions.size(); ++i) {
            const auto& sol = approximateSolutions[i];
            ss << "Solution " << i + 1 << ":\n";
            ss << "DrivingRoute" << i + 1 << ":";
            for (const auto& node : sol.drivingRoute) {
                ss << node << ",";
            }
            ss.seekp(-1, std::ios_base::end);
            ss << "(" << sol.drivingTime << ")\n";
            ss << "ParkingNode" << i + 1 << ":" << sol.parkingNode << "\n";
            ss << "WalkingRoute" << i + 1 << ":";
            for (const auto& node : sol.walkingRoute) {
                ss << node << ",";
            }
            ss.seekp(-1, std::ios_base::end);
            ss << "(" << sol.walkingTime << ")\n";
            ss << "TotalTime" << i + 1 << ":" << sol.totalTime << "\n";
        }
    }

    outFile << ss.str();
    return true;
} 