#include <iostream>
#include <fstream>
#include <cstdlib>

/*
Sources of Help:
Grok for seeing how to implement python in a C++ program
*/

using namespace std;

int main() {
    std::system("python3 color_picker.py");

    ifstream fin("chosen_color.txt");
    string r;
    fin >> r;
    string g;
    fin >> g;
    string b;
    fin >> b;
    fin.close();
    cout << "R:" << r << " G:" << g << " B:" << b<< endl;
}