#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//Is used to make all letters lowercase, making the search function in drawProducts case insensitive
#include <ctype.h>

/* overview.h also includes product.h */
#include "overview.h"
#include "../terminal.h"
#include "state.h"
#include "../loadSave.h"

/* Overview Functions */
void initOverview(Overview *overview) {
    overview->state = Searching;

    updateTime(overview);
    loadStartTime(&(overview->startHour), &(overview->startMinute));
    resetTime(overview);
    overview->minutesBetweenUpdates = 120;

    loadProducts(overview->products, &overview->productAmount);

    overview->searchTextLength = 0;
    overview->searchText[0] = '\0';

    srand(time(NULL));
}
void updateOverview(Overview *overview, StateType* currentState, int input) {
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
            overview->startHour++;
            saveStartTime(overview->startHour, overview->startMinute);
        } else {
            /*Adds a product and saves the new selection*/
            addProduct(overview);
            saveProducts(overview->products, &(overview->productAmount));
        }
    } else if(input == DOWN) {
        if(overview->state == ChangingTime) {
            overview->startHour--;
            saveStartTime(overview->startHour, overview->startMinute);
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
        overview->timeSkipped += 20 * 60;
        for(int i = 0; i < overview->productAmount; i++) {
            overview->products[i].currentAmount -= rand() % 10;
            if(overview->products[i].currentAmount < 0) {
                overview->products[i].currentAmount = 0;
            }
        }
    } else if(input == PAGE_DOWN) {
        overview->timeSkipped -= 20 * 60;
    } else if(input == HOME) {
        resetTime(overview);
        resetProducts(overview->products, overview->productAmount);
    } else {
        /*Adds a character to the searchText*/
        overview->searchText[overview->searchTextLength] = input;
        overview->searchText[overview->searchTextLength+1] = '\0';
        overview->searchTextLength++;
    }
    
    /*Handle the time of day*/
    updateTime(overview);
    if(overview->hour > overview->nextHour || (overview->hour == overview->nextHour && overview->minute > overview->nextMinute)) {
        setNextTime(overview);
        iterateProductPrices(overview->products, overview->productAmount);   
    }
    
    
}
void drawOverview(Overview *overview) {
    /*Draws temporary search box*/
    printf("Date: %02d/%02d/%d     Time: %02d:%02d:%02d    %cStart: %02d:%02d:00     Next: %02d:%02d:00    %cSearch: %s", 
        overview->day, overview->month, overview->year,
        overview->hour, overview->minute, overview->second, 
        overview->state == ChangingTime ? '>' : ' ',
        overview->startHour, overview->startMinute,
        overview->nextHour, overview->nextMinute,
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
        if(strstr(strToLower(currentProduct->name), strToLower(overview->searchText))) {
            y++;
            listItem(4 + y * 3, y, currentProduct);
        }
    }
}

void addProduct(Overview* overview) {
    Product *newProduct = &((overview->products)[overview->productAmount]);
    newProduct->name = "Pizzasnails";
    newProduct->startAmount = 1000;
    newProduct->amountDecrement = 10;
    newProduct->startPrice = 100;
    newProduct->priceDecrement = 8;

    resetProduct(*newProduct);

    overview->productAmount++;
}
void removeProduct(char *name, Overview *overview) {
    int found = 0;
    for(int i = 0; i < overview->productAmount; i++) {
        /* If the product has the same name as what should be removed, mark it as found */
        if(!strcmp(strToLower(overview->products[i].name), strToLower(name))) {
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
void resetProducts(Product *products, int productAmount) {
    for(int i = 0; i < productAmount; i++) {
        resetProduct(products[i]);
    }
}
void resetProduct(Product product) {
    product.currentAmount = product.startAmount;
    product.currentPrice = product.startPrice;
    product.expectedAmount = product.startAmount;
    product.currentPriceDecrement = 0;
    product.currentAmountDecrement = 0;
}
void iterateProductPrices(Product *products, int productAmount) {
    for(int i = 0; i < productAmount; i++) {
            Product *product = &(products[i]);
            product->currentAmountDecrement += product->amountDecrement;
            if(product->currentAmountDecrement > 100) {
                product->currentAmountDecrement = 100;
            }
            product->expectedAmount = product->startAmount - (product->startAmount * product->currentAmountDecrement / 100.0);
            if(product->currentAmount > product->expectedAmount) {
                product->currentPriceDecrement += product->priceDecrement;
                if(product->currentPriceDecrement > 100) {
                    product->currentPriceDecrement = 100;
                }
                product->currentPrice = product->startPrice - (product->startPrice * product->currentPriceDecrement / 100.0);
            }
        } 
}

void updateTime(Overview *overview) {
    long int seconds;
    time(&seconds);
    seconds += overview->timeSkipped;
    struct tm *time = localtime(&seconds);
    overview->second = time->tm_sec;
    overview->minute = time->tm_min;
    overview->hour   = time->tm_hour;
    
    overview->day = time->tm_mday;
    overview->month = 1+time->tm_mon;
    overview->year = 1900+time->tm_year;
}
void resetTime(Overview *overview) {
    overview->nextHour = overview->startHour;
    overview->nextMinute = overview->startMinute;
    overview->lastHour = 0;
    overview->lastMinute = 0; 
    overview->timeSkipped = 0;
}
void setNextTime(Overview *overview) {
    overview->lastHour = overview->nextHour;
    overview->lastMinute = overview->nextMinute;
    overview->nextHour += overview->minutesBetweenUpdates/60;
    overview->nextMinute += overview->minutesBetweenUpdates%60;
    if(overview->nextMinute >= 60) {
        overview->nextHour++;
        overview->nextMinute -= 60;
    }
    if(overview->nextHour >= 24) {
        overview->nextHour -= 24;
    }
}

char *strToLower(char *str) {
    char *strTemp = (char *) malloc((strlen(str)) * sizeof(char));
    int i;
    for(i = 0; i < strlen(str); i++) {
        if(str[i] != '\0') {
            strTemp[i] = tolower(str[i]);
        } else {
            strTemp[i] = str[i];
        }
    }
    strTemp[i] = '\0';
    return strTemp;
}

void compareProducts(void *p_product1, void *p_product2) {
    Product *product1, *product2;
    int i, p1NameLength, p2NameLength;
    product1 = (Product *) p_product1;
    product2 = (Product *) p_product2;
    p1NameLength = strlen(product1->name);
    p2NameLength = strlen(product2->name);
    /*for(i = 0; i < min(p1NameLength, p2NameLength); i++) {

    }*/
}

/*KNOWN ISSUE: The resetting and loading of products does not work correctly*/