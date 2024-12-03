#ifndef SIM_CITY_FINAL_MAP_H
#define SIM_CITY_FINAL_MAP_H

#include "cell.h"
#include <queue>

class Map {

public:

    //MAP.CPP
    Map();
    ~Map();
    int getWidth();
    int getHeight();
    void setWidth(int);
    void setHeight(int);
    void spreadPollution();
    Cell* getCell(int x, int y);
    void addCell(int x, int y, char symbol);
    int getTotalPollution(int x1=-1, int x2=-1, int y1=-1, int y2=-1);
    int getTotalPopulation(int x1=-1, int x2=-1, int y1=-1, int y2=-1);

    //GROWTHLOGIC.CPP
    bool isStable();
    bool simulateGrowth();
    void applyResidentialGrowthRules(Cell* cell);
    void applyCommercialGrowthRules(Cell* cell);
    void applyIndustrialGrowthRules(Cell* cell);

    //PTINTLOGIC.CPP
    void printMap(int x1=-1, int x2=-1, int y1=-1, int y2=-1);
    void printState(int x1=-1, int x2=-1, int y1=-1, int y2=-1);
    void printPollutionMap(int x1=-1, int x2=-1, int y1=-1, int y2=-1);

private:
    int width;
    int height;
    int totalPollution;
    int totalPopulation;
    int totalGoods;
    int totalWorkers;

    vector<vector<Cell*> > allCells;
    vector<Cell*> allResidents;
    vector<Cell*> allIndustries;
    vector<Cell*> allCommerce;
    vector<vector<int> > pollutionLevels;
    vector<vector<int> > previousPopulation;

    //HELPERFUNCTIONS.CPP
    vector<Cell*> getSortedCells();
    vector<vector<Cell*> > setCellOrder();
    vector<Cell*> getAdjCells(Cell* cell);
    bool adjPowerline(Cell* cell);
    void updatePreviousPopulation();
    int totalAdjPopulation(Cell* cell);

};

#endif //SIM_CITY_FINAL_MAP_H
