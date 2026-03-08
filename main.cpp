#include <iostream>

using namespace std;

class HSLColor {
    public:
        int hue; // Measured in degrees
        int saturation; // Measured in percentages
        int lightness; // Measured in percentages

        HSLColor(int hue = 40, int saturation= 35, int lightness = 75) {
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
    HSLColor original;
    // Need to make a full copy at a new memory address
    HSLColor colorPalette[3] = {HSLColor(original.hue + 90), HSLColor(original.hue + 180), HSLColor(original.hue + 270)};
    HSLColor tetradic1(original.hue + 90);
    HSLColor tetradic2(original.hue + 180);
    HSLColor tetradic3(original.hue + 270);
}