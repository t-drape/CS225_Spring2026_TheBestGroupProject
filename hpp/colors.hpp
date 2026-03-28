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

RGBColor* convertHSLtoRGB(HSLColor& color) {
    /*
    Reference: https://www.baeldung.com/cs/convert-color-hsl-rgb
    */

    // Chroma equation: (1 - |2L - 1|) x S
    double chromaP2 = (2 * color.getLightness() - 1);
    if (chromaP2 < 0) {
        chromaP2 *= -1.0;
    }
    double chroma = (1 - chromaP2) * color.getSaturation();
    // cout << "Chroma: " << chroma << endl;

    double hue_derivative = color.getHue() / 60.0;
    // cout << "Hue Derivative: " << hue_derivative << endl;

    // X = C * (1 - |(H' % 2) - 1|})
    double xP3 = (fmod(hue_derivative, 2.0)) - 1;
    if (xP3 < 0) {
        xP3 *= -1.0;
    }
    double x = chroma * (1 - xP3);
    // cout << "X: " << x << endl;

    double r,g,b = 0;
    if (hue_derivative <= 1) {
        r = chroma;
        g = x;
    } else if (hue_derivative <= 2) {
        r = x;
        g = chroma;
    } else if (hue_derivative <= 3) {
        g = chroma;
        b = x;
    } else if (hue_derivative <= 4) {
        g = x;
        b = chroma;
    } else if (hue_derivative <= 5) {
        r = x;
        b = chroma;
    } else if (hue_derivative <= 6) {
        r = chroma;
        b = x;
    }

    double m = color.getLightness() - (chroma / 2.0);
    // cout << "M: " << m << endl;

    // cout << "R1, G1, B1: " << r << ", " << g<< ", " << b << endl;
    r += m;
    g += m;
    b += m;
    // cout << "R1+m, G1+m, B1+m: " << r << ", " << g<< ", " << b << endl;
    cout << "Red: " << r * 255 << " Green: " << g * 255 << " Blue: " << b*255 << endl; 
    RGBColor* nc = new RGBColor(r * 255, g * 255, b * 255);
    return nc;
}

HSLColor* convertRGBtoHSL(RGBColor& color) {
    /*
    References: https://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
    */

    double red = color.getRedValue();
    double green = color.getGreenValue();
    double blue = color.getBlueValue();

    red /= 255;
    green /= 255;
    blue /= 255;

    double max;
    double min;

    if (red >= green && red >= blue) {
        max = red;
    } else if (green >= red && green >= blue) {
        max = green;
    } else if (blue >= red && blue >= green) {
        max = blue;
    }

    if (red <= green && red <= blue) {
        min = red;
    } else if (green <= red && green <= blue) {
        min = green;
    } else if (blue <= red && blue <= green) {
        min = blue;
    }

    double l = (min + max) / 2.0;

    double sat;
    double hue;

    if (max == min) {
        sat = 0;
        hue = 0;
    } else if (l <= 0.5) {
        sat = (max-min)/(max+min);
    } else if (l > 0.5) {
        sat = (max-min)/(2.0-max-min);
    }

    double h;

    if (red == max) {
        h = (green - blue)/(max-min);
    } else if (green == max) {
        h = (2.0) + (blue-red)/(max-min);
    } else if (blue == max) {
        h = (4.0) + (red-green)/(max-min);
    }

    h *= 60;

    if (h < 0) {
        h += 360;
    }

    HSLColor* nc = new HSLColor(h, sat, l);
    return nc;
}