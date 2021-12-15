#include "../lib.h"


void initEditView(EditView *editView) {
    editView->editingIndex = 0;
    editView->editingProduct = NULL; }
void updateEditView(EditView *editView, Overview *overview, StateType *currentState, int input) {
    if(input == BACKSPACE) {
        /*Removes a character from the searchText*/
        if(editView->editingIndex == 0) {
            if(editView->searchTextLength >= 1){
                editView->searchTextLength--;
                editView->searchText[editView->searchTextLength] = '\0';
            } else {
                *currentState = MENU;
            }
        /* Ways of removing characters from the different kinds of data in the temp product */
        } else if(editView->editingIndex == 1) {
            editView->tempProduct.name[strlen(editView->tempProduct.name)-1] = '\0';
        } else if(editView->editingIndex == 2) {
            editView->tempProduct.startAmount /= 10;
        } else if(editView->editingIndex == 3) {
            editView->tempProduct.startPrice /= 10;
        } else if(editView->editingIndex == 4) {
            editView->tempProduct.expectedDelta /= 10;
        } else if(editView->editingIndex == 5) {
            editView->tempProduct.priceDelta /= 10;
        }
    } else if(input == ESCAPE) {
        
    } else if(input == UP) {
        
    } else if(input == DOWN) {

    } else if(input == LEFT) {
        /*The user can control what thing to be editing in*/
        if(editView->editingIndex > 0){
            editView->editingIndex--;
        }
    } else if(input == RIGHT) {
        if (editView->editingIndex <= 4){
            editView->editingIndex++;
        }
        
        
    } else if(input == ENTER){
        if(editView->editingIndex == 0) {
            if(editView->searchTextLength >= 1) {
                /* If there is text in the search bar, find a product with that name and mark it for editing */
                editView->editingProduct = findProduct(editView->searchText, overview->products, overview->productAmount);
                /* If it does not exist, create that product and find that for editing */
                if(editView->editingProduct == NULL) {
                    addProduct(overview, editView->searchText, 100, 100, 10, 10);
                    editView->editingProduct = findProduct(editView->searchText, overview->products, overview->productAmount);
                }
                /* Change a flag to show that we are editing */
                editView->editingIndex = 1;
                /* Transfer all the values of the product selected for editing into a temporary struct */
                strcpy(editView->tempProduct.name, editView->editingProduct->name);
                editView->tempProduct.startAmount = editView->editingProduct->startAmount;
                editView->tempProduct.startPrice = editView->editingProduct->startPrice;
                editView->tempProduct.priceDelta = editView->editingProduct->priceDelta;
                editView->tempProduct.expectedDelta = editView->editingProduct->expectedDelta;
            }
        } else {
            /* If the user is already editing and ENTER is pressed, transfer all the temporary values back into the permanent products*/
            /* There should probably be an 'are you sure' prompt in here somehow */
            strcpy(editView->editingProduct->name, editView->tempProduct.name);
            editView->editingProduct->startAmount = editView->tempProduct.startAmount;
            editView->editingProduct->startPrice = editView->tempProduct.startPrice;
            editView->editingProduct->priceDelta = editView->tempProduct.priceDelta;
            editView->editingProduct->expectedDelta = editView->tempProduct.expectedDelta;
            editView->editingIndex = 0;
            /* Sorts the product array with the new product introduced or with the new product name*/
            qsort(overview->products, overview->productAmount, sizeof(Product), compareProducts);
            saveProducts(overview->products, &overview->productAmount);
        }
    } else {
        /*Ways of adding numbers or text to the temporary product*/
        if(editView->editingIndex == 1){
            int maxLength = 0;
            maxLength = strlen(editView->tempProduct.name); 
            if(maxLength < 15){
                editView->tempProduct.name[strlen(editView->tempProduct.name)] = input;
                editView->tempProduct.name[strlen(editView->tempProduct.name)+1] = '\0';
            }
        } else if(editView->editingIndex == 2 && isNumber(input)){
            int intLength = 0;
            intLength = floor(log10(abs(editView->tempProduct.startAmount))) + 1;
            if (intLength < MAX_NUMBER_LENGTH){
                editView->tempProduct.startAmount *= 10;
                editView->tempProduct.startAmount += input-48; 
            }
            

        } else if(editView->editingIndex == 3 && isNumber(input)){
            int intLength = 0;
            intLength = floor(log10(abs(editView->tempProduct.startPrice))) + 1;
            if (intLength < MAX_NUMBER_LENGTH){
                editView->tempProduct.startPrice *= 10;
                editView->tempProduct.startPrice += input-48;
            }
            
        } else if(editView->editingIndex == 4 && isNumber(input)){
            int intLength = 0;
            intLength = floor(log10(abs(editView->tempProduct.expectedDelta))) + 1;
            if (intLength < MAX_NUMBER_LENGTH - 7){ // this is done to ensure that the user cant decriment with more than 2 digits.
                editView->tempProduct.expectedDelta *= 10;
                editView->tempProduct.expectedDelta += input-48;
            }
            
        } else if(editView->editingIndex == 5 && isNumber(input)){
            int intLength = 0;
            intLength = floor(log10(abs(editView->tempProduct.priceDelta))) + 1;
            if (intLength < MAX_NUMBER_LENGTH - 7){ // this is done to ensure that the user cant decriment with more than 2 digits.
                editView->tempProduct.priceDelta *= 10;
                editView->tempProduct.priceDelta += input-48;
            }
            
        } else if(editView->editingIndex < 1) {
            /*Adds a character to the searchText*/
            editView->searchText[editView->searchTextLength] = input;
            editView->searchText[editView->searchTextLength+1] = '\0';
            editView->searchTextLength++;
        }        
    }
}
void drawEditView(EditView *editView, Overview *overview, Product *product) {
    /*Draws temporary search box*/
    consolePlacement(20, 0);
    printf("Search: %s", editView->searchText);
    /*Draws the variable lables*/
    editviewUI();
    /*Draws a list of the first n products*/
    drawEditProducts(overview, editView);
    consolePlacement(0, 0);
    printf("check: %i", editView->editingIndex);

}
void drawEditProducts(Overview *overview, EditView *editView) {
    int i, y = 0;
    if(editView->editingIndex != 0) {
        editListItem(3, -1, editView->editingIndex, &editView->tempProduct); //-1 represents an unknown index
    }
    /* Cycles through all products */
    for(i = 0; i < overview->productAmount && y < ((38 - 7) / 3); i++) {
        Product *currentProduct = (overview->products+i);
        /* If searchText is equal to a substring of the name of the product, draw it */
        if(lowercaseStrstr(currentProduct->name, editView->searchText)) {
            y++;
            editListItem(4 + y * 3, y, 0, currentProduct);
        }
    }
}

Product *findProduct(char *name, Product *products, int productAmount) {
    int i;
    for(i = 0; i < productAmount; i++) {
        /* If searchText is equal to a substring of the name of the product, return it */
        
        if(lowercaseStrstr(products[i].name, name)) {
            return &products[i];
        }
    }
    return NULL;
}