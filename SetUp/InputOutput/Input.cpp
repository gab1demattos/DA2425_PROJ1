/**
* @file Input.cpp
 * @brief Input handling functions for route planning system
 */

#include "Input.h"
#include <sstream>
#include <climits>

/**
 * @brief Helper function that checks if the given mode is "driving".
 * 
 * @param mode The mode string to check.
 * @return true If the mode is "driving".
 * @return false Otherwise.
 */
bool isModeDriving(const string &mode) {
    string res;
    for (const char c: mode)
        res += static_cast<char>(tolower(c));
    return res == "driving";
}


bool InputBestRoute(const string &file, string &mode, int &source, int &destination) {
    // Read from file
    ifstream inputFile(file);
    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.find("Mode:") != string::npos) {
            mode = line.substr(line.find(':') + 1);
        } else if (line.find("Source:") != string::npos) {
            source = stoi(line.substr(line.find(':') + 1));
        } else if (line.find("Destination:") != string::npos) {
            destination = stoi(line.substr(line.find(':') + 1));
        }
    }
    inputFile.close();

    if (!isModeDriving(mode)) {
        cout << "Invalid input." << endl;
        return false;
    }

    return true;
}

/**
 * @brief Helper function that parses a comma-separated string of node IDs to avoid
 * @param input Comma-separated string of node IDs
 * @param[out] output Vector to store parsed node IDs
 * @return true if parsing succeeded
 * @return false if invalid integer format encountered
 */
bool parseNodesToAvoid(const string &input, vector<int> &output) {
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        try {
            output.push_back(stoi(token));
        } catch (exception &e) {
            return false; // Invalid integer format
        }
    }
    return true;
}

/**
 * @brief Helper function that parses segments to avoid in format (x,y),(a,b)
 * @param input String containing segment pairs
 * @param[out] output Vector to store parsed segment pairs
 * @return true if parsing succeeded
 * @return false if invalid format encountered
 */
bool parseSegmentsToAvoid(const string &input, vector<pair<int, int> > &output) {
    stringstream ss(input);
    string token;

    while (getline(ss, token, ')')) {
        size_t openParen = token.find('(');
        if (openParen == string::npos) continue;

        string pairStr = token.substr(openParen + 1); // Remove '('
        stringstream pairStream(pairStr);
        string first, second;

        if (getline(pairStream, first, ',') && getline(pairStream, second, ',')) {
            try {
                output.emplace_back(stoi(first), stoi(second));
            } catch (exception &e) {
                return false; // Invalid number
            }
        }
    }
    return true;
}

/**
 * @brief Helper function that checks if mode is "driving-walking" (case insensitive)
 * @param mode Transportation mode string to check
 * @return true if mode is "driving-walking"
 * @return false otherwise
 */
bool isModeDrivingWalking(const string &mode) {
    string res;
    for (const char c: mode)
        res += static_cast<char>(tolower(c));
    return res == "driving-walking";
}


bool InputEnvironmentalRoute(const string &file, string &mode, int &source, int &destination, int &maxWalkTime,
                             vector<int> &avoidNodes,
                             vector<pair<int, int> > &avoidSegments) {
    // Read from file
    ifstream inputFile(file);
    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.find("Mode:") != string::npos) {
            mode = line.substr(line.find(':') + 1);
        } else if (line.find("Source:") != string::npos) {
            source = stoi(line.substr(line.find(':') + 1));
        } else if (line.find("Destination:") != string::npos) {
            destination = stoi(line.substr(line.find(':') + 1));
        } else if (line.find("MaxWalkTime:") != string::npos) {
            maxWalkTime = stoi(line.substr(line.find(':') + 1));
        } else if (line.find("AvoidNodes:") != string::npos) {
            string nodesStr = line.substr(line.find(':') + 1);
            if (!nodesStr.empty()) parseNodesToAvoid(nodesStr, avoidNodes);
        } else if (line.find("AvoidSegments:") != string::npos) {
            string segmentsStr = line.substr(line.find(':') + 1);
            if (!segmentsStr.empty()) parseSegmentsToAvoid(segmentsStr, avoidSegments);
        }
    }
    inputFile.close();

    if (!isModeDrivingWalking(mode)) {
        cout << "Invalid input." << endl;
        return false;
    }

    return true;
}


bool InputRestrictedRoute(const string &file, string &mode, int &source, int &destination, vector<int> &avoidNodes,
                          vector<pair<int, int> > &avoidSegments, int &includeNode) {
    ifstream inputFile(file);
    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.find("Mode:") != string::npos) {
            mode = line.substr(line.find(':') + 1);
        } else if (line.find("Source:") != string::npos) {
            source = stoi(line.substr(line.find(':') + 1));
        } else if (line.find("Destination:") != string::npos) {
            destination = stoi(line.substr(line.find(':') + 1));
        } else if (line.find("AvoidNodes:") != string::npos) {
            string nodesStr = line.substr(line.find(':') + 1);
            if (!nodesStr.empty()) parseNodesToAvoid(nodesStr, avoidNodes);
        } else if (line.find("AvoidSegments:") != string::npos) {
            string segmentsStr = line.substr(line.find(':') + 1);
            if (!segmentsStr.empty()) parseSegmentsToAvoid(segmentsStr, avoidSegments);
        } else if (line.find("IncludeNode:") != string::npos) {
            string include = line.substr(line.find(':') + 1);
            if (!include.empty()) {
                includeNode = stoi(line.substr(line.find(':') + 1));
            } else {
                includeNode = INT_MAX;
            }
        }
    }
    inputFile.close();

    if (!isModeDriving(mode)) {
        cout << "Invalid input." << endl;
        return false;
    }

    return true;
}
