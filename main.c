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

enum Keyname {
        //delete has been renamed "DEL" because its a preset from <windows.h>
        UP = 328, DOWN = 336, LEFT = 331, RIGHT = 333,
        PAGE_UP = 329, PAGE_DOWN = 337, DEL = 339, SPACE = 32, BACKSPACE = 8};
typedef enum Keyname Keyname;
enum StateType {MENU, OVERVIEW, EDIT, SEARCH};
typedef enum StateType StateType;
enum StateType current_state = MENU;

/* On-screen object structs */
struct Box {
    int x, y;
    char* text;
    int active;
};
typedef struct Box Box;

/* State structs */
struct Menu {
    int box_amount;
    struct Box boxes[3];
    int activeBoxIndex;
};
typedef struct Menu Menu;
struct Overview {
    Box testBox;
};
typedef struct Overview Overview;
struct EditView {
    Box testBox;
};
typedef struct EditView EditView;

void initStates();

/* Menu functions */
void initMenu(Menu* menu, int box_amount, int activeBoxIndex);
void updateMenu(Menu* menu, int input);
void drawMenu(Menu* menu);

/* Overview functions */
void initOverview(Overview* overview);
void updateOverview(Overview* overview, int input);
void drawOverview(Overview* overview);

/* EditView functions */
void initEditView(EditView* edit_view);
void updateEditView(EditView* edit_view, int input);
void drawEditView(EditView* edit_view);

/* State selecting function */
void updateState(int state, int input);
void redrawState(int state);

/* Box functions */
void initBox(Box* box, int x, int y, char* text);
void drawBox(char*, int, int, int);
void drawStructBox(Box* box);

/* Functions for automating live character input */
int readCharacter();
int mapNonASCIICharacter(char character);

/* General terminal functions */
void line(char);
void clear();
void ConsolePlacement(int, int);

int program_is_running = 1;

//value so I can reach it elsewhere!
    int testvalue = 0;

Menu menu;
Overview overview;
EditView editView;

/* Initializes everything and starts the primary and only loop in the program */
int main(void) {  
    int character_pressed = '\0';
    
    initStates();

    /* Initial draw to the screen before any input is given */
    redrawState(current_state);
    while(program_is_running) {
        if(kbhit()) {
            /* Reads a character */
            character_pressed = readCharacter();
            //printf("\n Key pressed = %c, with index of %i", character_pressed, character_pressed);

            /* Sends signal to the right state */
            updateState(current_state, character_pressed);
            redrawState(current_state);

            //function that can test and use charater_pressed!
            //updateOnPress(character_pressed);

        }
    } 

    return EXIT_SUCCESS;
}

/* STATE FUNCTIONS #BEGIN */
/* Initializes all the structures that represent states and the structures within them */
void initStates() {
    /*PROGRAM ACTS WEIRD WHEN I PUT INITIALIZERS IN THIS SEPARATE FUNCTION*/

    /* Initializes the menu and its contents*/
    initBox(&(menu.boxes[0]), 10, 10, "Overview");
    initBox(&(menu.boxes[1]), 20, 20, "Edit/Add");
    initBox(&(menu.boxes[2]), 30, 30, "Exit");
    initMenu(&menu, 3, 0);

    /* Initializes overview and its contents */
    initBox(&(overview.testBox), 10, 10, "Now you are in the overview");
    initOverview(&overview);

    /* Initializes editView and its contents */
    initBox(&(editView.testBox), 10, 10, "Now you are editing products");
    initEditView(&editView);
}

/* Updates a state with an input parameter */
void updateState(int state, int input) {
    switch(state) {
        case MENU:
            updateMenu(&menu, input);
            break;
        case OVERVIEW:
            updateOverview(&overview, input);
            break;
        case EDIT:
            updateEditView(&editView, input);
            break;
        case SEARCH:
            updateMenu(&menu, input); break;
    }
}
/* Redraws the state in the terminal */
void redrawState(int state) {
    clear();
    switch(state) {
        case MENU:
            drawMenu(&menu);
            break;
        case OVERVIEW:
            drawOverview(&overview);
            break;
        case EDIT:
            drawEditView(&editView);
            break;
        case SEARCH:
            drawEditView(&editView); /* DIS IS NOT SEARCH!!!
                                        no shit sherlock it points to editView :) - Bjørn*/
    }
}

