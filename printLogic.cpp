#include "map.h"

/*--COMPLETE------------------------------------------------------------------*/
/*
void Map::printMap(int x1, int x2, int y1, int y2) {
    cout.flush();

    // Set default values for the entire map if no specific range is provided
    if (x1 == -1) x1 = 0;
    if (x2 == -1) x2 = width;
    if (y1 == -1) y1 = 0;
    if (y2 == -1) y2 = height;

    const int cellWidth = 6; // Standardize the width for each cell

    for (int y = y1; y < y2; y++) {

        // PRINT THE TOP ROW BORDER
        for (int j = x1; j < x2; j++) {
            cout << "+";
            for (int k = 0; k < cellWidth; k++) {
                cout << "=";
            }
        }
        cout << "+" << endl;

        // PRINT AN EMPTY ROW FOR PERSONAL DESIGN PURPOSES
        for (int j = x1; j < x2; j++) {
            cout << "|";
            for (int k = 0; k < cellWidth; k++) {
                cout << " ";
            }
        }
        cout << "|" << endl;

        // PRINTING THE ACTUAL ROW WITH INFORMATION
        for (int x = x1; x < x2; x++) {
            cout << "| ";

            if (getCell(x, y) != nullptr) {

                Cell* cell = getCell(x, y);
                ostringstream content;

                // Determine the content to display
                if (cell->getPopulation() > 0) {
                    content << cell->getPopulation();   // Display population
                } else {
                    content << cell->getSymbol();       // Display symbol
                }

                // Calculate padding
                string output = content.str();
                int paddingLeft = (cellWidth - 2 - output.length()) / 2;
                int paddingRight = cellWidth - 2 - output.length() - paddingLeft;

                // Print content with padding
                for (int k = 0; k < paddingLeft; k++) {
                    cout << "  ";
                }

                cout << output;

                for (int k = 0; k < paddingRight; k++) {
                    cout << " ";
                }
            }
            else {
                // Empty cell with uniform spacing
                for (int k = 0; k < cellWidth - 2; k++) {
                    cout << " ";
                }
            }
        }
        cout << "|" << endl;

        // PRINT ANOTHER EMPTY ROW FOR PERSONAL DESIGN PURPOSES
        for (int j = x1; j < x2; j++) {

            cout << "|";
            for (int k = 0; k < cellWidth; k++) {
                cout << " ";
            }
        }
        cout << "|" << endl;
    }

    // PRINT THE BOTTOM ROW BORDER
    for (int j = x1; j < x2; j++) {

        cout << "+";
        for (int k = 0; k < cellWidth; k++) {
            cout << "=";
        }
    }
    cout << "+" << endl;
}
*/
void Map::printMap(int x1, int x2, int y1, int y2) {
    cout.flush();

    // Set default values for the entire map if no specific range is provided
    if (x1 == -1) x1 = 0;
    if (x2 == -1) x2 = width;
    if (y1 == -1) y1 = 0;
    if (y2 == -1) y2 = height;

    const int cellWidth = 6; // Standardize the width for each cell

    for (int y = y1; y < y2; y++) {

        // PRINT THE TOP ROW BORDER
        for (int j = x1; j < x2; j++) {
            cout << "+";
            for (int k = 0; k < cellWidth; k++) cout << "=";
        }
        cout << "+" << endl;

        // PRINT AN EMPTY ROW FOR PERSONAL DESIGN PURPOSES
        for (int j = x1; j < x2; j++) {
            cout << "|";
            for (int k = 0; k < cellWidth; k++) cout << " ";
        }
        cout << "|" << endl;

        // PRINTING THE ROW WITH INFORMATION
        for (int x = x1; x < x2; x++) {
            cout << "|  ";
            Cell* cell = getCell(x, y); // Retrieve the cell at (x, y)
            if (cell != nullptr) {
                ostringstream content;

                // Determine the content to display
                if (cell->getSymbol() == 'R') {
                    // Display residency type and population
                    string residencyType;
                    switch (cell->getResidencyType()) {
                        case Cell::HOUSE: residencyType = "H"; break;
                        case Cell::BUNGALOW: residencyType = "B"; break;
                        case Cell::APARTMENT: residencyType = "A"; break;
                    }
                    content << cell->getPopulation() << "/" << residencyType;
                } else if (cell->getPopulation() > 0) {
                    content << cell->getPopulation(); // Display population
                } else {
                    content << cell->getSymbol(); // Display symbol
                }

                // Calculate padding
                string output = content.str();
                int paddingLeft = (cellWidth - 2 - output.length()) / 2;
                int paddingRight = cellWidth - 2 - output.length() - paddingLeft;

                // Print content with padding
                for (int k = 0; k < paddingLeft; k++) cout << " ";
                cout << output;
                for (int k = 0; k < paddingRight; k++) cout << " ";
            } else {
                // Empty cell with uniform spacing
                for (int k = 0; k < cellWidth - 2; k++) cout << " ";
            }
        }
        cout << "|" << endl;

        // PRINT AN EMPTY ROW BELOW FOR SEPARATION
        for (int j = x1; j < x2; j++) {
            cout << "|";
            for (int k = 0; k < cellWidth; k++) cout << " ";
        }
        cout << "|" << endl;
    }

    // PRINT THE BOTTOM ROW BORDER
    for (int j = x1; j < x2; j++) {
        cout << "+";
        for (int k = 0; k < cellWidth; k++) cout << "=";
    }
    cout << "+" << endl;
}

