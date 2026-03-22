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
    vector<int> colors(3);
    std::system("python3 color_picker.py");
    ifstream fin("chosen_color.txt");
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

// int main() {
//     std::system("python3 color_picker.py");

//     ifstream fin("chosen_color.txt");
//     string r;
//     fin >> r;
//     string g;
//     fin >> g;
//     string b;
//     fin >> b;
//     fin.close();
//     cout << "R:" << r << " G:" << g << " B:" << b<< endl;
// }