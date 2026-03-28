#include <iostream>
#include <climits>

#include "./../hpp/read.hpp"
#include "./../hpp/clothes.hpp"
#include "./../hpp/colorDisplay.hpp"


using namespace std;

void warmTopDescription(Clothes& piece) {
    cout << "---------------------Top Piece:----------------------------" << endl;
    cout << "Your " << piece.getGraphic() << " short-sleeve shirt" << " in H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << endl; 
}

void coldTopDescription(Clothes& piece) {
    cout << "---------------------Top Piece:----------------------------" << endl;
    cout << "Your " << piece.getGraphic() << " long-sleeve shirt" << " in H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << endl; 
}

void warmBottomDescription(Clothes& piece) {
    cout << "---------------------Bottom Piece:----------------------------" << endl;
    cout << "Your" << " H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << " shorts" << endl; 
}

void coldBottomDescription(Clothes& piece) {
    cout << "---------------------Bottom Piece:----------------------------" << endl;
    cout << "Your " << "H=" << piece.getHue() << ", S=" << piece.getSaturation() << ", L=" << piece.getLightness() << " pants" << endl; 
}


void coldBottomDescription() {

}

// Function Definition from read.hpp
vector<int> getColors() {
    vector<int> colors;
    std::system("python3 ./../colorPicker/color_picker.py");
    ifstream fin("./../colorPicker/chosen_color.txt");
    string r;
    fin >> r;
    string g;
    fin >> g;
    string b;
    fin >> b;
    colors.push_back(stoi(r));
    colors.push_back(stoi(g));
    colors.push_back(stoi(b));
    return colors;
}

void print_colored_rgb(int r, int g, int b, const std::string& text) {
    // Set foreground color using RGB values
    std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";
    std::cout << text;
    // Reset color to default
    std::cout << "\033[0m" << std::endl;
}

string longSleeveShirt() {
    ifstream inputFile(LONG_SLEEVE_SHIRT_PATH);
    if (!inputFile.is_open()) {
        return "Error: Unable to open file";
    }
    string line, content;
    while (getline(inputFile, line)) {
        content += line + "\n";
    }
    return content;
}

string tshirt() {
    ifstream inputFile(TSHIRT_PATH);
    if (!inputFile.is_open()) {
        return "Error: Unable to open file";
    }
    string line, content;
    while (getline(inputFile, line)) {
        content += line + "\n";
    }
    return content;
}

string pants() {
    ifstream inputFile(PANT_PATH);
    if (!inputFile.is_open()) {
        return "Error: Unable to open file";
    }
    string line, content;
    while (getline(inputFile, line)) {
        content += line + "\n";
    }
    return content;
}

string shorts() {
    ifstream inputFile(SHORTS_PATH);
    if (!inputFile.is_open()) {
        return "Error: Unable to open file";
    }
    string line, content;
    while (getline(inputFile, line)) {
        content += line + "\n";
    }
    return content;
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


// Function Definition from clothes.hpp
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


int main(){
    srand(time(NULL));
    string closetName;
    string addToCloset = "hello";
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
        addPiece();
    }
    else if(addToCloset == "no"){
        try {
                vector<Clothes> fullCloset = createCloset(CLOSET_PATH);

                cout<<"Welcome to the outfit selector "<<closetName<<" "<<endl;
                cout<<"There will be a couple questions to help determine a great outfit!"<<endl;

                cout<<"What is the weather looking like today? Please Input Fahrenheit value: "<<endl;
                cin>>weather;
                if (weather >=70){
                    weather = WARM;
                }
                else if(weather < 70){
                    weather = COLD;
                } 

                cout<<"Are you looking for a colorful shirt today?: yes or no"<<endl;
                cin>>colorful;
                int c = NOT_COLORFUL;
                if (colorful =="yes"){
                    c = COLORFUL;
                }

                cout<<"Which graphic shirt would you like? (Type 'None' for None)"<<endl;
                cin>>graphic;

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
                        print_colored_rgb(t->getRedValue(), t->getGreenValue(), t->getBlueValue(), tshirt());
                        warmBottomDescription(bottoms[chosenBottomIndex]);
                        print_colored_rgb(b->getRedValue(), b->getGreenValue(), b->getBlueValue(), shorts());
                    } else {
                        coldTopDescription(top);
                        print_colored_rgb(t->getRedValue(), t->getGreenValue(), t->getBlueValue(), longSleeveShirt());
                        coldBottomDescription(bottoms[chosenBottomIndex]);
                        print_colored_rgb(b->getRedValue(), b->getGreenValue(), b->getBlueValue(), pants());
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
