#include "map.h"

/*--COMPLETE------------------------------------------------------------------*/

vector<Cell*> Map::getSortedCells() {
    vector<Cell*> allCells;

    // Combine all cell types into a single vector with type prioritization
    allCells.insert(allCells.end(), allCommerce.begin(), allCommerce.end());
    allCells.insert(allCells.end(), allIndustries.begin(), allIndustries.end());
    allCells.insert(allCells.end(), allResidents.begin(), allResidents.end());

    // Sort all cells based on the global priority rules
    sort(allCells.begin(), allCells.end(), [this](Cell* a, Cell* b) {
        // Rule 1: Commercial > Industrial > Residential
        int typeA = (a->getSymbol() == 'C') ? 0 : (a->getSymbol() == 'I') ? 1 : 2;
        int typeB = (b->getSymbol() == 'C') ? 0 : (b->getSymbol() == 'I') ? 1 : 2;
        if (typeA != typeB) return typeA < typeB;

        // Rule 2: Larger population grows first
        if (a->getPopulation() != b->getPopulation())
            return a->getPopulation() > b->getPopulation();

        // Rule 3: Higher capacity-to-population ratio grows first
        if (a->getSymbol() == 'R' && b->getSymbol() == 'R') {
            double ratioA = static_cast<double>(a->getPopulation()) / a->canIncreasePopulation();
            double ratioB = static_cast<double>(b->getPopulation()) / b->canIncreasePopulation();
            if (ratioA != ratioB) return ratioA < ratioB;
        }

        // Rule 4: Greater total adjacent population grows first
        int adjPopA = this->totalAdjPopulation(a);
        int adjPopB = this->totalAdjPopulation(b);
        if (adjPopA != adjPopB)
            return adjPopA > adjPopB;

        // Rule 5: Smaller Y-coordinates first
        if (a->getY() != b->getY())
            return a->getY() < b->getY();

        // Rule 6: Smaller X-coordinates first
        return a->getX() < b->getX();
    });

    return allCells;
}

/*--COMPLETE------------------------------------------------------------------*/

vector<vector<Cell*> > Map::setCellOrder() {
    vector<Cell*> sortedCells = getSortedCells();

    vector<vector<Cell*>> currCells(3); // 0: Commercial, 1: Industrial, 2: Residential
    for (Cell* cell : sortedCells) {
        if (cell->getSymbol() == 'C') {
            currCells[0].push_back(cell);
        }
        else if (cell->getSymbol() == 'I') {
            currCells[1].push_back(cell);
        }
        else if (cell->getSymbol() == 'R') {
            currCells[2].push_back(cell);
        }
    }

    return currCells;
}

/*--COMPLETE------------------------------------------------------------------*/

void Map::updatePreviousPopulation() {

    // Ensure previousPopulation is properly initialized with the correct dimensions
    previousPopulation = vector<vector<int>>(height, vector<int>(width, 0));

    // Get the ordered cells grouped by type
    vector<vector<Cell*>> orderedCells = setCellOrder();

    // Iterate over all cell groups (0: Commercial, 1: Industrial, 2: Residential)
    for (const auto& cellGroup : orderedCells) {
        for (Cell* cell : cellGroup) {
            if (cell != nullptr) { // Ensure the cell is not null

                int x = cell->getX();
                int y = cell->getY();

                if (x >= 0 && x < width && y >= 0 && y < height) { // Bounds check
                    previousPopulation[y][x] = cell->getPopulation();
                }
                else {
                    cerr << "Warning: Cell at (" << x << ", " << y << ") is out of bounds.\n";
                }
            }
        }
    }
}

/*--COMPLETE------------------------------------------------------------------*/

bool Map::adjPowerline(Cell* cell) {

    if (!cell) {
        return false;
    }

    const vector<Cell*>& adjacent = this->getAdjCells(cell);

    for (const Cell* adjCell : adjacent) {
        if (adjCell && (adjCell->getSymbol() == 'T' ||
                        adjCell->getSymbol() == '#')) {
            return true;
        }
    }

    return false;
}

/*--COMPLETE------------------------------------------------------------------*/

int Map::totalAdjPopulation(Cell* cell) {

    if (!cell) {
        return 0;
    }

    int adjacentPopulation = 0;

    const vector<Cell*>& adjacent = this->getAdjCells(cell);

    for (const Cell* adjCell : adjacent) {
        if (adjCell != nullptr) { // Avoid nullptr dereference
            adjacentPopulation += adjCell->getPopulation();
        }
    }

    return adjacentPopulation;
}

/*--COMPLETE------------------------------------------------------------------*/

vector<Cell*> Map::getAdjCells(Cell* cell) {

    if (!cell) return {}; // Return an empty vector if the cell is null

    vector<Cell*> adjacent;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue; // Skip the current cell

            int adjX = cell->getX() + dx;
            int adjY = cell->getY() + dy;

            if (adjX >= 0 && adjX < width && adjY >= 0 && adjY < height) {
                Cell* adjCell = allCells[adjY][adjX];
                if (adjCell != nullptr) {
                    adjacent.push_back(adjCell);
                }
            }
        }
    }

    return adjacent;
}

////////////////////////////////////////////////////////////////////////////////