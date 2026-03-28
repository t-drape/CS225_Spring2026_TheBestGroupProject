#include<iostream>
#include "read.hpp"
#include "clothes.hpp"

using namespace std;

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
int main(){
    string closetName;
    string addToCloset;
    int weather;
    string colorful;
    string chooseOutfit;
    string graphic;
    cout<<"Welcome to the outfit selector program!"<<endl;
    cout<<"What is your name: "<<endl;
    cin>>closetName;
    cout<<"Would you like to add an item to the closet? yes or no "<<endl;
    cin>>addToCloset;
    if (addToCloset == "yes"){
    }
    else if(addToCloset == "no"){
        cout<<"Welcome to the outfit selector "<<closetName<<" "<<endl;
        cout<<"There will be a couple questions to help determine a great outfit!"<<endl;
        cout<<"What is the weather looking like today? Please Input Fahrenheit value: "<<endl;
        cin>>weather;
        if (weather >=70){
            weather = 1;
        }
        else if(weather < 70){
            weather = 0;
        } 
        cout<<"Are you looking for a colorful outfit today?: yes or no"<<endl;
        cin>>colorful;
        int c = 0;
        if (colorful =="yes"){
            int c = 1;
        }
        cout<<"Which graphic shirt would you like? (in None type None)"<<endl;
        cin>>graphic;
        //this will select a shirt first ands then match a pair of bottoms to it
        createCloset(weather, c, graphic);
    } 
    /*
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
        */
        /* 
        Have the user specify graphics, weather, type, etc.
        Then, use the color dialog to select the closest color.
        Create a clothes object with the data.
        Save to CSV.
        */

    //}
    
    
}
