# Environmentally Friendly Route Planning

This repository contains a C++ project implementing several route-planning algorithms (best route, restricted route, and environmentally friendly route variants). The program reads road network and location data, computes routes according to user-selected criteria, and supports both interactive and batch input modes.

## Features

- Compute shortest and environmentally-friendly routes
- Restricted/independent route planning modes
- Interactive and batch input options
- Uses CSV input data located in `Data/` and example inputs in `Input/`

## Build (Linux)

1. Create a build directory and run CMake:

```bash
mkdir -p build
cd build
cmake ..
make
```

2. The executable will be produced as `route_planner` inside the build folder (or `cmake-build-debug/` when using an IDE build).

## Run

- Example (batch input):

```bash
./route_planner < ../Input/inputBestRoute.txt
```

- Example (interactive):

```bash
./route_planner
# then follow the on-screen menu prompts
```

## Data

- Place CSV files under the `Data/` directory. This repo already contains `Distances.csv`, `Locations.csv`, and Porto variants for testing.
- Example input scenarios are in the `Input/` directory:
  - `inputBestRoute.txt`
  - `inputEnvironmentalRoute.txt`
  - `inputRestrictedRoute.txt`

## Project Structure (high level)

- `Main/` — top-level entry points
- `SetUp/` — initial configuration and `Main.cpp`
- `DataStructures/` — graph and supporting data structures
- `ReadData/` — CSV and input parsing
- `Routes/` — route planning algorithm implementations
- `InputOutput/` and `Menu/` — UI and IO handling
- `docs/` — generated Doxygen documentation

## Documentation

Generate or view Doxygen documentation (if installed) with the provided `Doxyfile`; pre-generated HTML is available under `docs/html/` in this repository.

## Notes & Next Steps

- This is a university assignment — adjust data paths and input files as needed.
- To add more examples, place them in `Input/` and run the executable with redirection.

## Development Team

This project was developed by:

- [Francisca Portugal](https://github.com/franpts2)
- [Gabriela de Mattos](https://github.com/gab1demattos)
- [Maria Luiza Vieira](https://github.com/maluviieira)

## Course Information

Developed for the BD (Databases) course at FEUP (Faculty of Engineering, University of Porto).
