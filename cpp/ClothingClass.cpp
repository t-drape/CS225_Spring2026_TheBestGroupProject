#include <iostream>
#include <string>
using namespace std;

class Clothing {
private:
    string type;   // "Shirt" "Pants" "long sleeve"
 //   string size;   // S, M, L, etc.

public:

    Clothing() {
        type = "Shirt";
  //      size = "M";
    }

    Clothing(string t, string s) {
        type = t;
 //       size = s;
    }

    void setType(string t) { type = t; }
  //  void setSize(string s) { size = s; }

    string getType() const { return type; }
  //  string getSize() const { return size; }

    void display() const {
        cout << "Type: " << type << endl;
      //  cout << "Size: " << size << endl;
    }
};
