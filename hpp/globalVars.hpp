#include <string>

enum {SHORTS, SHIRTS};
enum {COLD, WARM};
enum {NOT_COLORFUL, COLORFUL};

using namespace std;

const string CLOSET_PATH = "./../Closet.csv";
const string FILE_BAD_MESSAGE = "Error opening the file.\n";
const string INSUFFICENT_CLOTHES_MESSAGE = "Sorry, you haven't added enough pieces to your closet yet. Add some more pieces then try again.\n";
const string NO_MATCH_MESSAGE = "Sorry, you don't own clothes matching that description. Please try again.\n";

const string TSHIRT_PATH = "./../displayFigures/tshirt.txt";
const string SHORTS_PATH = "./../displayFigures/shorts.txt";
const string LONG_SLEEVE_SHIRT_PATH = "./../displayFigures/LongSleeveTshirt.txt";
const string PANT_PATH = "./../displayFigures/pants.txt";