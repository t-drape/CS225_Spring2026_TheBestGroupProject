/*
Purpose: 
This header file defines helper functions that contribute to program functionality but are not class-specific.
Additionally, this header file contains our global variables, such as the predefined path to the closet file.
*/

#include <fstream>
#include <sstream>

using namespace std;

const string CLOSET_PATH = "./Closet.csv";

int getNextID(const string file) {
    /*
    Reference: Google AI overview of reading a CSV in C++
    */

    ifstream f(file);
    int num;
    string field;
    string str;

    getline(f, str); // Skip the header line

    while (getline(f, str)) {
        stringstream parser(str);
        // Must be single quotes, otherwise it reads the character as a string, throwing an error
        getline(parser, field, ',');
    }
    num = stoi(field);
    ++num;
    return num;
}

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