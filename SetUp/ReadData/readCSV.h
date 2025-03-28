#ifndef READCSV_H
#define READCSV_H

/**
* @file readCSV.h
 * @brief CSV file reading utilities for graph data
 */

#include <string>
#include "../DataStructures/Graph.h"

/**
 * @brief Reads location data from CSV file and populates the graph
 * @param filename Path to the CSV file containing location data
 * @param graph Graph object to populate with vertex data
 *
 * @details Expected CSV format:
 * Location,Id,Code,Parking
 *
 * Where:
 * - Location: Full location name
 * - Id: Unique node identifier (integer)
 * - Code: Short location code (string)
 * - Parking: 1 if parking available, 0 otherwise
 *
 * @note Skips the header line automatically
 * @note Creates vertices with associated location metadata
 */
void readLocations(const std::string &filename, Graph<int> &graph);

/**
 * @brief Reads distance data from CSV file and populates graph edges
 * @param filename Path to the CSV file containing distance data
 * @param graph Graph object to populate with edge data
 *
 * @details Expected CSV format:
 * Location1,Location2,Driving,Walking
 *
 * Where:
 * - Location1: Source location code
 * - Location2: Destination location code
 * - Driving: Driving time in minutes or 'X' if not drivable
 * - Walking: Walking time in minutes
 *
 * @note Skips the header line automatically
 * @note 'X' in Driving column is converted to INT_MAX (unreachable)
 * @note Creates bidirectional edges with both driving and walking times
 * @note Only adds edges between vertices that exist in the graph
 */
void readDistances(const std::string &filename, Graph<int> &graph);

#endif //READCSV_H
