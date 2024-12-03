#ifndef SIM_CITY_FINAL_CELL_H
#define SIM_CITY_FINAL_CELL_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

using namespace std;

class Map;

class Cell {
    public:

        //NEW FEATURE
        enum ResidencyType { HOUSE, BUNGALOW, APARTMENT }; // Define residency types

        // Constructor
        Cell(int x = -1, int y = -1, char c = 'U');

        // Setter functions
        void setX(int x);
        void setY(int y);
        void setSymbol(char symbol);

        // Getter functions
        int  getX() const;
        int  getY() const;
        char getSymbol() const;
        int  getPopulation() const;

        // Increment functions
        void incPopulation();

        //NEW FEATURES
        void setResidencyType(ResidencyType type);
        ResidencyType getResidencyType() const;
        bool canIncreasePopulation() const;

private:
        int x, y;
        char symbol;
        int population;

        //NEW FEATURES
        ResidencyType residencyType;    // Residency-specific attributes
        int populationCap;              // Maximum population based on residency type

        void updatePopulationCap();                 // Helper to set population cap
        ResidencyType assignRandomResidencyType();  // Random residency type assignment
};

#endif //SIM_CITY_FINAL_CELL_H
