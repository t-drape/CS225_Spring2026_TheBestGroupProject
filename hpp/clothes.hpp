/*
Purpose:
This header file defines the integral class of our program- our Clothes class definition.
This file includes the auxiliary header files to improve readability and separation of concerns.
*/

#include "colors.hpp"
#include "./../hpp/helper.hpp"
#include <vector>

void swap(double* a, double* b) {
    /*
        Reference: Google AI overview of swap in C++
    */
    double temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

class Clothes : public HSLColor {
    private:
        const int ID;
        string graphics;
        int weather; // Defines hot versus cold, 0 for cold, 1 for hot
        int type; // Defines tops versus bottoms, 1 for top, 0 for bottoms
    
    public:
        Clothes(string graphics, int weather, int type, double h, double s, double l, int id=getNextID(CLOSET_PATH)) : ID(id) {
            this->graphics = graphics;
            this->weather = weather;
            this->type = type;
            hue = h;
            saturation = s;
            lightness = l;
        }

        // Use a reference to reduce memory usage, (pass by reference, not pass by value)
        vector<Clothes> matchingClothes(vector<Clothes>& closet, double* hues) {
            int loops = 0;
            bool match = false;
            vector<Clothes> matches;
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
                for(int i = 0; i < closet.size(); i++) {
                    // 4 is the number of tetradic hues
                    if (closet[i].type != type) {
                        for (int j = 0; j < 4; j++) {
                        /*
                        Originally, I expanded both sides. This led to too many colors included.
                        So, the lower bound equals the original value, the upper bound equals the computed value.
                        */
                            double upperBound = hues[j] + (36 * loops);
                            double lowerBound = hues[j];
                            if (upperBound > 359) {
                                upperBound -= 360;
                            }
                            if (lowerBound > upperBound) {
                                swap(&lowerBound, &upperBound);
                            }

                            if (inRange(closet[i].getHue(), lowerBound, upperBound)) {
                                // Change to a Clothes Object once we have full project developed
                                matches.push_back(closet[i]);
                                match = true;
                            }
                        }
                    }
                }
                loops++;
            } while (match == false);
            return matches;
        }

        /* 
        Find last ID in closet,
        Initialization List to set ID variable,
        Pass values from menu,
        set all variables to values
        */

        void addToCloset() {
            /*
                References:
                    GoogleAI Overview of appending to a file in C++.
                    GoogleAI Overview of writing to a CSV file in C++.
                    GoogleAI Overview of append mode if no file exists.
                    Note: If the specified file does not exist, then, with append, a new empty file is created.
            */
            cout << "Adding Piece to Collection: ID = " << ID << "." << endl;
            ofstream closetFile;
            closetFile.open(CLOSET_PATH, std::ios::app);
            closetFile << "\n" << ID << "," << graphics << "," << weather << "," << type << "," << hue << "," << saturation << "," << lightness;
            closetFile.close();

            // Write Data fields as new row in Closet.csv
        }

        /*
            Note: 
            The IDS will not shift on deletion. This is fine. We have an incrementing count,
            ensuring that no new piece of clothing shares an ID or overwrites an old one.
            For example,
            1) The first piece of clothing in the file is deleted. This does not affect insertion, as new pieces
            will still be appended to the file without change.
            2) The last piece of clothing is deleted. When the user adds a piece of clothing, then the ID spot is overwritten,
            but the old piece is no longer needed, so this is proper functionality. 
        */
        
};

vector<Clothes> createCloset(const string filePath);
vector<Clothes> findShirts(const string filePath, int w, int colorful, string chosenGraphic, int chosenType=SHIRTS);
void addPiece();
