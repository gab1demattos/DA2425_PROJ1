#include "Input.h"
#include <sstream>

bool isModeDriving(const string& mode) {
    string res;
    for (const char c : mode)
        res += static_cast<char>(tolower(c));
    return res == "driving";
}

bool InputBestRoute(string & mode, int & source, int & destination) {
    // Read from file
    ifstream inputFile("../Input/inputBestRoute.txt");
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



bool parseNodesToAvoid(const string &input, vector<int> &output) {
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        try {
            output.push_back(stoi(token));
        } catch (exception &e) {
            return false;  // Invalid integer format
        }
    }
    return true;
}

bool parseSegmentsToAvoid(const string &input, vector<pair<int, int>> &output) {
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
                output.push_back({stoi(first), stoi(second)});
            } catch (exception &e) {
                return false;  // Invalid number
            }
        }
    }
    return true;
}

bool isModeDrivingWalking(const string& mode) {
    string res;
    for (const char c : mode)
        res += static_cast<char>(tolower(c));
    return res == "driving-walking";
}

bool InputEnvironmentalRoute(string & mode, int & source, int & destination, int & maxWalkTime, vector<int> & avoidNodes, vector<pair<int, int> > & avoidSegments) {
    // Read from file
    ifstream inputFile("../Input/inputEnvironmentalRoute.txt");
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

bool InputRestrictedRoute(string & mode, int & source, int & destination, vector<int> & avoidNodes, vector<pair<int, int> > & avoidSegments, int & includeNode) {
    ifstream inputFile("../Input/inputRestrictedRoute.txt");
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