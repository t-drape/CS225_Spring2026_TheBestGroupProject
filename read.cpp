#include <iostream>
#include <fstream>

using namespace std;

int main() {
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