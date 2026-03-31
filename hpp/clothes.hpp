/*
Purpose:
This header file defines the integral class of our program- our Clothes class definition.
This file includes the auxiliary header files to improve readability and separation of concerns.
*/

#ifndef CLOTHES_H
#define CLOTHES_H

#include <vector>

#include "helper.hpp"
#include "colors.hpp"
#include "globalVars.hpp"

void swap(double* a, double* b);

class Clothes : public HSLColor {
    private:
        const int ID;
        string graphics;
        int weather; // Defines hot versus cold, 0 for cold, 1 for hot
        int type; // Defines tops versus bottoms, 1 for top, 0 for bottoms
    
    public:
        Clothes(string graphics, int weather, int type, double h, double s, double l, int id=getNextID(CLOSET_PATH));
          ~Clothes();
        string getGraphic();

        // Use a reference to reduce memory usage, (pass by reference, not pass by value)
        vector<Clothes> matchingClothes(vector<Clothes>& closet, double* hues);

        void addToCloset();
        /* 
        Find last ID in closet,
        Initialization List to set ID variable,
        Pass values from menu,
        set all variables to values
        */

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

void warmTopDescription(Clothes& piece);
void coldTopDescription(Clothes& piece);
void warmBottomDescription(Clothes& piece);
void coldBottomDescription(Clothes& piece);

#endif
