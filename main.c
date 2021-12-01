#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
//used for strings.
#include <string.h>

// wchar needed for wprint too show different symbols.
#include <wchar.h>

//used for clearing the screen!
#include <unistd.h>

//used for placing cursor in console
#include <windows.h>

#define SPECIAL_CHAR_INDICATOR_1 224
#define SPECIAL_CHAR_INDICATOR_2 0
void line(char);
void box(char*, int, int, int);
void updateOnPress(int);
void clear();
void ConsolePlacement(int, int);


void tick_for_state(int state, int input);
void tick_menu(int input);
void tick_overview(int input);


int read_character();
int map_non_ascii_char(char character);

enum keyname {
        //delete has been renamed "DELETE2" because its a preset from <windows.h>
        UP = 328, DOWN = 336, LEFT = 331, RIGHT = 333,
        PAGE_UP = 329, PAGE_DOWN = 337, DELETE2 = 339};

enum state {MENU, OVERVIEW, EDIT, SEARCH};
enum state current_state = MENU;
int program_is_running = 1;

//value so I can reach it elsewhere!
    int testvalue = 0;


int main(void) {  

    printf("ÆKLDFJÆSLKDFJÆSDKL");

    int character_pressed = '\0';
    while(program_is_running) {
        if(kbhit()) {
            /* Reads a character */
            character_pressed = read_character();
            printf("\n Key pressed = %c, with index of %i", character_pressed, character_pressed);
            /* Sends signal to the right state */
            tick_for_state(current_state, character_pressed);
            
            //function that can test and use charater_pressed!
            updateOnPress(character_pressed);

        }
    }
    


    return EXIT_SUCCESS;
}
//draws 117 charaters: line('charater');
void line(char c){
    for(int i = 0; i < 117; i++){
        wprintf(L"%c", c);
    }
    printf("\n");
}

// makes a menu button: box("text in center", 1/0);
void box(char* str, int isactive, int x, int y){
    //takes the lengh of the input and uses it    
    int strL = strlen(str);
    //Box top
    ConsolePlacement(x, y);
    printf("/");
    for(int i = 0; i < strL + 2; i++){
        if(isactive){
            printf("=");
        } else{
            printf("-");
        }        
    }
    printf("\\");
    printf("\n");
    ConsolePlacement(x, y + 1);
    printf("| ");
    
    
    //prints the text in the box
    for(int i = 0; i < strL; i++){
        printf("%c", str[i]);
    }
    
    printf(" |\n");
    ConsolePlacement(x, y + 2);
    //box bottom
    printf("\\");
    for(int i = 0; i < strL + 2; i++){
        if(isactive){
            printf("=");
        } else{
            printf("-");
        }
    }
    printf("/\n");
}

//testing function that takes charater input
void updateOnPress(int character_pressed){
    clear();
    //ConsolePlacement(10, 10);
    line('-');
    //TESTING IF BOX CAN BE ACTIVE
            if(character_pressed == 77 || character_pressed == 333){
                testvalue = 1;
            } else if(character_pressed == 75 || character_pressed == 331){
                testvalue = 0;
            }
            printf("\n");
            box("testbox", testvalue, 10, 10);
    //END OF TESTING ACTIVE BOX
    
}


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
void ConsolePlacement(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
}

void tick_for_state(int state, int input) {
    switch(state) {
        case MENU:
            tick_menu(input); break;
        case OVERVIEW:
            tick_menu(input); break;
        case EDIT:
            tick_menu(input); break;
        case SEARCH:
            tick_menu(input); break;
    }
}

void tick_menu(int input) {
    /*Title*/
    /*Menu elements using arrow keys to navigate*/
}
void tick_overview(int input) {
    /*TODO: Handle input*/
    /*Get timestamp*/
    /*Check if text is being written in search. If this is the case, append it to a char array*/

    /*Get column lable names*/
    /*Get entry data for rows taking into account what is written in the search box*/


    /*TODO: Draw UI*/
    /*Draw timestamp [maybe time of next iteration]*/
    /*Draw searchbox*/
    
    /*Draw column lables*/
    /*Draw rows*/
}

int read_character() {
    int read_char =_getch();
    if(read_char == SPECIAL_CHAR_INDICATOR_1 || read_char == SPECIAL_CHAR_INDICATOR_2) {
        read_char = _getch();
        read_char = map_non_ascii_char(read_char);
    }
    return read_char;
}
int map_non_ascii_char(char character) {
    return pow(2, sizeof(char)*8) + character;
}


