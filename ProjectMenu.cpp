#include<iostream>
#include "read.hpp"
#include "clothes.hpp"
#include <string.h>

using namespace std;



int main(){
    string closetName;
    string addToCloset;
    int weather;
    string colorful;
    string chooseOutfit;
    cout<<"Welcome to the outfit selector program!"<<endl;
    cout<<"What is your name: "<<endl;
    cin>>closetName;
    cout<<"What is the weather looking like today? Please Input Fahrenheit value: "<<endl;
    cin>>weather;
    if (weather >=70){

    }
    else if(weather < 70){

    } 
    cout<<"Are you looking for a colorful outfit today?: yes or no"<<endl;
    cin>>colorful;
    if (colorful =="yes"){
        //choose clothes that isnt white or black
    }
    else if(colorful =="no"){
        //choose clothes that is plane colors 
    }
    cout<<"Would you like to add things to your closet "<<closetName<<" ?: yes or no"<<endl;
    cin>>addToCloset;
    if (addToCloset == "yes") {
        int type = 0;
        cout << "Is it a (0) Bottom or (1) Top piece?" << endl;
        cin >> type;

        if (!cin) {
            cout << "Invalid Input. Aborting action, please start again." << endl;
            // Change to recursive function call
            exit(1);
        }

        int weather = 0;
        cout << "Is this a (0) Fall/Winter [cold] or (1) Spring/Summer [warm] piece?" << endl;
        cin >> weather;

        if (!cin) {
            cout << "Invalid Input. Aborting action, please start again." << endl;
            // Change to recursive function call
            exit(1);
        }

        string graphic = "None";
        cout << "What graphic? (If None, type None)" << endl;
        getline(cin, graphic);
        getline(cin, graphic);

        cout << "Choose your Color from the Color Dialog." << endl;
        vector<int> colorVector = getColors();
        RGBColor rgb = RGBColor(colorVector[0], colorVector[1], colorVector[2]);
        HSLColor* hsl = convertRGBtoHSL(rgb);
        double hue = hsl->getHue();
        double sat = hsl->getSaturation();
        double light = hsl->getLightness();
        delete hsl;
        Clothes nc = Clothes(graphic, weather, type, hue, sat, light);
        nc.addToCloset();
        /* 
        Have the user specify graphics, weather, type, etc.
        Then, use the color dialog to select the closest color.
        Create a clothes object with the data.
        Save to CSV.
        */

    }
    if (addToCloset =="no"){
        cout<<"Would you like to choose an outfit now?: yes or no"<<endl;
        cin>>chooseOutfit;
        if (chooseOutfit == "yes"){

        }
        if(chooseOutfit == "no"){

        }
    }
    cout<<"Would you like to choose an outfit?: yes or no"<<endl;
    cin>>chooseOutfit;
    if (chooseOutfit == "yes"){

    }
    if(chooseOutfit == "no"){

    }

}
