#include <iostream>
#include <string>

#include "./../hpp/clothes.hpp"

vector<Clothes> createCloset(const string filePath) {
    /*
    Purpose: Create a vector representation of the Clothes objects in the user's closet file
    References: C++ documentation on std::stod function
    */
    bool allOneType = true;
    vector<Clothes> closet;
    int lastType = -1;
    ifstream closetFile(filePath);

    if (!closetFile.good()) {
        throw(FILE_BAD_MESSAGE);
    }

    int ID;
    string graphics;
    int weather;
    int type;
    double hue;
    double sat;
    double light;

    string inputLine;
    string field;

    getline(closetFile, inputLine); // Skip the header line

    while(!closetFile.eof() && getline(closetFile, inputLine)) {
        stringstream parser(inputLine);
        getline(parser, field, ',');
        ID = stoi(field);
        getline(parser, field, ',');
        graphics = field;
        getline(parser, field, ',');
        weather = stoi(field);
        getline(parser, field, ',');
        type = stoi(field);
        if (lastType == -1) {
            lastType = type;
        }
        if (type != lastType) {
            allOneType = false;
        }
        getline(parser, field, ',');
        hue = stod(field);
        getline(parser, field, ',');
        sat = stod(field);
        getline(parser, field, '\n');
        light = stod(field);
        closet.push_back(Clothes(graphics, weather, type, hue, sat, light, ID));
    }
    if (allOneType) {
        throw(type);
    }
    return closet;
}

int main() {
    /*
        Notes: 
            MatchingClothes will get stuck in an infinite loop if the closet contains only a single type of clothing.
            For example, if a person has only type=1 clothes, then the loop will continue to expand, and will not find any matches,
            since it only matches for type=0 clothes. 

            Future feature expansion includes deletion. Removing clothes from the CSV file is beyond the scope of this project, however,
            it is a feature that we will try to include later on in the development process.

            Unique error: If the closet file has no clothes, but has an extra line (besides the header), then the program will not work correctly.

    */
    cout << "Main program." << endl;
    string g = "Hello";

    try {
        Clothes h("None", 1,1,145,.71,.39);
        h.addToCloset();
        vector<Clothes> cloth;
        cloth = createCloset(CLOSET_PATH);
        double* colorPaletteHues = tetradicPaletteGenerator(h.getHue());
        vector<Clothes> matches = h.matchingClothes(cloth, colorPaletteHues);
        cout << "Matching Clothes:" << endl;
        for(int i = 0; i < matches.size(); i++) {
            RGBColor* r1 = convertHSLtoRGB(matches[i]);
            cout << *r1;

        }
    }
    catch(int m) {
        if(m == 1) {
            cout << "Sorry, your closet currently only contains tops. We cannot create outfits without bottoms." << endl;
        } else {
            cout << "Sorry, your closet currently only contains bottoms. We cannot create outfits without tops." << endl;
        }
    }
    catch(string msg) {
        cout << msg << endl;
    }
    return 0;
}