/*--COMPLETE------------------------------------------------------------------*/

void Map::printState(int x1, int x2, int y1, int y2) {

    cout.flush();

    printMap(x1, x2, y1, y2);

    cout << "Available Workers: " << totalWorkers << endl;
    cout << "Available Goods:   " << totalGoods << endl;

}

/*--COMPLETE------------------------------------------------------------------*/
/*
void Map::printPollutionMap(int x1, int x2, int y1, int y2) {
    cout.flush();

    // Set default values for the entire map if no specific range is provided
    if (x1 == -1) x1 = 0;
    if (x2 == -1) x2 = width;
    if (y1 == -1) y1 = 0;
    if (y2 == -1) y2 = height;

    const int cellWidth = 6; // Standardize the width for each cell

    for (int y = y1; y < y2; y++) {

        // PRINT THE TOP ROW BORDER
        for (int j = x1; j < x2; j++) {
            cout << "+";
            for (int k = 0; k < cellWidth; k++) cout << "=";
        }
        cout << "+" << endl;

        // PRINT AN EMPTY ROW FOR PERSONAL DESIGN PURPOSES
        for (int j = x1; j < x2; j++) {
            cout << "|";
            for (int k = 0; k < cellWidth; k++) cout << " ";
        }
        cout << "|" << endl;

        // PRINTING THE ROW WITH INFORMATION
        for (int x = x1; x < x2; x++) {
            cout << "| ";
            Cell* cell = getCell(x, y); // Retrieve the cell at (x, y)
            if (cell != nullptr) {
                char symbol = cell->getSymbol();
                int pollution = pollutionLevels[y][x]; // Pollution value for the current cell

                // Build cell content with fixed width
                ostringstream content;
                if (pollution > 0) {
                    // Show pollution for non-industrial cells
                    if (symbol != 'I') {
                        content << symbol << "(" << pollution << ")";
                    } else {
                        content << pollution; // Replace symbol with pollution for industrial cells
                    }
                } else {
                    // Show only the symbol if pollution is 0
                    content << symbol;
                }

                string output = content.str();
                int paddingLeft = (cellWidth - 1 - output.length()) / 2;
                int paddingRight = cellWidth - 1 - output.length() - paddingLeft;

                // Add padding for alignment
                for (int k = 0; k < paddingLeft; k++) cout << " ";
                cout << output;
                for (int k = 0; k < paddingRight; k++) cout << " ";
            } else {
                // Empty cell with uniform spacing
                for (int k = 0; k < cellWidth - 1; k++) cout << " ";
            }
        }
        cout << "|" << endl;

        // PRINT AN EMPTY ROW BELOW FOR SEPARATION
        for (int j = x1; j < x2; j++) {
            cout << "|";
            for (int k = 0; k < cellWidth; k++) cout << " ";
        }
        cout << "|" << endl;
    }

    // PRINT THE BOTTOM ROW BORDER
    for (int j = x1; j < x2; j++) {
        cout << "+";
        for (int k = 0; k < cellWidth; k++) cout << "=";
    }
    cout << "+" << endl;

    // Calculate and display total pollution
    getTotalPollution(x1, x2, y1, y2);
    getTotalPopulation(x1, x2, y1, y2);
    cout << "Total Population:  " << totalPopulation << endl;
    cout << "Total Pollution:   " << totalPollution << endl;


    cout << endl;

}
*/

