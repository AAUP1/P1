#include <stdio.h>
#include <string.h>

/* overview.h also includes product.h */
#include "overview.h"
#include "../terminal.h"
#include "state.h"
#include "../loadSave.h"

/* Overview Functions */
void initOverview(Overview *overview) {
    FILE *file = fopen("products.txt", "r");
    int productAmount = countLinesInFile(file);
    overview->productAmount = productAmount;
    fclose(file);
    loadProducts(overview->products, &productAmount);

    overview->searchTextLength = 0;
    overview->searchText[0] = '\0';
}
void updateOverview(Overview *overview, StateType* currentState, int input) {
    if(input == BACKSPACE) {
        overview->searchTextLength--;
        overview->searchText[overview->searchTextLength] = '\0';
    } else if(input == UP) {
        addProduct(overview);
        saveProducts(overview->products, &(overview->productAmount));
    } else if(input == DOWN) {

    } else if(input == LEFT) {
        
    } else if(input == RIGHT) {

    } else {
        overview->searchText[overview->searchTextLength] = input;
        overview->searchText[overview->searchTextLength+1] = '\0';
        overview->searchTextLength++;
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
    //drawBox("Now you are in the overview", 0, 10, 10);
    printf("%s", overview->searchText);
    int i;
    overviewUI();
    drawProducts(overview);

}
void drawProducts(Overview *overview) {
    int i, y = 0;
    for(i = 0; i < overview->productAmount & i < ((38 - 4) / 3); i++) {
        Product *currentProduct = (overview->products+i);
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
    /*int found
    for(int i = 0; i < overview->productAmount; i++) {
        if(overview->products->name) {

        }
    }*/
}