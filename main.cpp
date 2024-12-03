/*
 * In this new implementation of my SIM CITY Implementation I incorporated a BFS
 * algorithm for the pollution spread to reduce iteration over the map.
 *
 * Using a BFS algorithm to spread pollution outward in waves, ensuring each
 * cell is visited only once and reducing redundant calculations.
 */

#include "configure.h"
#include "map.h"

/*--COMPLETE------------------------------------------------------------------*/

int main() {

    Map map;
    string filename;
    int refreshRate = 0;
    int timeLimit = 0;

    // Prompt user to input the simulation configuration file
    // Initialize the Map object with the region file
    if (!setMaps(refreshRate, timeLimit, map)) {
        cerr << "Error: Failed to load configuration from file.\n";
        return 1;
    }

    // Output the initial state of the region (time step 0)
    map.printMap();

    cout << "Time Limit:   " << timeLimit << endl;
    cout << "Refresh Rate: " << refreshRate << endl;
    cout << endl;

    // Initialize other variables (workers, goods, pollution, etc.)
    int timeStep = 0;

    // Begin simulation loop
    while (timeStep < timeLimit) {

        // Simulate the growth of residential, commercial, and industrial zones
        // Update the number of available workers and goods based on map state


        if(map.simulateGrowth()) {
            break;
        }

        // Print the current time step, workers, goods at the refresh rate
        if (timeStep % refreshRate == 0) {
            map.printState();
        }

        // Increment the time step
        timeStep ++;
    }
    cout << endl;

    // Output the final region state
    cout << "FINAL STATE" << endl;
    map.printState();
    cout << "Total Population:  " << map.getTotalPopulation() << endl;

    //Calculate the final Pollution Map
    map.spreadPollution();

    // Output the final Pollution Map
    map.printPollutionMap();

    // Ask the user for a rectangular area to analyze
    int x1, x2, y1, y2;
    cout << "Enter the specific region you would like to analyze: ";
    cin >> x1 >> x2 >> y1 >> y2;

    map.printMap(x1, x2, y1, y2);
    map.printPollutionMap(x1, x2, y1, y2);


    return 0;
}
