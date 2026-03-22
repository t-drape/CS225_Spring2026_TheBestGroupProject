#include "clothes.hpp"
#include <iostream>

int main() {
    /*
        Note: 
            MatchingClothes will get stuck in an infinite loop if the closet contains only a single type of clothing.
            For example, if a person has only type=1 clothes, then the loop will continue to expand, and will not find any matches,
            since it only matches for type=0 clothes. 
    */
    cout << "Main program." << endl;
    string g = "Hello";
    Clothes a(g, 1,1,146,0,0);
    Clothes b(g, 1,1,136,0,0);
    Clothes c(g, 1,1,219,0,0);
    Clothes d(g, 1,1,218,0,0);
    Clothes e(g, 1,1,217,0,0);
    Clothes f(g, 1,0,36,0,0);
    Clothes m(g, 1,1,1,0,0);
    Clothes h(g, 1,1,0,0,0);

    h.addToCloset();

    vector<Clothes> cloth;
    cloth.push_back(a);
    cloth.push_back(b);
    cloth.push_back(c);
    cloth.push_back(d);
    cloth.push_back(e);
    cloth.push_back(f);
    cloth.push_back(m);
    
    double* colorPaletteHues = tetradicPaletteGenerator(h.getHue());
    vector<Clothes> matches = h.matchingClothes(cloth, colorPaletteHues);
    for(int i = 0; i < matches.size(); i++) {
        cout << matches[i];
    }
    // vector<Clothes> clothes({a,b,c,d,e,f,m,h});
    return 0;
}