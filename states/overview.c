#include <stdio.h>
#include <string.h>

/* overview.h also includes product.h */
#include "overview.h"
#include "../terminal.h"
#include "state.h"
#include "../loadSave.h"

/* Overview Functions */
void initOverview(Overview *overview) {
    loadProducts(overview->products, &overview->productAmount);

    overview->searchTextLength = 0;
    overview->searchText[0] = '\0';
}
void updateOverview(Overview *overview, StateType* currentState, int input) {
    if(input == BACKSPACE) {
        /*Removes a character from the searchText*/
        overview->searchTextLength--;
        overview->searchText[overview->searchTextLength] = '\0';
    } else if(input == UP) {
        /*Adds a product and saves the new selection*/
        addProduct(overview);
        saveProducts(overview->products, &(overview->productAmount));
    } else if(input == DOWN) {

    } else if(input == LEFT) {
        
    } else if(input == RIGHT) {

    } else if(input == DEL) {
        /*Removes a product and saves the new selection*/
        removeProduct(overview->searchText, overview);
        saveProducts(overview->products, &(overview->productAmount));
    } else {
        /*Adds a character to the searchText*/
        overview->searchText[overview->searchTextLength] = input;
        overview->searchText[overview->searchTextLength+1] = '\0';
        overview->searchTextLength++;
    }
    
    /*TODO: Handle the time of day*/
}
void drawOverview(Overview *overview) {
    /*Draws temporary search box*/
    printf("Search: %s", overview->searchText);
    /*Draws the variable lables*/
    overviewUI();
    /*Draws a list of the first n products*/
    drawProducts(overview);

}
void drawProducts(Overview *overview) {
    int i, y = 0;
    /* Cycles through all products */
    for(i = 0; i < overview->productAmount && y < ((38 - 7) / 3); i++) {
        Product *currentProduct = (overview->products+i);
        /* If searchText is equal to a substring of the name of the product, draw it */
        if(strstr(currentProduct->name, overview->searchText)) {
            y++;
            listItem(4 + y * 3, y, currentProduct->name, currentProduct->currentAmount, 
                currentProduct->startPrice, currentProduct->currentPrice, currentProduct->amountDecrement);
        }
    }
}

void addProduct(Overview* overview) {
    Product *newProduct = &((overview->products)[overview->productAmount]);
    newProduct->name = "Dont";
    overview->productAmount++;
}
void removeProduct(char *name, Overview *overview) {
    int found = 0;
    for(int i = 0; i < overview->productAmount; i++) {
        /* If the product has the same name as what should be removed, mark it as found */
        if(!strcmp(overview->products[i].name, name)) {
            found = 1;
        }
        /* If the product has been found, move the proceding products one step down over the product that should be removed */
        if(found) {
            if(i == overview->productAmount-1) {
                //Do nothing if we have reached the end of the array, as the length will just be shortened
            } else {
                //Moves the products one space down
                overview->products[i] = overview->products[i+1];
            }
        }
    }
    if(found) {
        overview->productAmount--;
    }
}