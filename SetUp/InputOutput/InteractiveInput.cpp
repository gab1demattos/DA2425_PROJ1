/**
* @file InteractiveInput.cpp
 * @brief Interactive menu input handling functions
 */
#include "InteractiveInput.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <climits>
#include "../DataStructures/Graph.h"
using namespace std;


/**
 * @brief Validates and parses source and destination node inputs
 * @param[out] source Reference to store the parsed source node ID
 * @param[out] destination Reference to store the parsed destination node ID
 * @param[in,out] line String used for input storage and processing
 * @param[in] g Pointer to the graph containing the nodes and edges
 * @return true if both inputs are valid integers, false otherwise
 * @details Prompts user for source and destination nodes, validates they are
 *          positive integers, and stores the parsed values in the output parameters.
 *          Clears and reuses the line string for both inputs.
 */
bool checkSourceDest(int &source, int &destination, string line, Graph<int> *g) {
    cout << "Enter Source: ";
    getline(cin, line);
    regex intRegex("^\\d+$");
    if (!regex_match(line, intRegex)) {
        return false; // Invalid input
    }
    source = stoi(line);

    // Check if source node exists in graph
    if (!g->findVertex(source)) {
        cout << "Error: Source node " << source << " does not exist in the graph." << endl;
        return false;
    }

    cout << "Enter Destination: ";
    getline(cin, line);
    if (!regex_match(line, intRegex)) {
        return false; // Invalid input
    }
    destination = stoi(line);

    // Check if destination node exists in graph
    if (!g->findVertex(destination)) {
        cout << "Error: Destination node " << destination << " does not exist in the graph." << endl;
        return false;
    }

    return true;
}


/**
 * @brief Validates and parses node IDs to avoid
 * @param[out] avoidNodes Reference to vector that will store parsed node IDs
 * @param[in,out] line String used for input storage and processing
 * @param[in] g Pointer to the graph containing the nodes and edges
 * @return true if input format is valid or empty, false otherwise
 * @details Prompts user for space-separated node IDs, validates the format,
 *          and stores parsed integers in the output vector. Accepts empty input.
 */
bool parseNodes(vector<int> &avoidNodes, string line, Graph<int> *g) {
    cout << "Enter Avoid Nodes (separated by spaces): ";
    getline(cin, line);

    // check if it's in the right format
    if (!line.empty()) {
        regex nodesRegex("^\\d+( \\d+)*$");
        if (!regex_match(line, nodesRegex)) {
            return false;
        }

        istringstream iss(line);
        int node;
        while (iss >> node) {
            // Check if node exists in graph
            if (!g->findVertex(node)) {
                cout << "Error: Node " << node << " does not exist in the graph." << endl;
                return false;
            }
            avoidNodes.push_back(node);
        }
    }
    return true;
}


/**
 * @brief Validates and parses segments to avoid
 * @param[out] avoidSegments Reference to vector that will store parsed segment pairs
 * @param[in,out] line String used for input storage and processing
 * @param[in] g Pointer to the graph containing the nodes and edges
 * @return true if input format is valid or empty, false otherwise
 * @details Prompts user for segment pairs in format "x,y z,w", validates the format,
 *          and stores parsed pairs in the output vector. Accepts empty input.
 */
bool parseSegments(vector<pair<int, int> > &avoidSegments, string line, Graph<int> *g) {

    cout << "Enter Avoid Segments (comma inside pairs, space between pairs): ";
    getline(cin, line);

    if (!line.empty()) {
        regex segmentsRegex("^\\d+,\\d+( \\d+,\\d+)*$");
        if (!regex_match(line, segmentsRegex)) {
            return false;
        }

        istringstream issSegments(line);
        string segment;
        while (issSegments >> segment) {
            replace(segment.begin(), segment.end(), ',', ' ');
            istringstream segmentStream(segment);
            int first, second;
            segmentStream >> first >> second;

            // Check if both nodes exist in graph
            if (!g->findVertex(first) || !g->findVertex(second)) {
                cout << "Error: One or both nodes in segment (" << first << "," << second <<
                        ") do not exist in the graph." << endl;
                return false;
            }

            // Check if edge exists between the nodes
            bool edgeExists = false;
            Vertex<int> *v1 = g->findVertex(first);
            for (auto e: v1->getAdj()) {
                if (e->getDest()->getInfo() == second) {
                    edgeExists = true;
                    break;
                }
            }
            if (!edgeExists) {
                cout << "Error: Edge between nodes " << first << " and " << second << " does not exist in the graph." <<
                        endl;
                return false;
            }

            avoidSegments.push_back(make_pair(first, second));
        }
    }
    return true;
}

bool InterInputBestRoute(string &mode, int &source, int &destination, Graph<int> *g) {
    cout << "Enter Mode: ";
    cin >> mode;
    if (mode != "driving" && mode != "Driving") {
        return false;
    }

    string line;
    cin.ignore();
    if (!checkSourceDest(source, destination, line, g)) {
        return false;
    }
    cout << endl;
    return true;
}

bool InterInputRestrictedRoute(string &mode, int &source, int &destination, vector<int> &avoidNodes,
                               vector<pair<int, int> > &avoidSegments, int &includeNode, Graph<int> *g) {
    cout << "Enter Mode: ";
    cin >> mode;
    if (mode != "driving" && mode != "Driving") {
        return false;
    }

    string line;
    cin.ignore();

    if (!checkSourceDest(source, destination, line, g)) {
        return false;
    }

    if (!parseNodes(avoidNodes, line, g)) {
        return false;
    }

    if (!parseSegments(avoidSegments, line, g)) {
        return false;
    }

    cout << "Enter Include Node: ";
    getline(cin, line);
    if (line.empty()) {
        includeNode = INT_MAX;
    } else {
        includeNode = stoi(line);
        // Check if include node exists in graph
        if (!g->findVertex(includeNode)) {
            cout << "Error: Include node " << includeNode << " does not exist in the graph." << endl;
            return false;
        }
    }
    return true;
}

bool InterInputEnvironmetalRoute(string &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes,
                                 vector<pair<int, int> > &avoidSegments, Graph<int> *g) {
    cout << "Enter Mode: ";
    cin >> mode;
    if (mode != "driving-walking" && mode != "Driving-walking") {
        return false;
    }

    string line;
    cin.ignore();

    if (!checkSourceDest(source, destination, line, g)) {
        return false;
    }

    cout << "Enter Max Walk Time: ";
    getline(cin, line);

    regex intRegex("^\\d+$");
    if (!regex_match(line, intRegex)) {
        return false;
    }
    maxWalkTime = stoi(line);

    if (!parseNodes(avoidNodes, line, g)) {
        return false;
    }

    if (!parseSegments(avoidSegments, line, g)) {
        return false;
    }
    return true;
}
