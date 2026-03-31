#include <iostream>
#include <string>
#include <fstream>

#include "./../hpp/globalVars.hpp"
#include "./../hpp/colorDisplay.hpp"

using namespace std;

void printColoredRGB(int r, int g, int b, const std::string& text) {
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
