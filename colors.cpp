#include <iostream>

using namespace std;

class HSLColor {
    private:
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

        friend ostream& operator<<(ostream& os, RGBColor& color) {
            os << "Red: " << color.redValue;
            os << " Green: " << color.greenValue;
            os << " Blue: " << color.blueValue;
            os << endl;
            return os;
        }

};

class Node {
    public:
        int me;
        Node* next;
    Node() : next(NULL) {};
};

class LinkedList {
    public:
        Node* head;
        bool inList(int hue) {
            Node* testHead = head;
            while(testHead != NULL) {
                if (testHead->me == hue) {
                    return true;
                }
                testHead = testHead->next;
            }
            return false;
        }
        void addUnique(int hue) {
            if (inList(hue)) {
                return;
            }
            Node* np = new Node;
            np->me = hue;
            if (head == NULL) {
                head = np;
            } else {
                Node* testHead;
                testHead = head;
                while(testHead->next != NULL) {
                    testHead = testHead->next;
                }
                testHead->next = np;
            }
        }

        friend ostream& operator<<(ostream& os, LinkedList& ll) {
            Node* testHead = ll.head;
            while (testHead->next != NULL) {
                os << "Value: " << testHead->me << endl;
                testHead = testHead->next;
            }
            os << "Value: " << testHead->me << endl;
            return os;
        }
};

bool inRange(int value, int lowerBound, int upperBound) {
    if (value >= lowerBound && value <= upperBound) {
        return true;
    }
    return false;
}

int* tetradicPaletteGenerator(int hue) {
    /*
    References:
    color function: https://customstickers.com/community/blog/how-to-calculate-complementary-triadic-and-tetradic-colors-from-a-hex-code?srsltid=AfmBOoqEuD3xMxsxkL3ULkV0TfeZKsFD4GemfKF8-prqylBgYfmWh-Bo
    return array: https://www.digitalocean.com/community/tutorials/return-array-in-c-plus-plus-function
    */

    static int colorPaletteHues[4];
    // Assign tetradic hue values to palette array 
    for (int i = 0; i < 4; i++) {
        int offset = 90 * i;
        int newValue = hue + offset;
        if (newValue > 359) {
            newValue -= 360;
        }
        colorPaletteHues[i] = newValue;
    }
    return colorPaletteHues;
}

Node* matchingClothes(HSLColor* closet, int* hues) {
    int loops = 0;
    bool match = false;
    LinkedList head;
    head.head = NULL;
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
        for(int i = 0; i < 10; i++) {
            for (int j = 0; j < 4; j++) {
                /*
                Originally, I expanded both sides. This led to too many colors included.
                So, the lower bound equals the original value, the upper bound equals the computed value.
                */
                int upperBound = hues[j] + (36 * loops);
                if (upperBound > 359) {
                    upperBound -= 360;
                }
                if (inRange(closet[i].getHue(), hues[j], upperBound)) {
                    // Change to a Clothes Object once we have full project developed
                    head.addUnique(closet[i].getHue());
                    match = true;
                }
            }
        }
        loops++;
    } while (match == false);
    return head.head;

}

RGBColor* convertHSLtoRGB(HSLColor& color) {
    /*
    Reference: https://www.baeldung.com/cs/convert-color-hsl-rgb
    */

    // Chroma equation: (1 - |2L - 1|) x S
    double chromaP2 = (2 * color.getLightness() - 1);
    if (chromaP2 < 0) {
        chromaP2 *= -1;
    }
    double chroma = (1 - chromaP2) * color.getSaturation();
    cout << "Chroma: " << chroma << endl;

    double hue_derivative = color.getHue() / 60.0;
    cout << "Hue Derivative: " << hue_derivative << endl;

    // X = C * (1 - |(H' % 2) - 1|})
    double xP3 = (fmod(hue_derivative, 2.0)) - 1;
    if (xP3 < 0) {
        xP3 *= -1;
    }
    double x = chroma * (1 - xP3);
    cout << "X: " << x << endl;

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

    double m = color.getLightness() - (chroma / 2);
    cout << "M: " << m << endl;

    cout << "R1, G1, B1: " << r << ", " << g<< ", " << b << endl;
    r += m;
    g += m;
    b += m;
    cout << "R1+m, G1+m, B1+m: " << r << ", " << g<< ", " << b << endl;

    RGBColor* nc = new RGBColor(r * 255, g * 255, b * 255);
    return nc;
}


int main() {
    /*
    Given an HSL value,
    Compute the tetradic color palette,
    If no colors found in array,
        Extend range to values within 10% of tetradic hues
    Else,
        Pick random tetradic color based on user input
    Return HSL value,
    Convert HSL values to RGB,
    Display RGB value(s) on clothes to user
    */

    /*
    Actually, We don't need to make 4 HSLColor objects.
    Instead, use an integer array to test equality on the hue.
    So, we can do HSLColor == 45;
    This will tell us if the hue of the color is equal to 45, leaving room for different saturations and lightnesses
    Also, this improves memory usage
    */

    HSLColor original(0);
    // Assign tetradic hue values to palette array
    int* colorPaletteHues = tetradicPaletteGenerator(original.getHue());

    // Test data. Change to read Clothes from Closet once full project linked
    HSLColor closetColors[10] = {
        HSLColor(36, 100, 100),
        HSLColor(50),
        HSLColor(60),
        HSLColor(70),
        HSLColor(80),
        HSLColor(40),
        HSLColor(50),
        HSLColor(60),
        HSLColor(70),
        HSLColor(80),
    };

    LinkedList head;
    head.head = NULL;

    head.head = matchingClothes(closetColors, colorPaletteHues);

    cout << head;

    HSLColor test(136, .54, .43);
    RGBColor* ptr = convertHSLtoRGB(test);
    cout << *ptr;

    return 0;    
}