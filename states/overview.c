#include "../lib.h"

/* Overview Functions */
void initOverview(Overview *overview) {
    overview->state = Searching;

    updateTime(overview);
    loadStartTime(&(overview->startUpdatingTime));
    resetTime(overview);
    overview->timeBetweenUpdates = 120*60;

    loadProducts(overview->products, &overview->productAmount);
    qsort(overview->products, overview->productAmount, sizeof(Product), compareProducts);

    overview->searchTextLength = 0;
    overview->searchText[0] = '\0';
    
    resetProducts(overview->products, overview->productAmount);

    srand(time(NULL));
}
void updateOverview(Overview *overview, StateType* currentState, int input, Product *product) {
    if(input == BACKSPACE) {
        /*Removes a character from the searchText*/
        if(overview->searchTextLength >= 1){
            overview->searchTextLength--;
            overview->searchText[overview->searchTextLength] = '\0';
        } else {
            *currentState = MENU;
        }
        
    } else if(input == UP) {
        if(overview->state == ChangingTime) {
            overview->startUpdatingTime += 60*60;
            saveStartTime(overview->startUpdatingTime);
        } else {
            /*Adds a product and saves the new selection*/
            addProduct(overview, "Henlo", 420, 69, 20, 10);
            saveProducts(overview->products, &(overview->productAmount));
        }
    } else if(input == DOWN) {
        if(overview->state == ChangingTime) {
            overview->startUpdatingTime -= 60*60;
            saveStartTime(overview->startUpdatingTime);
        }
    } else if(input == LEFT) {
        overview->state = ChangingTime;
    } else if(input == RIGHT) {
        overview->state = Searching;
    } else if(input == DEL) {
        /*Removes a product and saves the new selection*/
        removeProduct(overview->searchText, overview);
        saveProducts(overview->products, &(overview->productAmount));
    } else if(input == PAGE_UP) {
        overview->timeOffset += 20 * 60;
        for(int i = 0; i < overview->productAmount; i++) {
            overview->products[i].currentAmount -= rand() % 10;
            if(overview->products[i].currentAmount < 0) {
                overview->products[i].currentAmount = 0;
            }
        }
    } else if(input == ESCAPE) {
        
    } else if(input == PAGE_DOWN) {
        
    }else if(input == HOME) {
        resetTime(overview);
        resetProducts(overview->products, overview->productAmount);
    } else if(input == END) {
        
    } else {
        /*Adds a character to the searchText*/
        overview->searchText[overview->searchTextLength] = input;
        overview->searchText[overview->searchTextLength+1] = '\0';
        overview->searchTextLength++;
    }
    
    /*Handle the time of day*/
    updateTime(overview);
    updateProducts(overview);
    
    
}
void drawOverview(Overview *overview) {
    struct tm *time = localtime(&overview->currentTime);
    /*Draws temporary search box*/
    printf("Date: %02d/%02d/%d     Time: %02d:%02d:%02d    ", 
        time->tm_mday, time->tm_mon, 1900+time->tm_year,
        time->tm_hour, time->tm_min, time->tm_sec);
    time = localtime(&overview->startUpdatingTime);
    printf("%cStart: %02d:%02d:00     ", 
        overview->state == ChangingTime ? '>' : ' ',
        time->tm_hour, time->tm_min);
    time = localtime(&overview->nextUpdateTime);
    printf("Next: %02d:%02d:00    ", 
        time->tm_hour, time->tm_min);
    printf("%cSearch: %s", 
        overview->state == Searching ? '>' : ' ',
        overview->searchText);
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
        if(lowercaseStrstr(currentProduct->name, overview->searchText)) {
            y++;
            listItem(4 + y * 3, y, currentProduct);
        }
    }
}

void addProduct(Overview* overview, char* newname, int startAmount, int startPrice, int expectedDelta, int priceDelta) {
    Product *newProduct = &((overview->products)[overview->productAmount]);
    strcpy(newProduct->name, newname);
    newProduct->startAmount = startAmount;
    newProduct->expectedDelta = expectedDelta;
    newProduct->startPrice = startPrice;
    newProduct->priceDelta = priceDelta;

    overview->productAmount++;
    qsort(overview->products, overview->productAmount, sizeof(Product), compareProducts);
}
void removeProduct(char *name, Overview *overview) {
    int found = 0;
    for(int i = 0; i < overview->productAmount; i++) {
        /* If the product has the same name as what should be removed, mark it as found */
        if(!lowercaseStrcmp(overview->products[i].name, name)) {
            found = 1;
        }
        /* If the product has been found, move the proceding products one step down over the product that should be removed */
        if(found) {
            if(i == overview->productAmount-1) {
                /*Do nothing if we have reached the end of the array, as the length will just be shortened*/
            } else {
                /*Moves the products one space down*/
                overview->products[i] = overview->products[i+1];
            }
        }
    }
    if(found) {
        overview->productAmount--;
    }
}
void updateProducts(Overview *overview) {
    if(overview->currentTime%LENGTH_OF_DAY >= overview->nextUpdateTime%LENGTH_OF_DAY) {
        iterateProductPrices(overview->products, overview->productAmount);
        setNextTime(overview);
    }
}

