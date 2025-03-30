#include "InteractiveInput.h"
#include <iostream>
using namespace std;

void InterInputBestRoute(std::string &mode, int &source, int &destination){
  cout << "Enter Mode: ";
  cin >> mode;
  if (mode != "driving" && mode != "Driving"){
    cout << "Invalid mode!";
  }
  cout << "Enter Source: ";
  cin >> source;

  cout << "Enter Destination: ";
  cin >> destination;
}