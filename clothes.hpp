#include "colors.hpp"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const string CLOSET_PATH = "./Closet.csv";

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

class Clothes : public HSLColor {
    private:
        const int ID;
        string graphics;
        int weather;
        int type; // Defines tops versus bottoms, 1 for top, 0 for bottoms
    
    public:
        Clothes(string graphics, int weather, int type, double h, double s, double l) : ID(getNextID(CLOSET_PATH)) {
            this->graphics = graphics;
            this->weather = weather;
            this->type = type;
            hue = h;
            saturation = s;
            lightness = l;
        }

        // Use a reference to reduce memory usage, (pass by reference, not pass by value)
        vector<Clothes> matchingClothes(vector<Clothes>& closet, double* hues) {
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

        /* 
        Find last ID in closet,
        Initialization List to set ID variable,
        Pass values from menu,
        set all variables to values
        */
        // addToCloset(Clothes& piece) {
        //     /*
        //     Write Data fields as new row in Closet.csv
        //     */
        // }
};