/* Menu functions */
void initMenu(Menu* menu, int box_amount, int activeBoxIndex) {
    int i;
    /* Initializes all the boxes in the menu */
    menu->box_amount = box_amount;
    for(i = 0; i < box_amount; i++) {
        menu->boxes[i].active = i == activeBoxIndex;
    }
}
void updateMenu(Menu* menu, int input) {
    int i;
    
    /* If the user inputs space, make a selection */
    if(input == SPACE) {
        /* If the active box is the exit box, stop the program */
        if(menu->activeBoxIndex == 2) {
            program_is_running = 0;
            return;
        }
        /* If the program did not stop, change the state index to the active box index */
        current_state = 1+menu->activeBoxIndex;
        return;
    }

    /* Pressing up and down changes the active box, looping around */
    if(input == DOWN) {
        menu->activeBoxIndex++;
        if(menu->activeBoxIndex >= menu->box_amount) {
            menu->activeBoxIndex = 0;
        }
    } else if(input == UP) {
        menu->activeBoxIndex--;
        if(menu->activeBoxIndex < 0) {
            menu->activeBoxIndex = menu->box_amount-1;
        }
    }
    /* Applies the changes to the boxes on by one */
    for(i = 0; i < menu->box_amount; i++) {
        if(i == menu->activeBoxIndex) {
            menu->boxes[i].active = 1;
        } else {
            menu->boxes[i].active = 0;
        }
    }
}
void drawMenu(Menu* menu) {
    /* Draws an extremely cool title text */
    printf(" ________  ________  _______   ________  ________      \n");
    printf("|\\   __  \\|\\   __  \\|\\  ___ \\ |\\   __  \\|\\   ___ \\     \n");
    printf("\\ \\  \\|\\ /\\ \\  \\|\\  \\ \\   __/|\\ \\  \\|\\  \\ \\  \\_|\\ \\    \n");
    printf(" \\ \\   __  \\ \\   _  _\\ \\  \\_|/_\\ \\   __  \\ \\  \\ \\\\ \\   \n");
    printf("  \\ \\  \\|\\  \\ \\  \\\\  \\\\ \\  \\_|\\ \\ \\  \\ \\  \\ \\  \\_\\\\ \\  \n");
    printf("   \\ \\_______\\ \\__\\\\ _\\\\ \\_______\\ \\__\\ \\__\\ \\_______\\ \n");
    printf("    \\|_______|\\|__|\\|__|\\|_______|\\|__|\\|__|\\|_______| \n");
    /* Draws all the boxes */

    drawStructBox(&(menu->boxes[0]));
    drawStructBox(&(menu->boxes[1]));
    drawStructBox(&(menu->boxes[2]));
}

/* Overview Functions */
void initOverview(Overview *overview) {

}
void updateOverview(Overview *overview, int input) {
    if(input == BACKSPACE) {
        current_state = MENU;
    }
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
void drawOverview(Overview *overview) {
    drawStructBox(&(overview->testBox));
}

/* EditView functions */
void initEditView(EditView *editView) {

}
void updateEditView(EditView *editView, int input) {
    if(input == BACKSPACE) {
        current_state = MENU;
    }
}
void drawEditView(EditView *editView) {
    drawStructBox(&(editView->testBox));
}
/* STATE FUNCTIONS #END */

/* ON-SCREEN OBJECT FUNCTIONS #BEGIN */
// Initializes a box object with the given values
void initBox(Box* box, int x, int y, char* text) {
    box->x = x;
    box->y = y;
    box->text = text;
    box->active = 0;
}
// makes a menu button: drawBox("text in center", 1/0);
void drawBox(char* str, int isactive, int x, int y){
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
    /* Draws arrow behind box if it is active */
    if(isactive) {
        ConsolePlacement(x - 5, y + 1);
        printf("--->");
    }
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
// Draws a box using the struct that represents a box
void drawStructBox(Box* box) {
    drawBox(box->text, box->active, box->x, box->y);
}
//draws 117 charaters: line('charater');
void line(char c){
    for(int i = 0; i < 117; i++){
        wprintf(L"%c", c);
    }
    printf("\n");
}
/* ON-SCREEN OBJECT FUNCTIONS #END */

/* CHARACTER INPUT FUNCTIONS #BEGIN */
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
/* CHARACTER INPUT FUNCTIONS #END */

/* CONSOLE FUNCTIONS #BEGIN */
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
/* CONSOLE FUNCTIONS #END */


/*

KNOWN ISSUES:
    * [[[FIXED]]]   When putting inizializers in a separate function, the program crashes

*/

/*

TODO:
    * [[[DONE]]]   Change all variable names containing "selected" to "active"

*/

/*

THINGS TO CHECK IF YOU FORGOR:
    * Creating a new state for the state machine requires following elements to be implemented:
        1. A struct representing the state with objects associated with this state
        2. An init function that initializes all variables and structs inside the state struct
        3. An update function that passes through an input character
        4. A draw function that types the text into the terminal
        5. Add this state entry to initStates, updateStates and drawStates
        !!! See other states for reference

*/