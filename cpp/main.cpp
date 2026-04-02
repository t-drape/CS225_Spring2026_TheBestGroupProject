#include <iostream>
#include <climits>

// #include "./../hpp/read.hpp"
// #include "./../hpp/clothes.hpp"
// #include "./../hpp/colorDisplay.hpp"
// #include "colors.cpp"

#include "./../hpp/clothes.hpp"
#include "./../hpp/globalVars.hpp"
#include "./../hpp/helper.hpp"
#include "./../hpp/colors.hpp"
#include "./../hpp/colorDisplay.hpp"
#include "./../hpp/read.hpp"
#include "./../hpp/messages.hpp"

using namespace std;

int main(){
    srand(time(NULL));
    string addToCloset = "hello";
    int weather;
    string colorful;
    string chooseOutfit;
    string graphic;
    string name;

    cout << "What is your name?: ";
    getline(cin, name);
    Messages greetAndFarewell = Messages(name, "the Algorithmic Outfit Selector!", 
        "Welcome to", "You look good today, please come back tomorrow to keep looking this good hahaha! Thank you for visiting");
    cout << greetAndFarewell.welcome;

    string endLoop = "no";

    do {
        cout<<"Would you like to add an item to the closet? [yes, no]"<<endl;
        cin>>addToCloset;

        if (addToCloset == "yes"){
            addPiece();
        }
        else if(addToCloset == "no"){
            try {
                    vector<Clothes> fullCloset = createCloset(CLOSET_PATH);

                    cout<<"It's the Algorithmic Outfit Selector's Time to Shine! 🤩"<<endl;
                    cout<<"There will be a couple questions to help determine a great outfit!"<<endl;

                    cout<<"What is the weather looking like today? Please Input Fahrenheit value: ";
                    cin>>weather;

                    while (!cin) {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Invalid Input. Please input a numerical value: ";
                        cin >> weather;
                    }
                    if (weather >=70){
                        weather = WARM;
                    }
                    else if(weather < 70){
                        weather = COLD;
                    } 


                    cout<<"Are you looking for a colorful shirt today?: [yes, no]"<<endl;
                    cin>>colorful;
                    int c = NOT_COLORFUL;
                    if (colorful =="yes"){
                        c = COLORFUL;
                    }

                    // Need both the get rid of new line character being read
                    getline(cin, graphic);
                    cout<<"Which graphic shirt would you like? (Type 'None' for None, 'Any' for Random)"<<endl;
                    getline(cin, graphic);

                    //this will select a shirt first ands then match a pair of bottoms to it
                    try {
                        vector<Clothes> shirts = findShirts(CLOSET_PATH, weather, c, graphic);
                        int chosenTopIndex = 0;
                        if (shirts.size() > 1) { 
                            chosenTopIndex = rand() % shirts.size();
                        }

                        Clothes& top = shirts[chosenTopIndex];

                        vector<Clothes> bottoms = top.matchingClothes(fullCloset, tetradicPaletteGenerator(top.getHue()));
                        int chosenBottomIndex = 0;
                        if (bottoms.size() > 1) {
                            chosenBottomIndex = rand() % bottoms.size();
                        }

                        RGBColor* t = convertHSLtoRGB(shirts[chosenTopIndex]);
                        RGBColor* b = convertHSLtoRGB(bottoms[chosenBottomIndex]);

                        if (weather == WARM) {
                            warmTopDescription(top);
                            printColoredRGB(t->getRedValue(), t->getGreenValue(), t->getBlueValue(), tshirt());
                            warmBottomDescription(bottoms[chosenBottomIndex]);
                            printColoredRGB(b->getRedValue(), b->getGreenValue(), b->getBlueValue(), shorts());
                        } else {
                            coldTopDescription(top);
                            printColoredRGB(t->getRedValue(), t->getGreenValue(), t->getBlueValue(), longSleeveShirt());
                            coldBottomDescription(bottoms[chosenBottomIndex]);
                            printColoredRGB(b->getRedValue(), b->getGreenValue(), b->getBlueValue(), pants());
                        }
                        delete t;
                        delete b;
                    }
                    catch(string msg) {
                        cout << msg;
                    }
                }
            catch(int m) {
                if(m == SHIRTS) {
                    cout << "Sorry, your closet currently only contains tops. We cannot create outfits without bottoms." << endl;
                } else if (m == SHORTS) {
                    cout << "Sorry, your closet currently only contains bottoms. We cannot create outfits without tops." << endl;
                }
                exit(1);
            }
            catch(string msg) {
                cout << msg << endl;
                exit(1);
            }
        } 
        cout << "Do you want to exit the Algorithmic Outfit Selector? [yes, no]: ";
        cin >> endLoop;
    } while(endLoop == "no");
    cout << greetAndFarewell.goodbye;
}
