#include "map.h"

///- MAP CLASS -////////////////////////////////////////////////////////////////

/*--COMPLETE------------------------------------------------------------------*/

Map::Map() {
    width = 0;
    height = 0;
    totalPollution = 0;
    totalPopulation = 0;
    totalGoods = 0;
    totalWorkers = 0;
}

/*--COMPLETE------------------------------------------------------------------*/

Map::~Map() {
    for (auto& row : allCells) {
        for (auto& cell : row) {
            delete cell;
        }
    }
}

/*--COMPLETE------------------------------------------------------------------*/

void Map::addCell(int x, int y, char symbol) {

    while (y >= allCells.size()) {
        allCells.push_back(vector<Cell*>());
    }

    while (x >= allCells[y].size()) {
        allCells[y].push_back(nullptr);
    }

    Cell* newCell = nullptr;
    if (symbol == 'C') {
        Cell* commercialCell = new Cell(x, y, symbol);
        allCommerce.push_back(commercialCell);
        newCell = commercialCell;
    }
    else if (symbol == 'R') {
        Cell* residentialCell = new Cell(x, y, symbol);
        allResidents.push_back(residentialCell);
        newCell = residentialCell;
    }
    else if (symbol == 'I') {
        Cell* industrialCell = new Cell(x, y, symbol);
        allIndustries.push_back(industrialCell);
        newCell = industrialCell;
    }
    else {
        newCell = new Cell(x, y, symbol);
    }

    allCells[y][x] = newCell;
}

/*--COMPLETE------------------------------------------------------------------*/

Cell* Map::getCell(int x, int y) {

    if (x >= 0 && x <= width && y >= 0 && y <= height) {
        return allCells[y][x];
    }

    return nullptr;
}

/*--COMPLETE------------------------------------------------------------------*/

void Map::setWidth(int value) {
    width = value;
}

/*--COMPLETE------------------------------------------------------------------*/

void Map::setHeight(int value) {
    height = value;
}

/*--COMPLETE------------------------------------------------------------------*/

int Map::getWidth() {
    return width;
}

/*--COMPLETE------------------------------------------------------------------*/

int Map::getHeight() {
    return height;
}

/*--COMPLETE------------------------------------------------------------------*/
/*
void Map::spreadPollution() {
    // Initialize the pollution map to zero for each cell
    pollutionLevels = vector<vector<int>>(height, vector<int>(width, 0));

    // Loop through all industrial cells
    for (Cell* indCell : allIndustries) {
        int x = indCell->getX();
        int y = indCell->getY();
        int pollutionAmount = indCell->getPopulation();

        // Apply pollution to the source cell
        pollutionLevels[y][x] = pollutionAmount; // Set pollution level for the industrial cell

        // Spread pollution outward only one block away
        vector<pair<int, int>> directions = {
                {0, 1}, {1, 0}, {0, -1}, {-1, 0}, // Cardinal directions
                {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // Diagonal directions
        };

        for (auto [dx, dy] : directions) {
            int adjX = x + dx;
            int adjY = y + dy;

            // Check bounds
            if (adjX >= 0 && adjX < width && adjY >= 0 && adjY < height) {
                Cell* adjCell = getCell(adjX, adjY);

                // Skip industrial cells
                if (adjCell && adjCell->getSymbol() == 'I') continue;

                // Set pollution to one less than the source
                pollutionLevels[adjY][adjX] = max(pollutionLevels[adjY][adjX], pollutionAmount - 1);
            }
        }
    }
}
*/
void Map::spreadPollution() {
    // Initialize pollution map and visited status
    pollutionLevels = vector<vector<int>>(height, vector<int>(width, 0));
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    queue<pair<pair<int, int>, int>> pollutionQueue; // { {x, y}, pollution level }

    // Enqueue all industrial cells
    for (Cell* indCell : allIndustries) {
        int x = indCell->getX();
        int y = indCell->getY();
        int pollution = indCell->getPopulation();
        pollutionQueue.push({{x, y}, pollution});
        pollutionLevels[y][x] = pollution;
        visited[y][x] = true;
    }

    // Define movement directions (8-neighborhood)
    vector<pair<int, int>> directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0},
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    // BFS for pollution spreading
    while (!pollutionQueue.empty()) {
        auto [coords, level] = pollutionQueue.front();
        pollutionQueue.pop();
        int x = coords.first, y = coords.second;

        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;

            // Check bounds and avoid revisiting cells
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && !visited[ny][nx]) {
                Cell* adjCell = getCell(nx, ny);
                if (adjCell && adjCell->getSymbol() != 'I') { // Skip industrial cells
                    int newPollution = max(level - 1, 0);
                    pollutionLevels[ny][nx] = max(pollutionLevels[ny][nx], newPollution);
                    if (newPollution > 0) {
                        pollutionQueue.push({{nx, ny}, newPollution});
                    }
                }
                visited[ny][nx] = true;
            }
        }
    }
}


/*--COMPLETE------------------------------------------------------------------*/

int Map::getTotalPollution(int x1, int x2, int y1, int y2) {

    // Ensure to reinitialize pollution
    totalPollution = 0;

    // Set default values for the entire map if no specific range is provided
    if (x1 == -1) x1 = 0;
    if (x2 == -1) x2 = width;
    if (y1 == -1) y1 = 0;
    if (y2 == -1) y2 = height;

    for (int y = y1; y < y2; y ++) {

        for (int x = x1; x < x2; x++) {
            totalPollution += pollutionLevels[y][x];
        }
    }

    return totalPollution;
}

/*--COMPLETE------------------------------------------------------------------*/

int Map::getTotalPopulation(int x1, int x2, int y1, int y2) {

    totalPopulation = 0;

    // Set default values for the entire map if no specific range is provided
    if (x1 == -1) x1 = 0;
    if (x2 == -1) x2 = width;
    if (y1 == -1) y1 = 0;
    if (y2 == -1) y2 = height;


    // Iterate only through residential cells
    for (Cell* resCell : allResidents) {
        int cellX = resCell->getX();
        int cellY = resCell->getY();

        // Check if the cell is within the given range
        if (cellX >= x1 && cellX < x2 && cellY >= y1 && cellY < y2) {
            totalPopulation += resCell->getPopulation();
        }
    }

    return totalPopulation;
}

////////////////////////////////////////////////////////////////////////////////