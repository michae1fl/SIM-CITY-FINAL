#include "cell.h"

///- CELL CLASS -///////////////////////////////////////////////////////////////

//-PRIVATE FUNCTIONS-///////////////////////////////////////////////////////////

/*--COMPLETE------------------------------------------------------------------*/

Cell::ResidencyType Cell::assignRandomResidencyType() {
    static random_device rd;    // Seed for random number generator
    static mt19937 gen(rd());   // Mersenne Twister engine
    static uniform_int_distribution<> dist(0, 2); // Range for 3 residency types

    return static_cast<ResidencyType>(dist(gen)); // Convert random int to ResidencyType
}

/*--COMPLETE------------------------------------------------------------------*/

void Cell::updatePopulationCap() {
    switch (residencyType) {
        case HOUSE:
            populationCap = 5;
            break;
        case BUNGALOW:
            populationCap = 2;
            break;
        case APARTMENT:
            populationCap = 8;
            break;
    }
}

//-PUBLIC FUNCTIONS-////////////////////////////////////////////////////////////

/*--COMPLETE------------------------------------------------------------------*/

Cell::Cell(int x, int y, char c)
        : x(x), y(y), symbol(c), population(0) {
    if (c == 'R') { // Only assign residency type for residential cells
        residencyType = assignRandomResidencyType();
        updatePopulationCap();
    } else {
        residencyType = HOUSE; // Default for non-residential
        populationCap = 0;     // Non-residential cells don't have a population cap
    }
}

/*--COMPLETE------------------------------------------------------------------*/

void Cell::setX(int x) {
    this->x = x;
}

/*--COMPLETE------------------------------------------------------------------*/

void Cell::setY(int y) {
    this->y = y;
}

/*--COMPLETE------------------------------------------------------------------*/

void Cell::setSymbol(char symbol) {
    this->symbol = symbol;
}

/*--COMPLETE------------------------------------------------------------------*/

void Cell::setResidencyType(ResidencyType type) {
    residencyType = type;
    updatePopulationCap();
}

/*--COMPLETE------------------------------------------------------------------*/

int Cell::getX() const {
    return x;
}

/*--COMPLETE------------------------------------------------------------------*/

int Cell::getY() const {
    return y;
}

/*--COMPLETE------------------------------------------------------------------*/

char Cell::getSymbol() const {
    return symbol;
}

/*--COMPLETE------------------------------------------------------------------*/

int Cell::getPopulation() const {
    return population;
}

/*--COMPLETE------------------------------------------------------------------*/

Cell::ResidencyType Cell::getResidencyType() const {
    return residencyType;
}

/*--COMPLETE------------------------------------------------------------------*/

void Cell::incPopulation() {
    population ++;
}

/*--COMPLETE------------------------------------------------------------------*/

bool Cell::canIncreasePopulation() const {
    return population < populationCap;
}


////////////////////////////////////////////////////////////////////////////////