#include <iostream>

using namespace std;

class HSLColor {
    private:
        int hue; // Measured in degrees
        int saturation; // Measured in percentages
        int lightness; // Measured in percentages
    public:

        int getHue() {return hue;}

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

        bool operator==(int value) {
            // Only check hue to include different shades of the same color
            if (hue == value) {
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

bool inRange(int value, int lowerBound, int upperBound) {
    cout << "LB: " << lowerBound << endl;
    cout << "UB: " << upperBound << endl;
    if (value >= lowerBound && value <= upperBound) {
        return true;
    }
    return false;
}

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
    /*
    Actually, We don't need to make 4 HSLColor objects.
    Instead, use an integer array to test equality on the hue.
    So, we can do HSLColor = 45;
    This will tell us if the hue of the color is equal to 45, leaving room for different saturations and lightnesses
    Also, this improves memory usage
    */
    HSLColor original;
    int colorPaletteHues[4];
    // Assign tetradic hue values to palette array 
    for (int i = 0; i < 4; i++) {
        int offset = 90 * i;
        int newValue = original.getHue() + offset;
        if (newValue > 359) {
            newValue -= 360;
        }
        colorPaletteHues[i] = newValue;

    }
    HSLColor closetColors[10] = {
        HSLColor(40, 100, 100),
        HSLColor(50),
        HSLColor(60),
        HSLColor(70),
        HSLColor(80),
        HSLColor(90),
        HSLColor(100),
        HSLColor(110),
        HSLColor(120),
        HSLColor(120),
    };
    int loops = 0;
    bool match = false;
    LinkedList head;
    head.head = NULL;
    do {
        /*
        For clothes in partitioned closet,
        If hue is within range,
        Add to matchingColor Linked list of Clothes objects
        */
        for(int i = 0; i < 10; i++) {
            for (int j = 0; j < 4; j++) {
                int lowerBound = colorPaletteHues[j] - (36 * loops);
                int upperBound = colorPaletteHues[j] + (36 * loops);
                if (lowerBound < 0) {
                    lowerBound += 360;
                } else if (upperBound > 359) {
                    upperBound -= 360;
                }
                if (inRange(closetColors[i].getHue(), lowerBound, upperBound)) {
                    head.addUnique(closetColors[i].getHue());
                    match = true;
                }
            }
        }
        loops++;
    } while (match == false);
    cout << loops << endl;
    cout << head;
    /*
    If no tops in closet, return error message.
    If no bottoms in closet, return error message.
    */

    /*
    Loop until match found,
    Each iteration, increase range by 10%, = add/subtract 36 degrees from each value
    */
    return 0;    
}