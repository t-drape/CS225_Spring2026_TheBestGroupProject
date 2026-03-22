#include "clothes.hpp"
#include <iostream>
#include <string>

vector<Clothes> createCloset(const string filePath) {
    /*
    References: C++ documentation on std::stod function
    */
    vector<Clothes> closet;
    ifstream closetFile(filePath);
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
        getline(parser, field, ',');
        hue = stod(field);
        getline(parser, field, ',');
        sat = stod(field);
        getline(parser, field, '\n');
        light = stod(field);
        closet.push_back(Clothes(graphics, weather, type, hue, sat, light, ID));
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

    */
    cout << "Main program." << endl;
    string g = "Hello";
    Clothes a(g, 1,1,146,0,0);
    // Clothes b(g, 1,1,136,0,0);
    // Clothes c(g, 1,1,219,0,0);
    // Clothes d(g, 1,1,218,0,0);
    // Clothes e(g, 1,1,217,0,0);
    // Clothes f(g, 1,0,36,0,0);
    // Clothes m(g, 1,1,1,0,0);
    Clothes h(g, 1,1,0,0,0, 0);
    // a.addToCloset()
    vector<Clothes> cloth;

    cloth = createCloset(CLOSET_PATH);
    for(int i = 0; i < cloth.size(); i++) {
        cout << cloth[i];
    }

    // cloth.push_back(a);
    // cloth.push_back(b);
    // cloth.push_back(c);
    // cloth.push_back(d);
    // cloth.push_back(e);
    // cloth.push_back(f);
    // cloth.push_back(m);
    
    double* colorPaletteHues = tetradicPaletteGenerator(h.getHue());
    vector<Clothes> matches = h.matchingClothes(cloth, colorPaletteHues);
    cout << "Matching Clothes:" << endl;
    for(int i = 0; i < matches.size(); i++) {
        cout << matches[i];
    }
    // vector<Clothes> clothes({a,b,c,d,e,f,m,h});
    return 0;
}