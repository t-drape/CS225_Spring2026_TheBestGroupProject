#include "colors.hpp"
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
            /* 
            Find last ID in closet,
            Initialization List to set ID variable,
            Pass values from menu,
            set all variables to values
            Add Piece to Closet
            */
        }

        // addToCloset(Clothes& piece) {
        //     /*
        //     Write Dat fields as new row in Closet.csv
        //     */
        // }
};