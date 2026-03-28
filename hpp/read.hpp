/*
Purpose: 
This header file defines helper functions that run the Python script for the color-picking GUI.
*/

#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

/*
Sources of Help:
Grok for seeing how to implement python in a C++ program
*/

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