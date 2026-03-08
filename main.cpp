#include <iostream>

using namespace std;

class HSLColor {
    public:
        int hue; // Measured in degrees
        int saturation; // Measured in percentages
        int lightness; // Measured in percentages

        HSLColor(int hue = 40, int saturation = 35, int lightness = 75) {
            if (hue > 359) {
                hue -= 360;
            }
            this->hue = hue;
            this->saturation = saturation;
            this->lightness = lightness;
        }

        friend ostream& operator<<(ostream& os, HSLColor& color) {
            os << "Hue: " << color.hue;
            os << " Saturation: " << color.saturation;
            os << " Lightness: " << color.lightness;
            os << endl;
            return os;
        }

        bool operator==(HSLColor& color) {
            if (hue == color.hue && saturation == color.saturation && lightness == color.lightness) {
                return true;
            }
            return false;
        }
};

class RGBColor {
    public:
        int redValue;
        int greenValue;
        int blueValue;
};

int main() {
    /*
    Given an HSL value,
    Compute the tetradic color palette,
    If no colors found in array,
        Extend range to values within 15 degrees
    Else,
        Pick random tetradic color based on user input
    Return HSL value,
    Convert HSL values to RGB,
    Display RGB value(s) on clothes to user
    */
    HSLColor original(180, 20, 10);
    // Need to make a full copy at a new memory address
    // Create an array of the 4 tetradic colors to match the closet colors against
    HSLColor colorPalette[4] = {original, HSLColor(original.hue + 90), HSLColor(original.hue + 180), HSLColor(original.hue + 270)};
    for(int i = 0; i < 4; i++) {
        cout << colorPalette[i];
    }
    HSLColor closetColors[10] = {
        HSLColor(),
        HSLColor(),
        HSLColor(),
        HSLColor(),
        HSLColor(),
        HSLColor(),
        HSLColor(),
        HSLColor(),
        HSLColor(),
        HSLColor(),
    };
    for (int i = 0; i < 10; i++) {
        for(int j = 0; j < 4; j++) {
            if (closetColors[i] == colorPalette[j]) {
                cout << "Found a match";
                return 0;
            }
        }
    }
    cout << "No match found";
    return 0;    
}