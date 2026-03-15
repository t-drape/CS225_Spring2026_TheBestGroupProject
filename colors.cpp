#include <iostream>
#include <vector>
#include "clothes.hpp"

using namespace std;

bool inRange(double value, double lowerBound, double upperBound) {
    if (value >= lowerBound && value <= upperBound) {
        return true;
    }
    return false;
}

double* tetradicPaletteGenerator(double hue) {
    /*
    References:
    color function: https://customstickers.com/community/blog/how-to-calculate-complementary-triadic-and-tetradic-colors-from-a-hex-code?srsltid=AfmBOoqEuD3xMxsxkL3ULkV0TfeZKsFD4GemfKF8-prqylBgYfmWh-Bo
    return array: https://www.digitalocean.com/community/tutorials/return-array-in-c-plus-plus-function
    */

    static double colorPaletteHues[4];
    // Assign tetradic hue values to palette array 
    for (int i = 0; i < 4; i++) {
        int offset = 90 * i;
        double newValue = hue + offset;
        if (newValue > 359) {
            newValue -= 360;
        }
        colorPaletteHues[i] = newValue;
    }
    return colorPaletteHues;
}

vector<Clothes> matchingClothes(vector<Clothes> closet, double* hues) {
    int loops = 0;
    bool match = false;
    vector<Clothes> matches;
    /*
    Loop until match found,
    Each iteration, increase range by 10%, = add/subtract 36 degrees from each value
    */
    do {
        /*
        For clothes in partitioned closet,
        If hue is within range,
        Add to matchingColor Linked list of Clothes objects
        */
        for(int i = 0; i < closet.size(); i++) {
            // 4 is the number of tetradic hues
            for (int j = 0; j < 4; j++) {
                /*
                Originally, I expanded both sides. This led to too many colors included.
                So, the lower bound equals the original value, the upper bound equals the computed value.
                */
                double upperBound = hues[j] + (36 * loops);
                if (upperBound > 359) {
                    upperBound -= 360;
                }
                if (inRange(closet[i].getHue(), hues[j], upperBound)) {
                    // Change to a Clothes Object once we have full project developed
                    matches.push_back(closet[i]);
                    match = true;
                }
            }
        }
        loops++;
    } while (match == false);
    return matches;
}

int main() {
    string g = "Hello";
    Clothes a(g, 1,1,146,0,0);
    Clothes b(g, 1,1,136,0,0);
    Clothes c(g, 1,1,219,0,0);
    Clothes d(g, 1,1,218,0,0);
    Clothes e(g, 1,1,217,0,0);
    Clothes f(g, 1,1,36,0,0);
    Clothes m(g, 1,1,1,0,0);
    Clothes h(g, 1,1,0,0,0);

    vector<Clothes> cloth;
    cloth.push_back(a);
    cloth.push_back(b);
    cloth.push_back(c);
    cloth.push_back(d);
    cloth.push_back(e);
    cloth.push_back(f);
    cloth.push_back(m);
    
    double* colorPaletteHues = tetradicPaletteGenerator(h.getHue());
    vector<Clothes> matches = matchingClothes(cloth, colorPaletteHues);
    for(int i = 0; i < matches.size(); i++) {
        cout << matches[i];
    }
    // vector<Clothes> clothes({a,b,c,d,e,f,m,h});
    return 0;
}


// int main() {
//     /*
//     Given an HSL value,
//     Compute the tetradic color palette,
//     If no colors found in array,
//         Extend range to values within 10% of tetradic hues
//     Else,
//         Pick random tetradic color based on user input
//     Return HSL value,
//     Convert HSL values to RGB,
//     Display RGB value(s) on clothes to user
//     */

//     /*
//     Actually, We don't need to make 4 HSLColor objects.
//     Instead, use an integer array to test equality on the hue.
//     So, we can do HSLColor == 45;
//     This will tell us if the hue of the color is equal to 45, leaving room for different saturations and lightnesses
//     Also, this improves memory usage
//     */

//     // HSLColor original(0);
//     // // Assign tetradic hue values to palette array
//     // int* colorPaletteHues = tetradicPaletteGenerator(original.getHue());

//     // // Test data. Change to read Clothes from Closet once full project linked
//     // HSLColor closetColors[10] = {
//     //     HSLColor(36, 100, 100),
//     //     HSLColor(50),
//     //     HSLColor(60),
//     //     HSLColor(70),
//     //     HSLColor(80),
//     //     HSLColor(40),
//     //     HSLColor(50),
//     //     HSLColor(60),
//     //     HSLColor(70),
//     //     HSLColor(80),
//     // };

//     // LinkedList head;
//     // head.head = NULL;

//     // head.head = matchingClothes(closetColors, colorPaletteHues);

//     // cout << head;

//     // HSLColor test(136, .54, .43);
//     // RGBColor* ptr = convertHSLtoRGB(test);
//     // cout << *ptr;

//     // RGBColor test2(50, 168, 82);
//     // HSLColor* ptr2 = convertRGBtoHSL(test2);
//     // cout << *ptr2;

//     // return 0;    
// }