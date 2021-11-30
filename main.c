#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>
// wchar needed for wprint too show different symbols.
#include <wchar.h>
#define SPECIAL_CHAR_INDICATOR 224
void line(char);
void box(char*);

void tick_for_state(int state, int input);
void tick_menu(int input);
void tick_overview(int input);


int read_character();
int map_non_ascii_char(char character);

enum keyname {
        UP = 328, DOWN = 336, LEFT = 331, RIGHT = 333,
        PAGE_UP = 329, PAGE_DOWN = 337, DELETE = 339};

enum state {MENU, OVERVIEW, EDIT, SEARCH};
enum state current_state = MENU;
int program_is_running = 1;


int main(void) {  
    line('-');
    box("HERPY DERP");
    
    int character_pressed = '\0';
    while(program_is_running) {
        if(kbhit()) {
            /* Reads a character */
            character_pressed = read_character();
            printf("\n Key pressed = %c, with index of %i", character_pressed, character_pressed);
            /* Sends signal to the right state */
            tick_for_state(current_state, character_pressed);
        }
    }
    return EXIT_SUCCESS;
}
//line function that will draw a 117 character long line
void line(char c){
    for(int i = 0; i < 117; i++){
        wprintf(L"%c", c);
    }
    printf("\n");
}

// makes a menu button with text inside
void box(char* str){
    //takes the lengh of the input and uses it    
    int strL = strlen(str);
    //Box top
    printf("/");
    for(int i = 0; i < strL + 2; i++){
        printf("-");
    }
    printf("\\\n| ");
    
    //prints the text in the box
    for(int i = 0; i < strL; i++){
        printf("%c", str[i]);
    }
    
    printf(" |\n");

    printf("\\");
    for(int i = 0; i < strL + 2; i++){
        printf("-");
    }
    printf("/");
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
    if(read_char == SPECIAL_CHAR_INDICATOR) {
        read_char = _getch();
        read_char = map_non_ascii_char(read_char);
    }
    return read_char;
}
int map_non_ascii_char(char character) {
    return pow(2, sizeof(char)*8) + character;
}


