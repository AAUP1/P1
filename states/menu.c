#include "menu.h"
#include "../terminal.h"
#include <stdio.h>
#include "state.h"

#define EXIT_BUTTON_INDEX 3

void initMenu(Menu* menu) {
    int i;
    /* Initializes all the boxes in the menu */
    initBox(&(menu->boxes[0]), 10, 10, "Overview");
    initBox(&(menu->boxes[1]), 15, 15, "Edit Products");
    initBox(&(menu->boxes[2]), 20, 20, "Add Products");
    initBox(&(menu->boxes[3]), 25, 25, "Exit");
    menu->box_amount = 4;
    for(i = 0; i < menu->box_amount; i++) {
        menu->boxes[i].active = i == 0;
    }
}
void updateMenu(Menu* menu, StateType *currentState, int *programRunning, int input) {
    int i;
    
    /* If the user inputs space, make a selection */
    if(input == ENTER) {
        /* If the active box is the exit box, stop the program */
        if(menu->activeBoxIndex == EXIT_BUTTON_INDEX) {
            *programRunning = 0;
            return;
        }
        /* If the program did not stop, change the state index to the active box index */
        *currentState = 1+menu->activeBoxIndex;
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
    drawStructBox(&(menu->boxes[3]));
}