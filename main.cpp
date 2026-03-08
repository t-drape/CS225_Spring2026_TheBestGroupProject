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
};

class RGBColor {
    public:
        int redValue;
        int greenValue;
        int blueValue;
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
    Reference: https://www.digitalocean.com/community/tutorials/return-array-in-c-plus-plus-function
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
    // do {
    //     /*
    //     For clothes in partitioned closet,
    //     If hue is within range,
    //     Add to matchingColor Linked list of Clothes objects
    //     */
    //     for(int i = 0; i < 10; i++) {
    //         for (int j = 0; j < 4; j++) {
    //             /*
    //             Originally, I expanded both sides. This led to too many colors included.
    //             So, the lower bound equals the original value, the upper bound equals the computed value.
    //             */
    //             int upperBound = colorPaletteHues[j] + (36 * loops);
    //             if (upperBound > 359) {
    //                 upperBound -= 360;
    //             }
    //             if (inRange(closetColors[i].getHue(), colorPaletteHues[j], upperBound)) {
    //                 // Change to a Clothes Object once we have full project developed
    //                 head.addUnique(closetColors[i].getHue());
    //                 match = true;
    //             }
    //         }
    //     }
    //     loops++;
    // } while (match == false);

    cout << head;

    return 0;    
}