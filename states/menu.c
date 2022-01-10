#include "../lib.h"



void initMenu(Menu* menu) {
    menu->activeBoxIndex = 0;
    menu->box_amount = 3;
}
void updateMenu(Menu* menu, StateType *currentState, int *programRunning, int input) {
    /* If the user inputs space, make a selection */
    if(input == ENTER) {
        /* If the active box is the exit box, stop the program */
        if(menu->activeBoxIndex == EXIT_INDEX) {
            *programRunning = 0;
            return;
        }
        /* If the program did not stop, change the state index to the active box index */
        *currentState = menu->activeBoxIndex;
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
}
void drawMenu(Menu* menu) {
    drawtitle();
    /* Draws all the boxes */
    drawBox("Overview", menu->activeBoxIndex == OVERVIEW, 10, 10);
    drawBox("Edit Products", menu->activeBoxIndex == EDIT, 15, 15);
    drawBox("Exit", menu->activeBoxIndex == EXIT_INDEX, 20, 20);
    
}