#include "editview.h"
#include "state.h"
#include "../terminal.h"
#include "../UI.h"
//#include "overview.h"
#include <stdio.h>
#include "../loadSave.h"
int editingproduct = 0;
char chartest[32];
void initEditView(EditView *editView) {

}
void updateEditView(EditView *editView, StateType *currentState, Overview *overview, int input) {
    
    if(input == BACKSPACE) {
        /*Removes a character from the searchText*/
        if(overview->searchTextLength >= 1){
            if(editingproduct == 0){
                overview->searchTextLength--;
                overview->searchText[overview->searchTextLength] = '\0';
            }            
        } else {
            *currentState = MENU;
        }
    }
    else if(input == UP) {
        
    } else if(input == DOWN) {

    } else if(input == LEFT) {
        
    } else if(input == RIGHT) {
        editingproduct = 0;
    } else if(input == ENTER){
        if(overview->searchTextLength >= 1){
            editingproduct = 1;                    
        }
    }else {
        
        if(editingproduct == 1){
            
        } else {
            /*Adds a character to the searchText*/
            overview->searchText[overview->searchTextLength] = input;
            overview->searchText[overview->searchTextLength+1] = '\0';
            overview->searchTextLength++;
        }        
    }
}
void drawEditView(EditView *editView, Overview *overview) {
    
    /*Draws temporary search box*/
    ConsolePlacement(20, 0);
    printf("Search: %s", overview->searchText);

    /*Draws the variable lables*/
    overviewUI();
    /*Draws a list of the first n products*/
    drawProducts(overview);
    if(editingproduct == 1){

        ConsolePlacement(4, 8);
        //printf
    }    
}
