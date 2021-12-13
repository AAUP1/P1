#include "lib.h"

#define SPECIAL_CHAR_INDICATOR_1 224
#define SPECIAL_CHAR_INDICATOR_2 0

/* clear function to clear console on all OS
clear will move cursor back to (0,0) in console*/
void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
// Places cursor at a specific x, y coordinate in the terminal
void ConsolePlacement(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}


// Checks if a character is being pressed and returns a correlating integer index
int readCharacter() {
    int read_char =_getch();
    if(read_char == SPECIAL_CHAR_INDICATOR_1 || read_char == SPECIAL_CHAR_INDICATOR_2) {
        read_char = _getch();
        read_char = mapNonASCIICharacter(read_char);
    }
    return read_char;
}
// If a character is not in the ASCII character table, it will be mapped outside of the char datasize
int mapNonASCIICharacter(char character) {
    return pow(2, sizeof(char)*8) + character;
}


