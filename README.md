# Sim City Project

## Project Overview

Sim City is a C++ simulation program that models the growth of a city over time. 
The program simulates residential, commercial, and industrial zones, each with 
unique growth rules influenced by resources (workers and goods) and pollution 
levels. The city layout and initial conditions are defined by a configuration 
file, and the simulation progresses through time steps until reaching a stable 
state or specified time limit.

Key enhancements in this version include dynamic residency types for residential
zones, refined pollution management using a Breadth-First Search (BFS) algorithm, 
and improved map visualization with residency details and pollution levels.

## Project Structure

The code is organized into several main components:

- **main.cpp**: Manages program initialization, loads configuration files, and
  initiates the simulation loop.
- **configure.cpp** / **configure.h**: Handles parsing and validating configuration
  and layout files.
- **cell.cpp** / **cell.h**: Defines the Cell class, representing individual map
  cells with enhanced features like residency types and population caps.
- **map.cpp** / **map.h**: Defines the Map class, which handles city layout, zone
  management, simulation of growth, and pollution spread.
  - **growthLogic.cpp**: Implements growth rules for different zone types.
  - **helperFunctions.cpp**: Provides utility functions to manage cell
    relationships and attributes.
  - **printLogic.cpp**: Manages visualization of the map state and pollution levels.

## Key Functionalities

### New and Updated Features
1. **Residential Zone Enhancements**:
   - Residential cells are assigned a random residency type (House, Bungalow, Apartment)
     with varying population caps.
   - Growth rules consider the residency type, improving simulation realism.
2. **Pollution Management**:
   - BFS algorithm efficiently spreads pollution outward from industrial zones, reducing
     redundant calculations.
   - Pollution levels are now displayed alongside other map details.
3. **Improved Visualization**:
   - Map output includes details like population/residency type for residential cells and
     pollution levels for all cells.
   - Users can analyze specific rectangular regions for detailed population and pollution
     statistics.
4. **Dynamic Growth Rules**:
   - Growth for residential, commercial, and industrial zones depends on adjacency,
     resources, and powerline connectivity.
   - Zones grow hierarchically based on type, population, and adjacency metrics.

### Exisiting Features

1. **Initialization**: 
   - Loads configuration and region layout from a CSV file specified by the user.
   - Initializes the map with residential (`R`), commercial (`C`), and industrial 
   (`I`) zones, powerlines and roads based on the configuration.

2. **Simulation Loop**:
  - Handles zone growth, updates resources (workers and goods), and checks
    stability at each time step.
  - Outputs the map state periodically based on user-defined refresh rates.

3. **Final Analysis**:
   - Computes and displays total population, workers, goods, and pollution.
   - Allows users to analyze specific regions of the map.

## Compilation and Setup

### Prerequisites

- **C++ compiler** (e.g., g++, clang++)
- **Standard Libraries** (no additional libraries are required)

### Compilation

To compile the program, use the following command in the terminal:

```bash
g++ main.cpp map.cpp cell.cpp configure.cpp growthLogic.cpp helperFunctions.cpp printLogic.cpp -o simcity
```
This will create an executable named `simcity`.

### Running the Program
To run the simulation:

```bash
./simcity
```
After starting the program, you’ll be prompted to enter the configuration file name.

## Configuration File Format

The configuration file should follow this structure:

1. **First Line**: Path to the CSV file defining the city’s layout.
2. **Second Line**: Maximum number of time steps for the simulation.
3. **Third Line**: Refresh rate to control how often the map’s state is output.

The CSV file should contain characters for each cell type:

- **R**: Residential zone
- **C**: Commercial zone
- **I**: Industrial zone
- **-**: Road
- **T**: Powerline
- **#**: Powerline over a road
- **P**: Power plant

## Usage Instructions

1. Run the program and provide the configuration file name when prompted.
2. The program will initialize the city map and display the initial state.
3. The simulation will proceed in time steps, updating population, resources, 
and pollution.
4. Results, including available workers, goods, and pollution levels, are 
displayed based on the refresh rate.
5. At the end of the simulation, the final state of the city is printed, 
including:
   - The total population for each zone type.
   - Total pollution levels in the city.
   - Option to analyze a specified area for detailed pollution and population data.

## Example Output

```plaintext
Please enter configuration filename: config1.txt
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   I  |   I  |   I  |   -  |   C  |   C  |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   -  |   -  |   -  |   -  |   -  |   -  |   #  |   -  |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|      |      |   -  |  R/H |  R/H |  R/A |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
Time Limit:   20
Refresh Rate: 1

+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   I  |   I  |   I  |   -  |   C  |   C  |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   -  |   -  |   -  |   -  |   -  |   -  |   #  |   -  |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|      |      |   -  |  1/H |  1/H |  2/A |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
Available Workers: X
Available Goods:   Y

FINAL STATE
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   I  |   I  |   I  |   -  |   C  |   C  |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   -  |   -  |   -  |   -  |   -  |   -  |   #  |   -  |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|      |      |   -  |  5/H |  5/H |  5/A |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
Available Workers: X
Available Goods:   Y
Total Population:  Z

FINAL POLLUTION MAP
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   I  |   I  |   I  |   -  | C(1) |   C  |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   -  |   -  |   -  |   -  |   -  |   -  |   #  |   -  |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|      |      |   -  |  5/H |  5/H |  2/A |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
Total Pollution:   X
Total Population:  Y

Enter the specific region you would like to analyze: X1 X2 Y1 Y2
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   I  |   I  |   I  |   -  |   C  |   C  |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   -  |   -  |   -  |   -  |   -  |   -  |   #  |   -  |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|      |      |   -  |  5/H |  5/H |  2/A |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   I  |   I  |   I  |   -  | C(1) |   C  |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|   -  |   -  |   -  |   -  |   -  |   -  |   #  |   -  |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
|      |      |      |      |      |      |      |      |
|      |      |   -  |  5/H |  5/H |  2/A |   T  |      |
|      |      |      |      |      |      |      |      |
+======+======+======+======+======+======+======+======+
Total Pollution:   1
Total Population:  39
```

## Notes

- Ensure that the configuration file and CSV layout file are correctly formatted
 to avoid parsing errors.
- The program is configured to halt if the city reaches a stable state before 
the time limit.
