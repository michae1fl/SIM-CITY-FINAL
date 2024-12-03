#include "configure.h"


bool setMaps(int& refresh, int& limit, Map& map) {

    string filename;

    //OPENING THE CONFIGURATION FILE
    cout << "Please enter configuration filename: ";
    cin >> filename;

    ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        return false;
    }

    string line;

    //USE A COUNTER TO DETERMINE WHICH LINE OF THE FILE WE ARE ON
    int counter = 0;

    while (getline(file, line)) {

        size_t colonIndex = line.find(':');
        if (colonIndex == string::npos) {
            cerr << "Invalid format in configuration file." << endl;
            return false;
        }

        if (counter == 0) {
            filename = line.substr(colonIndex + 1);
        }
        if (counter == 1) {
            string value = line.substr(colonIndex + 1);
            limit = stoi(value);
        }
        if (counter == 2) {
            string value = line.substr(colonIndex + 1);
            refresh = stoi(value);
        }

        counter ++;

    }

    file.close();

    //OPENING THE REGION FILE
    file.open(filename);

    if (!file.is_open()) {
        return false;
    }

    int YValue = 0;

    while (getline(file, line)) {

        stringstream ss(line);
        string cellData;
        char symbol;
        int XValue = 0;

        while (getline(ss, cellData, ',')) {

            if (cellData.empty()) {
                XValue ++;
            }
            else {

                symbol = cellData[0];

                map.addCell(XValue, YValue, symbol);

                XValue ++;

            }

        }

        map.setWidth(max(map.getWidth(), XValue));
        YValue ++;

    }

    map.setHeight(YValue);
    file.close();

    return true;

}