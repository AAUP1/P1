#include "editview.h"
#include "state.h"
#include "../terminal.h"
#include "../UI.h"
//#include "overview.h"
#include <stdio.h>

void initEditView(EditView *editView) {

}
void updateEditView(EditView *editView, StateType *currentState, int input) {
    
    if(input == BACKSPACE) {
        *currentState = MENU;
    }
    /*if(asd == 0){
        
    }*/
}
void drawEditView(EditView *editView, Overview *overview) {
    /*Draws temporary search box*/
    ConsolePlacement(20, 0);
    printf("Search: %s", overview->searchText);
    /*Draws the variable lables*/
    overviewUI();
    /*Draws a list of the first n products*/
    drawProducts(overview);

}
