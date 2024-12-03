#include "map.h"

/*--COMEBACK------------------------------------------------------------------*/
/*
bool Map::isStable() {

    for (int i = 0; i < height; ++i) {

        for (int j = 0; j < width; ++j) {

            // Ensure the cell exists and is not null
            if (i >= allCells.size() ||
                j >= allCells[i].size() ||
                allCells[i][j] == nullptr) {
                continue; // Skip invalid or uninitialized cells
            }

            // Compare current population with the previous state
            if (allCells[i][j] != nullptr &&
                allCells[i][j]->getPopulation() != previousPopulation[i][j]) {
                return false;
            }
        }
    }
    return true; // Return false if changes were found
}
 */
bool Map::isStable() {

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i >= allCells.size() ||
                j >= allCells[i].size() ||
                    allCells[i][j] == nullptr) {
                continue; // Skip invalid or uninitialized cells
            }

            Cell* cell = allCells[i][j];
            if (cell->getSymbol() == 'R' &&
                cell->getPopulation() != previousPopulation[i][j] &&
                cell->canIncreasePopulation()) {
                return false; // Unstable if population changed and can grow further
            }
        }
    }
    return true; // Stable if no changes detected
}

/*--COMPLETE------------------------------------------------------------------*/

bool Map::simulateGrowth() {

    // Update previous population data for stability check
    updatePreviousPopulation();

    // Initialize and order the cells based on type
    // Assuming 0: Commercial, 1: Industrial, 2: Residential
    vector<vector<Cell*> > currCells = setCellOrder();

    // Process commercial cells
    for (Cell* cell : currCells[0]) {
        if (cell->getSymbol() == 'C') {
            applyCommercialGrowthRules(cell);
        }
    }

    // Process industrial cells
    for (Cell* cell : currCells[1]) {
        if (cell->getSymbol() == 'I') {
            applyIndustrialGrowthRules(cell);
        }
    }

    // Process residential cells
    for (Cell* cell : currCells[2]) {
        if (cell->getSymbol() == 'R') {
            applyResidentialGrowthRules(cell);
        }
    }

    // Check for stability (if no further changes in map state)
    if (isStable()) {
        return true;
    }

    return false;

}


/*--COMPLETE------------------------------------------------------------------*/

void Map::applyResidentialGrowthRules(Cell* cell) {
    int adjacentPop = this->totalAdjPopulation(cell);
    int population = cell->getPopulation();

    // Growth conditions
    if ((population == 0 && this->adjPowerline(cell)) ||
        (population == 0 && adjacentPop >= 1) ||
        (population == 1 && adjacentPop >= 2) ||
        (population == 2 && adjacentPop >= 4) ||
        (population == 3 && adjacentPop >= 6) ||
        (population == 4 && adjacentPop >= 8)) {

        // Check if the population can be increased
        if (cell->canIncreasePopulation()) {
            cell->incPopulation();
            totalWorkers++;
        }
    }
}

/*--COMPLETE------------------------------------------------------------------*/

void Map::applyCommercialGrowthRules(Cell* cell) {
    int adjacentPop = this->totalAdjPopulation(cell);
    int population = cell->getPopulation();

    // Growth conditions
    if ((population == 0 && this->adjPowerline(cell) && totalWorkers >= 1 && totalGoods >= 1) ||
        (population == 0 && adjacentPop >= 1 && totalWorkers >= 1 && totalGoods >= 1) ||
        (population == 1 && adjacentPop >= 2 && totalWorkers >= 1 && totalGoods >= 1)) {
        cell->incPopulation();
        totalWorkers--;
        totalGoods--;
    }
}

/*--COMPLETE------------------------------------------------------------------*/

void Map::applyIndustrialGrowthRules(Cell* cell) {
    int adjacentPop = this->totalAdjPopulation(cell);
    int population = cell->getPopulation();

    // Growth conditions
    if ((population == 0 && this->adjPowerline(cell) && totalWorkers >= 2) ||
        (population == 0 && adjacentPop >= 1 && totalWorkers >= 2) ||
        (population == 1 && adjacentPop >= 2 && totalWorkers >= 2) ||
        (population == 2 && adjacentPop >= 4 && totalWorkers >= 2)) {
        cell->incPopulation();
        totalWorkers -= 2;
        totalGoods++;
    }
}

////////////////////////////////////////////////////////////////////////////////