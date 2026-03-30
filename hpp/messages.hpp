#include <string>

using namespace std;

class Statement {
    private:
        string name;
        string middle;
        string start;
    public:
        Statement();
        Statement(string name, string middle, string start);
        friend ostream& operator<<(ostream& os, Statement& s);
};

class Messages {
    private:
        const string name;
        const string middlePart;
    public:
        Statement welcome;
        Statement goodbye;
        Messages(const string n, const string m, const string greeting, const string farewell);
        ~Messages();
};