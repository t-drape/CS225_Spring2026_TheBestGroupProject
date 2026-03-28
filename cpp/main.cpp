#include <iostream>
#include <string>

#include "./../hpp/clothes.hpp"

vector<Clothes> createCloset(const string filePath) {
    /*
    Purpose: Create a vector representation of the Clothes objects in the user's closet file
    References: C++ documentation on std::stod function
    */
    bool allOneType = true;
    vector<Clothes> closet;
    int lastType = -1;
    ifstream closetFile(filePath);

    if (!closetFile.good()) {
        throw(FILE_BAD_MESSAGE);
    }

    int ID;
    string graphics;
    int weather;
    int type;
    double hue;
    double sat;
    double light;

    string inputLine;
    string field;

    getline(closetFile, inputLine); // Skip the header line

    while(!closetFile.eof() && getline(closetFile, inputLine)) {
        stringstream parser(inputLine);
        getline(parser, field, ',');
        ID = stoi(field);
        getline(parser, field, ',');
        graphics = field;
        getline(parser, field, ',');
        weather = stoi(field);
        getline(parser, field, ',');
        type = stoi(field);
        if (lastType == -1) {
            lastType = type;
        }
        if (type != lastType) {
            allOneType = false;
        }
        getline(parser, field, ',');
        hue = stod(field);
        getline(parser, field, ',');
        sat = stod(field);
        getline(parser, field, '\n');
        light = stod(field);
        closet.push_back(Clothes(graphics, weather, type, hue, sat, light, ID));
    }
    if (allOneType) {
        throw(type);
    }
    return closet;
}

// Function Definition from colors.hpp
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

    double r = 0;
    double g = 0;
    double b = 0;
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

int main() {
    /*
        Notes: 
            MatchingClothes will get stuck in an infinite loop if the closet contains only a single type of clothing.
            For example, if a person has only type=1 clothes, then the loop will continue to expand, and will not find any matches,
            since it only matches for type=0 clothes. 

            Future feature expansion includes deletion. Removing clothes from the CSV file is beyond the scope of this project, however,
            it is a feature that we will try to include later on in the development process.

            Unique error: If the closet file has no clothes, but has an extra line (besides the header), then the program will not work correctly.

    */
    cout << "Main program." << endl;
    string g = "Hello";

    try {
        Clothes h("None", 1,1,145,.71,.39);
        h.addToCloset();
        vector<Clothes> cloth;
        cloth = createCloset(CLOSET_PATH);
        double* colorPaletteHues = tetradicPaletteGenerator(h.getHue());
        vector<Clothes> matches = h.matchingClothes(cloth, colorPaletteHues);
        cout << "Matching Clothes:" << endl;
        for(int i = 0; i < matches.size(); i++) {
            RGBColor* r1 = convertHSLtoRGB(matches[i]);
            cout << *r1;

        }
    }
    catch(int m) {
        if(m == 1) {
            cout << "Sorry, your closet currently only contains tops. We cannot create outfits without bottoms." << endl;
        } else {
            cout << "Sorry, your closet currently only contains bottoms. We cannot create outfits without tops." << endl;
        }
    }
    catch(string msg) {
        cout << msg << endl;
    }
    return 0;
}