void updateTime(Overview *overview) {
    time(&overview->currentTime);
    overview->currentTime = 1639288800; /*This corresponds to the 12th of december 2021 at 7 AM*/
    overview->currentTime += overview->timeOffset;
    while(overview->currentTime%LENGTH_OF_DAY + overview->timeBetweenUpdates < overview->nextUpdateTime%LENGTH_OF_DAY) {
        overview->nextUpdateTime -= overview->timeBetweenUpdates;
    }
    if(overview->nextUpdateTime%LENGTH_OF_DAY < overview->startUpdatingTime%LENGTH_OF_DAY) {
        overview->nextUpdateTime = overview->startUpdatingTime;
    }
}
void resetTime(Overview *overview) {
    overview->nextUpdateTime = overview->startUpdatingTime;
    overview->lastUpdateTime = 0;
    overview->timeOffset = 0;
}
void setNextTime(Overview *overview) {
    overview->lastUpdateTime = overview->nextUpdateTime;
    overview->nextUpdateTime += overview->timeBetweenUpdates;
}

void resetProducts(Product *products, int productAmount) {
    for(int i = 0; i < productAmount; i++) {
        products[i].currentAmount = products[i].startAmount;
        products[i].expectedModifier = 100;
        products[i].priceModifier = 100;  
    }
}  
void iterateProductPrices(Product *products, int productAmount) {
    for(int i = 0; i < productAmount; i++) {
        products[i].expectedModifier -= products[i].expectedDelta;
        if(products[i].expectedModifier < 0) {
            products[i].expectedModifier = 0;
        }
        if(products[i].currentAmount > getExpectedProductAmount(&products[i])) {
            products[i].priceModifier -= products[i].priceDelta;
            if(products[i].priceModifier < 0) {
                products[i].priceModifier = 0;
            }
        }
    }
}
int getCurrentProductPrice(Product *product) {
    return (product->startPrice * product->priceModifier) / 100;
}
int getExpectedProductAmount(Product *product) {
    return (product->startAmount * (product->expectedModifier-product->expectedDelta)) / 100;
}

int lowercaseStrcmp(char *str1, char *str2) {
    char str1Low[MAX_NAME_LENGTH];
    char str2Low[MAX_NAME_LENGTH];
    int i; 
    for(i = 0; i <= strlen(str1); i++) {
        str1Low[i] = tolower(str1[i]);
    }
    for(i = 0; i <= strlen(str2); i++) {
        str2Low[i] = tolower(str2[i]);
    }
    return strcmp(str1Low, str2Low);
}
int lowercaseStrstr(char *str1, char *str2) {
    char str1Low[MAX_NAME_LENGTH];
    char str2Low[MAX_NAME_LENGTH];
    int i; 
    for(i = 0; i <= strlen(str1); i++) {
        str1Low[i] = tolower(str1[i]);
    }
    for(i = 0; i <= strlen(str2); i++) {
        str2Low[i] = tolower(str2[i]);
    }
    return strstr(str1Low, str2Low) != NULL;
}
int compareLetters(char letter, char otherLetter) {
    return tolower(letter) - tolower(otherLetter);
}
int compareStrings(char *str, char *otherStr) {
    int strLength = strlen(str);
    int otherStrLength = strlen(otherStr);
    int shortestLength = strLength < otherStrLength ? strLength : otherStrLength;
    int letterResult = 0;
    for(int i = 0; i < shortestLength; i++) {
        letterResult = compareLetters(str[i], otherStr[i]);
        if(letterResult != 0) {
            return letterResult;
        }
    }
    return strLength - otherStrLength;
}

int compareProducts(const void *p_product1,  const void *p_product2) {
    Product *product1, *product2;
    product1 = (Product *) p_product1;
    product2 = (Product *) p_product2;
    return compareStrings(product1->name, product2->name);
}