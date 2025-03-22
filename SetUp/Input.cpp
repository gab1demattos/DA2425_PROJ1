#include "Input.h"

bool isModeDriving(const string& mode) {
    string res;
    for (const char c : mode)
        res += static_cast<char>(tolower(c));
    return res == "driving";
}

bool InputBestRoute(string & mode, int & source, int & destination) {
    // Read from file
    ifstream inputFile("Input/input.txt");
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
