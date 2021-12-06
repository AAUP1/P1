#include "overview.h"
#include "../terminal.h"
#include "state.h"

/* Overview Functions */
void initOverview(Overview *overview) {
    initBox(&(overview->testBox), 10, 10, "Now you are in the overview");
}
void updateOverview(Overview *overview, StateType* currentState, int input) {
    if(input == BACKSPACE) {
        *currentState = MENU;
    } else if(input == UP) {

    } else if(input == DOWN) {

    } else if(input == LEFT) {
        
    } else if(input == RIGHT) {

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