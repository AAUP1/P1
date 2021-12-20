#include "lib.h"

StateType currentState = MENU;

void initStates();

/* State selecting function */
void updateState(int state, int input);
void redrawState(int state);

int programRunning = 1;

Menu menu;
Overview overview;
EditView editView;
Product product;

/* Initializes everything and starts the primary and only loop in the program */
int main(void) {  
    int characterPressed = '\0';

    initStates();
    /* Initial draw to the screen before any input is given */
    redrawState(currentState);
    controls(currentState);
    while(programRunning) {
        if(kbhit()) {
            /* Reads a character */
            characterPressed = readCharacter();
            /* Sends signal to the right state */
            updateState(currentState, characterPressed);
            redrawState(currentState);
            controls(currentState);            
        }
    } 

    return EXIT_SUCCESS;
}

/* STATE FUNCTIONS #BEGIN */
/* Initializes all the structures that represent states and the structures within them */
void initStates() {

    /* Initializes the menu and its contents*/
    initMenu(&menu);

    /* Initializes overview and its contents */
    initOverview(&overview);

    /* Initializes editView and its contents */
    initEditView(&editView);
}

/* Updates a state with an input parameter */
void updateState(int state, int input) {
    switch(state) {
        case MENU:
            updateMenu(&menu, &currentState, &programRunning, input);
            break;
        case OVERVIEW:
            updateOverview(&overview, &currentState, input, &product);
            break;
        case EDIT:
            updateEditView(&editView, &overview, &currentState, input);
            break;
        case SEARCH:
            updateMenu(&menu, &currentState, &programRunning, input); 
            break;
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
            drawEditView(&editView, &overview, &product);
            break;
        /*case SEARCH:
            drawEditView(&editView, &overview, &product); /* DIS IS NOT SEARCH!!!
                                        no shit sherlock it points to editView :) - Bjørn*/
    }
}
/*

THINGS TO CHECK IF YOU FORGOT:
    * Creating a new state for the state machine requires following elements to be implemented:
        1. A struct representing the state with objects associated with this state
        2. An init function that initializes all variables and structs inside the state struct
        3. An update function that passes through an input character
        4. A draw function that types the text into the terminal
        5. Add this state entry to initStates, updateStates and drawStates
        !!! See other states for reference
*/