#include <vector>
#include <sstream>

#include "./../hpp/clothes.hpp"
#include "./../hpp/read.hpp"

using namespace std;

Clothes::Clothes(string graphics, int weather, int type, double h, double s, double l, int id) : ID(id) {
    this->graphics = graphics;
    this->weather = weather;
    this->type = type;
    hue = h;
    saturation = s;
    lightness = l;
}

string Clothes::getGraphic() {return graphics;}

// Use a reference to reduce memory usage, (pass by reference, not pass by value)
vector<Clothes> Clothes::matchingClothes(vector<Clothes>& closet, double* hues) {
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
            if (closet[i].type != type && closet[i].weather == weather) {
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

void Clothes::addToCloset() {
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
Find last ID in closet,
Initialization List to set ID variable,
Pass values from menu,
set all variables to values
*/

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
    if (closet.size() == 0) {
        throw(INSUFFICENT_CLOTHES_MESSAGE);
    } 
    if (allOneType) {
        throw(type);
    }
    return closet;
}

// This refines the closet based on user input to create a more realistic clothes matching application
vector<Clothes> findShirts(const string filePath, int w, int colorful, string chosenGraphic, int chosenType) {
    /*
    Purpose: Create a vector representation of the Clothes objects in the user's closet file
    References: C++ documentation on std::stod function
    */
    vector<Clothes> closet;
    int lastType = chosenType;
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

        getline(parser, field, ',');
        hue = stod(field);
        getline(parser, field, ',');
        sat = stod(field);
        getline(parser, field, '\n');
        light = stod(field);

        if (chosenGraphic == "Any") {
            if (colorful) {
                if (weather == w && type == chosenType && light != 0 && light != 1) {
                    closet.push_back(Clothes(graphics, weather, type, hue, sat, light, ID));
                }
            } else {
                if (weather == w && type == chosenType && ( light == 0 || light == 1)) {
                    closet.push_back(Clothes(graphics, weather, type, hue, sat, light, ID));
                }
            }
        } else {
            if (colorful) {
                if (weather == w && graphics == chosenGraphic && type == chosenType && light != 0 && light != 1) {
                    closet.push_back(Clothes(graphics, weather, type, hue, sat, light, ID));
                }
            } else {
                if (weather == w && graphics == chosenGraphic && type == chosenType && ( light == 0 || light == 1)) {
                    closet.push_back(Clothes(graphics, weather, type, hue, sat, light, ID));
                }
            }
        }
    }
    if (closet.size() == 0) {
        throw(NO_MATCH_MESSAGE);
    }
    return closet;
}

void addPiece() {
    int type = 0;
    cout << "Is it a (0) Bottom or (1) Top piece?: ";
    cin >> type;

    while (!cin || type > 1 || type < 0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid Input. Is it a (0) Bottom or (1) Top piece?: ";
        cin >> type;
    }

    int weather = 0;
    cout << "Is this a (0) Fall/Winter [cold] or (1) Spring/Summer [warm] piece?: ";
    cin >> weather;

    while (!cin || weather > 1 || weather < 0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid Input. Is this a (0) Fall/Winter [cold] or (1) Spring/Summer [warm] piece?: ";
        cin >> weather;
    }

    string graphic = "None";
    if (type == SHIRTS) {
        cout << "What graphic? (Type 'None' for None)" << endl;
        getline(cin, graphic);
        getline(cin, graphic);
    }

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
}

void warmTopDescription(Clothes& piece) {
    string g = piece.getGraphic();
    cout << "---------------------Top Piece:----------------------------" << endl;
    if (g != "None") {
        cout << "Your " << piece.getGraphic() << " short-sleeve shirt" << " in H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << endl; 
    } else {
        cout << "Your " << "H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << " short-sleeve shirt" << endl; 
    }
}

void coldTopDescription(Clothes& piece) {
    string g = piece.getGraphic();
    cout << "---------------------Top Piece:----------------------------" << endl;
    if (g != "None") {
        cout << "Your " << piece.getGraphic() << " long-sleeve shirt" << " in H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << endl; 
    } else {
        cout << "Your " << "H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << " long-sleeve shirt" << endl; 
    }
}

void warmBottomDescription(Clothes& piece) {
    cout << "---------------------Bottom Piece:----------------------------" << endl;
    cout << "Your" << " H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << " shorts" << endl; 
}

void coldBottomDescription(Clothes& piece) {
    cout << "---------------------Bottom Piece:----------------------------" << endl;
    cout << "Your " << "H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << " pants" << endl; 
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
