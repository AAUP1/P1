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
    product->numLength = 0;
    if(input == BACKSPACE) {
        /*Removes a character from the searchText*/
        if(overview->searchTextLength >= 1 || editingproduct == 1){
            if(editingproduct == 1){
                product->nameLength--;
                product->tempName[product->nameLength] = '\0';
            } else if(editingproduct > 1){
                product->numLength--;
                product->tempnum[product->numLength] = '\0';
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
        clearTName(product);
        editingproduct--;
    } else if(input == RIGHT) {
        clearTName(product);
        editingproduct++;
    } else if(input == ENTER){
        if(overview->searchTextLength >= 1){
            editingproduct = 1;
        }
    }else {
        
        if(editingproduct == 1){
            product->tempName[product->nameLength] = input;
            product->tempName[product->nameLength+1] = '\0';
            product->nameLength++;
        } else if(editingproduct > 1){
            product->tempnum[product->numLength] = input;
            product->tempnum[product->numLength+1] = '\0';
            product->numLength++;

        }else {
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
    ConsolePlacement(0, 0);
    printf("check: %i", editingproduct);
    if(editingproduct >= 1){
        editingMode(editView, overview, product);
               
    }    
}
void editingMode(EditView *editView, Overview *overview, Product *product){
    
    if(editingproduct == 1){
        ConsolePlacement(4, 8);
        printf("%s", product->tempName);
    } else if(editingproduct == 2){
        ConsolePlacement(20, 8);
        printf(" %s", product->tempnum);
    } else if(editingproduct == 3){
        ConsolePlacement(50, 8);
        printf(" %s", product->tempnum);
    } else if(editingproduct == 4){
        ConsolePlacement(75, 8);
        printf(" %s", product->tempnum);
    } else if(editingproduct == 5){
        ConsolePlacement(103, 8);
        printf(" %s", product->tempnum);
    }

    

}
/* clears tempName*/
void clearTName(Product *product){
    while(product->nameLength >= 1 && product->numLength >= 1){
        product->nameLength--;
        product->tempName[product->numLength] = '\0';
        product->numLength--;
        product->tempnum[product->numLength] = '\0';
    }
}