void Map::printPollutionMap(int x1, int x2, int y1, int y2) {
    cout.flush();

    // Set default values for the entire map if no specific range is provided
    if (x1 == -1) x1 = 0;
    if (x2 == -1) x2 = width;
    if (y1 == -1) y1 = 0;
    if (y2 == -1) y2 = height;

    const int cellWidth = 6; // Standardize the width for each cell

    for (int y = y1; y < y2; y++) {

        // PRINT THE TOP ROW BORDER
        for (int j = x1; j < x2; j++) {
            cout << "+";
            for (int k = 0; k < cellWidth; k++) cout << "=";
        }
        cout << "+" << endl;

        // PRINT AN EMPTY ROW FOR PERSONAL DESIGN PURPOSES
        for (int j = x1; j < x2; j++) {
            cout << "|";
            for (int k = 0; k < cellWidth; k++) cout << " ";
        }
        cout << "|" << endl;

        // PRINTING THE ROW WITH INFORMATION
        for (int x = x1; x < x2; x++) {
            cout << "| ";
            Cell* cell = getCell(x, y); // Retrieve the cell at (x, y)
            if (cell != nullptr) {
                ostringstream content;

                int pollution = pollutionLevels[y][x];
                char symbol = cell->getSymbol();

                if (symbol == 'R') {
                    // Display residency type, population, and pollution
                    string residencyType;
                    switch (cell->getResidencyType()) {
                        case Cell::HOUSE: residencyType = "H"; break;
                        case Cell::BUNGALOW: residencyType = "B"; break;
                        case Cell::APARTMENT: residencyType = "A"; break;
                    }
                    if (pollution > 0) {
                        content << cell->getPopulation() << "/" << residencyType << "(" << pollution << ")";
                    } else {
                        content << cell->getPopulation() << "/" << residencyType;
                    }
                } else if (pollution > 0) {
                    // Show pollution for non-residential cells
                    if (symbol != 'I') {
                        content << symbol << "(" << pollution << ")";
                    } else {
                        content << pollution; // Replace symbol with pollution for industrial cells
                    }
                } else {
                    // Show only the symbol if pollution is 0
                    content << symbol;
                }

                string output = content.str();
                int paddingLeft = (cellWidth - 1 - output.length()) / 2;
                int paddingRight = cellWidth - 1 - output.length() - paddingLeft;

                // Add padding for alignment
                for (int k = 0; k < paddingLeft; k++) cout << " ";
                cout << output;
                for (int k = 0; k < paddingRight; k++) cout << " ";
            } else {
                // Empty cell with uniform spacing
                for (int k = 0; k < cellWidth - 1; k++) cout << " ";
            }
        }
        cout << "|" << endl;

        // PRINT AN EMPTY ROW BELOW FOR SEPARATION
        for (int j = x1; j < x2; j++) {
            cout << "|";
            for (int k = 0; k < cellWidth; k++) cout << " ";
        }
        cout << "|" << endl;
    }

    // PRINT THE BOTTOM ROW BORDER
    for (int j = x1; j < x2; j++) {
        cout << "+";
        for (int k = 0; k < cellWidth; k++) cout << "=";
    }
    cout << "+" << endl;

    // Display total pollution and population
    getTotalPollution(x1, x2, y1, y2);
    cout << "Total Pollution:   " << totalPollution << endl;
    cout << "Total Population:  " << totalPopulation << endl;

}

////////////////////////////////////////////////////////////////////////////////