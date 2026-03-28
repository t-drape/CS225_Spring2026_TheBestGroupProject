#include <iostream>
#include <string>
#include <fstream>

#include "./../hpp/helper.hpp"

using namespace std;

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


int main() {
    
    // Print "Hello, World!" in a shade of orange (RGB: 255, 165, 0)
    print_colored_rgb(255, 165, 0, "Hello, World! This is orange text.");

    // Print "Success" in a shade of green (RGB: 0, 128, 0)
    print_colored_rgb(0, 128, 0, "Success in green.");
    print_colored_rgb(0,128,0, longSleeveShirt());
    print_colored_rgb(0,128,0, pants());

    

    return 0;
}
