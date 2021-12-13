#define SPECIAL_CHAR_INDICATOR_1 224
#define SPECIAL_CHAR_INDICATOR_2 0

enum Keyname {
        //NOTE: delete has been renamed "DEL" because its a preset from <windows.h>
        UP = 328, DOWN = 336, LEFT = 331, RIGHT = 333,
        PAGE_UP = 329, PAGE_DOWN = 337, HOME = 327, END = 335, 
        DEL = 339, SPACE = 32, BACKSPACE = 8, ENTER = 13, ESCAPE = 27};
typedef enum Keyname Keyname;

void line(char);
void clear();
void consolePlacement(int, int);


int readCharacter();
int mapNonASCIICharacter(char character);
int isNumber(int input);