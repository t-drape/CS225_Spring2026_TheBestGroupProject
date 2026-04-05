/*
Purpose: 
This header file defines the major color types we use throughout the system. Additionally, we define
two conversion functions that are not class-specific, but allow us to convert between the color classes we have defined.
*/

#ifndef COLORS_H
#define COLORS_H

#include <iostream>

using namespace std;

class HSLColor {
    protected:
        double hue; // Measured in degrees
        double saturation; // Measured in percentages
        double lightness; // Measured in percentages
    public:
        // Use an integer here, as the precision should be to the 1's place.
        // For example, Google's Color picker doesn't display fractional values, only integers in [0, 359].
        int getHue();
        double getLightness();
        double getSaturation();

        HSLColor(double hue = 40, double saturation = 35, double lightness = 75);
        ~HSLColor();
        friend ostream& operator<<(ostream& os, HSLColor& color);
};

class RGBColor {
    private:
        int redValue;
        int greenValue;
        int blueValue;
    public:
        RGBColor(int r, int g, int b);
        ~RGBColor();
        double getRedValue();

        double getGreenValue();

        double getBlueValue();
        
        friend ostream& operator<<(ostream& os, RGBColor& color);

};

RGBColor* convertHSLtoRGB(HSLColor& color);
HSLColor* convertRGBtoHSL(RGBColor& color);

#endif
