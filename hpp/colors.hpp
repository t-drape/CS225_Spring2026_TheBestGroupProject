/*
Purpose: 
This header file defines the major color types we use throughout the system. Additionally, we define
two conversion functions that are not class-specific, but allow us to convert between the color classes we have defined.
*/

#include <iostream>

using namespace std;

class HSLColor {
    protected:
        double hue; // Measured in degrees
        double saturation; // Measured in percentages
        double lightness; // Measured in percentages
    public:
        int getHue() {return hue;}
        double getLightness() {return lightness;}
        double getSaturation() {return saturation;}

        HSLColor(double hue = 40, double saturation = 35, double lightness = 75) {
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
};

class RGBColor {
    private:
        int redValue;
        int greenValue;
        int blueValue;
    public:
        RGBColor(int r, int g, int b) {
            redValue = r;
            greenValue = g;
            blueValue = b;
        }

        double getRedValue() {
            return double(redValue);
        }

        double getGreenValue() {
            return double(greenValue);
        }

        double getBlueValue() {
            return double(blueValue);
        }
        
        friend ostream& operator<<(ostream& os, RGBColor& color) {
            os << "Red: " << color.redValue;
            os << " Green: " << color.greenValue;
            os << " Blue: " << color.blueValue;
            os << endl;
            return os;
        }

};

RGBColor* convertHSLtoRGB(HSLColor& color);
HSLColor* convertRGBtoHSL(RGBColor& color);