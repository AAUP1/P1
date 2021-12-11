#include "editview.h"
#include "state.h"
#include "../terminal.h"
#include "../UI.h"
//#include "overview.h"
#include <stdio.h>
#include "../loadSave.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int editingproduct = 0;
//char chartest[32];


void initEditView(EditView *editView) {

}
void updateEditView(EditView *editView, StateType *currentState, Overview *overview, int input, Product *product) {
    
    if(input == BACKSPACE) {
        /*Removes a character from the searchText*/
        if(overview->searchTextLength >= 1 || editingproduct == 1){
            if(editingproduct == 1){
                product->nameLength--;
                product->tempName[product->nameLength] = '\0';
            } else{
                overview->searchTextLength--;
                overview->searchText[overview->searchTextLength] = '\0';
            }            
        } else if(editingproduct == 0) {
            *currentState = MENU;
        }
    }
    else if(input == UP) {
        
    } else if(input == DOWN) {

    } else if(input == LEFT) {
        editingproduct = 1;
    } else if(input == RIGHT) {
        clearTName(product);
        editingproduct = 0;
    } else if(input == ENTER){
        if(overview->searchTextLength >= 1){
            editingproduct = 1;

        }
    }else {
        
        if(editingproduct == 1){
            product->tempName[product->nameLength] = input;
            product->tempName[product->nameLength+1] = '\0';
            product->nameLength++;
        } else {
            /*Adds a character to the searchText*/
            overview->searchText[overview->searchTextLength] = input;
            overview->searchText[overview->searchTextLength+1] = '\0';
            overview->searchTextLength++;
        }        
    }
}
void drawEditView(EditView *editView, Overview *overview, Product *product) {
    
    /*Draws temporary search box*/
    ConsolePlacement(20, 0);
    printf("Search: %s", overview->searchText);

    /*Draws the variable lables*/
    overviewUI();
    /*Draws a list of the first n products*/
    drawProducts(overview);
    if(editingproduct == 1){
        editingMode(editView, overview, product);
               
    }    
}
void editingMode(EditView *editView, Overview *overview, Product *product){
    ConsolePlacement(4, 8);
    printf("%s", product->tempName);
    

}
void clearTName(Product *product){
    while(product->nameLength >= 1){
        product->nameLength--;
        product->tempName[product->nameLength] = '\0';
    }
}