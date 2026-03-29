/*
Purpose: 
This header file defines helper functions that contribute to program functionality but are not class-specific.
Additionally, this header file contains our global variables, such as the predefined path to the closet file.
*/

#include <fstream>
#include <sstream>

enum {SHORTS, SHIRTS};
enum {COLD, WARM};
enum {NOT_COLORFUL, COLORFUL};

using namespace std;

const string CLOSET_PATH = "./../Closet.csv";
const string FILE_BAD_MESSAGE = "Error opening the file.";
const string INSUFFICENT_CLOTHES_MESSAGE = "Sorry, you haven't added enough pieces to your closet yet. Add some more pieces then try again.";
const string NO_MATCH_MESSAGE = "Sorry, you don't own clothes matching that description. Please try again.";

const string TSHIRT_PATH = "./../displayFigures/tshirt.txt";
const string SHORTS_PATH = "./../displayFigures/shorts.txt";
const string LONG_SLEEVE_SHIRT_PATH = "./../displayFigures/LongSleeveTshirt.txt";
const string PANT_PATH = "./../displayFigures/pants.txt";

void swap(double* a, double* b);

// Change to function declaration

int getNextID(const string file) {
    /*
    Reference: Google AI overview of reading a CSV in C++
    */

    ifstream f(file);
    int num = -1;
    string field;
    string str;
    if (!f.good()) {
        throw(FILE_BAD_MESSAGE);
    }

    getline(f, str); // Skip the header line

    // This line ensures that the program runs correctly with empty closet files (only the header line)
    if (f.eof()) {
        return 0;
    }

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

// void displayClothes() {
//     ifstream closetFile(CLOSET_PATH);
//     string line;
//     while(!closetFile.eof()) {
//         closetFile >> line;
//         cout << "From file: " << line << endl;
//     }
// }

/* For deletion: 
    Display all items in the closet.
    Read all Clothes objects into a vector.
    Get user input of ID.
    Save to integer.
    Confirm deletion.
    Open Closet file in write mode (This overwrites all previous content, VERY DANGEROUS!)
    Once confirmed, begin loop:
        Save to file if clothes object ID does not equal delete ID

*/