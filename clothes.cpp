#include "clothes.hpp"
#include <iostream>

int main() {
    string g = "hello";
    Clothes c(g, 1,1,40,30,10);
    cout << c;
    // cout << c.getHue() << endl;
    // cout << c.getSaturation() << endl;
    // cout << c.getLightness();
}