#include "../lib.h"


void initEditView(EditView *editView) {
    editView->editingIndex = 0;
    editView->editingProduct = NULL;    
}
void updateEditView(EditView *editView, Overview *overview, StateType *currentState, int input) {
    if(editView->popupIsActivated) {
        updatePopup(editView, overview, input);
        return;
    }
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
        editView->editingIndex = 0;
    } else if(input == DEL){
        /*Removes a product and saves the new selection*/
        removeProduct(editView->searchText, overview);
        saveProducts(overview->products, &(overview->productAmount));
    }else if(input == UP) {
        
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
        /*If the user is searching*/
        if(editView->editingIndex == 0) {
            /*And if there is text written in the search bar*/
            if(editView->searchTextLength >= 1) {
                initiateEditing(editView, overview);
            }
        } else {
            /*However if the user is somewhere other than the search bar (is editing a product), try to apply the new changes */
            char *popupText = (char *) malloc(sizeof(char)*128);
            sprintf(popupText, "Are you done editing the product named %s?", editView->editingProduct->name, editView->tempProduct.name);
            showPopup(editView, popupText, "Yes, save it", "No, go back", checkForAbnormalities);
            free(popupText);
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
            
        } else if(editView->editingIndex < 1 && editView->searchTextLength < 20) {
            /*Adds a character to the searchText*/
            editView->searchText[editView->searchTextLength] = input;
            editView->searchText[editView->searchTextLength+1] = '\0';
            editView->searchTextLength++;
        }        
    }
}
void drawEditView(EditView *editView, Overview *overview, Product *product) {
    if(editView->popupIsActivated) {
        drawPopup(editView);
        return;
    }
    /*Draws temporary search box*/
    consolePlacement(0, 0);
    printf("Search: %s", editView->searchText);
    /*Draws the variable lables*/
    editviewUI();
    /*Draws a list of the first n products*/
    drawEditProducts(overview, editView);
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

/*Draws the popup instead of the editing screen*/
void drawPopup(EditView *editView) {
    printf(editView->popupText);
    drawBox(editView->popupLeftText, editView->selectedPopupButton == 0, 40, 15);
    drawBox(editView->popupRightText, editView->selectedPopupButton == 1, 70, 15);
}
/*Takes keyboard input for the popup screen if it is showing*/
void updatePopup(EditView *editView, Overview *overview, int input) {
    if(input == LEFT) {
        editView->selectedPopupButton = 0;
    } else if(input == RIGHT) {
        editView->selectedPopupButton = 1;
    } else if(input == ENTER) {
        hidePopup(editView, overview);
    }
}
/*Activates the popup and gives it appropriate values including a function that should be performed when the popup is hidden*/
void showPopup(EditView *editView, char *popupText, char *popupLeftText, char *popupRightText, void (*f)(EditView *, Overview *)) {
    editView->popupIsActivated = 1;
    strcpy(editView->popupText, popupText);
    editView->popupLeftText = popupLeftText;
    editView->popupRightText = popupRightText;
    editView->selectedPopupButton = 1;
    editView->popupFunction = f;
}
/*Hides the popup and executes the function that it was assigned in the "showPopup" function */
void hidePopup(EditView *editView, Overview *overview) {
    editView->popupIsActivated = 0;
    if(editView->selectedPopupButton == 0 && editView->popupFunction != NULL) {
        editView->popupFunction(editView, overview);
    }
}

void initiateEditing(EditView *editView, Overview *overview) {
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
/*Checks for all the user definable inputs if they are abnormally large or small, if some are, display a popup otherwise, complete editing */
void checkForAbnormalities(EditView *editView, Overview *overview) {
    char* warningText = (char *) malloc(sizeof(char) * 512);
    sprintf(warningText, "WARNING-WARNING-WARNING-WARNING-WARNING");
    int abnormalityFound = 0;
    if(editView->tempProduct.startAmount > 200 || editView->tempProduct.startAmount < 5) {
        sprintf(warningText, "%s\nThe Start Amount is abnormal at %d", warningText, editView->tempProduct.startAmount);
        abnormalityFound = 1;
    }
    if(editView->tempProduct.startPrice > 200 || editView->tempProduct.startPrice < 5) {
        sprintf(warningText, "%s\nThe Start Price is abnormal at %d", warningText, editView->tempProduct.startPrice);
        abnormalityFound = 1;
    }
    if(editView->tempProduct.expectedDelta > 30 || editView->tempProduct.expectedDelta < 5) {
        sprintf(warningText, "%s\nThe Amount Decrement is abnormal at %d", warningText, editView->tempProduct.expectedDelta);
        abnormalityFound = 1;
    }
    if(editView->tempProduct.priceDelta > 30 || editView->tempProduct.priceDelta < 5) {
        sprintf(warningText, "%s\nThe Price Decrement is abnormal at %d", warningText, editView->tempProduct.priceDelta);
        abnormalityFound = 1;
    }
    if(abnormalityFound) {
        showPopup(editView, warningText, "Proceed anyway", "Go back", completeEditing);
    } else {
        completeEditing(editView, overview);
    }
    free(warningText);
}
/* Puts all the values from the temporary product into the product that is currently being edited */
void completeEditing(EditView *editView, Overview *overview) {
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