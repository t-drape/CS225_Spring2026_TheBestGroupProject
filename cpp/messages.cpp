#include <iostream>
#include <string>

#include "./../hpp/messages.hpp"

using namespace std;

Statement::Statement() {};
Statement::Statement(string name, string middle, string start) {
    this->start = start;
    this->name = name;
    this->middle = middle;
}
ostream& operator<<(ostream& os, Statement& s) {
    // Welcome to the Algorithmic Outfit Selector, Name! 👕👖
    // Thank you for visiting the Algorithmic Outfit Selector, Name! 👕👖
    os << s.start << " " << s.middle << ", " << s.name << "! 👕👖" << endl;
    return os;
}

Messages::Messages(const string n, const string m, const string greeting, const string farewell) : name(n), middlePart(m) {
    welcome = Statement(n, middlePart, greeting);
    goodbye = Statement(n, middlePart, farewell);
}

Messages::~Messages() {
    cout << "Goodbye! Au Revoir!" << endl;
}