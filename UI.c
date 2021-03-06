#include "lib.h"



/* makes a menu button: drawBox("text in center", 1/0);*/
void drawBox(char* str, int isactive, int x, int y){
    int strL = strlen(str); //takes the lengh of the input and uses it    
    /*Draws the top of the box*/
    consolePlacement(x, y);
    printf("/");
    for(int i = 0; i < strL + 2; i++){
        if(isactive){
            printf("=");
        } else{
            printf("-");
        }        
    }
    printf("\\");
    printf("\n");
    /* Draws arrow behind box if it is active */
    if(isactive) {
        consolePlacement(x - 5, y + 1);
        printf("--->");
        consolePlacement(x + strL + 5, y + 1);
        printf("<---");
    }
    consolePlacement(x, y + 1);
    printf("| ");
    
    
    /*prints the text in the box*/
    for(int i = 0; i < strL; i++){
        printf("%c", str[i]); 
    }    
    printf(" |\n");
    consolePlacement(x, y + 2);

    /*Draws the buttom of the box*/
    printf("\\");
    for(int i = 0; i < strL + 2; i++){
        if(isactive){
            printf("="); // if active draw these
        } else{
            printf("-"); // in inactive draw these
        }
    }
    printf("/\n");
}

/*draws a line across the screen*/
void line(char c){
    for(int i = 0; i < SCREENWIDTH; i++){
        wprintf(L"%c", c);
    }
    printf("\n");
}
/*Lists an item with Name, amount, price and decrement*/
void listItem(int y, int index, Product *product) {
    consolePlacement(0, y);
    line('-');
    
    /*Digit*/
    if(index != -1) {
        printf("%d.", index);
    } else { //If the index is -1 print questionmarks
        printf("??.");
    }
    
    /*Product name*/
    consolePlacement(4, y + 1);
    printf("%s", product->name);
    
    /*Amount*/
    consolePlacement(20, y + 1);
    printf("%d [%d]", product->currentAmount, getExpectedProductAmount(product));
    /*Start price*/
    consolePlacement(50, y + 1);
    printf("%.2lf", product->startPrice);
    /*Live price*/
    consolePlacement(75, y + 1);
    printf("%.2lf", getCurrentProductPrice(product));
    /*Decriment*/
    consolePlacement(103, y + 1);
    printf("%% %.2lf", product->priceDelta);
    printf("\n");
    line('-');
}
/*List an item with all ediable parameters*/
void editListItem(int y, int index, int editing, Product *product) {
    consolePlacement(0, y);
    line('-');
    
    /*Digit*/
    if(index != -1) {
        printf("%d.", index);
    } else { //If the index is -1 print questionmarks. This is meant for editing the temporary product
        printf("??.");
    }
    
    /*Product name*/
    consolePlacement(4, y + 1);
    printf("%c%s", editing == 1 ? '>' : ' ', product->name);
    
    /*Start Amount*/
    consolePlacement(20, y + 1);
    printf("%c%d", editing == 2 ? '>' : ' ', product->startAmount);
    /*Start price*/
    consolePlacement(50, y + 1);
    printf("%c%.2lf", editing == 3 ? '>' : ' ', product->startPrice);
    /*Amount Decrement*/
    consolePlacement(75, y + 1);
    printf("%c%% %.2lf", editing == 4 ? '>' : ' ', product->expectedDelta);
    /*Price Decrement*/
    consolePlacement(103, y + 1);
    printf("%c%% %.2lf", editing == 5 ? '>' : ' ', product->priceDelta);
    printf("\n");
    line('-');
}
/* Draws an extremely cool title text */
void drawtitle() {
    printf(" ________   ________   _______    ________   ________    \n");
    printf("|\\   __  \\ |\\   __  \\ |\\  ____\\  |\\   __  \\ |\\   ___ \\    \n");
    printf("\\ \\  \\|\\ /_\\ \\  \\|\\  \\\\ \\  \\__|  \\ \\  \\|\\  \\\\ \\  \\_|\\ \\   \n");
    printf(" \\ \\   __  \\\\ \\   _  _\\\\ \\   __\\  \\ \\   __  \\\\ \\  \\ \\\\ \\  \n");
    printf("  \\ \\  \\|\\  \\\\ \\  \\\\  \\|\\ \\  \\_|__ \\ \\  \\ \\  \\\\ \\  \\_\\\\ \\ \n");
    printf("   \\ \\_______\\\\ \\__\\\\ _\\ \\ \\_______\\\\ \\__\\ \\__\\\\ \\_______\\ \n");
    printf("    \\|_______| \\|__|\\|__| \\|_______| \\|__|\\|__| \\|_______|\n");
}
/*Draws the top UI in Overview*/
void overviewUI(int sortingMode){
    consolePlacement(0,1);
    line('-');
    consolePlacement(2, 2);
    printf("Product name %c", sortingMode == Name ? 'v' : ' ');
    consolePlacement(20, 2);
    printf("Product amount %c", sortingMode == CurrentAmount ? 'v' : ' ');
    consolePlacement(45, 2);
    printf("Start Price %c", sortingMode == StartPrice ? 'v' : ' ');
    consolePlacement(71, 2);
    printf("Live Price %c", sortingMode == CurrentPrice ? 'v' : ' ');
    consolePlacement(100, 2);
    printf("Decrement %c", sortingMode == PriceDecrement ? 'v' : ' ');
}
/*Draws the top UI in Editview*/
void editviewUI() {
    consolePlacement(0,1);
    line('-');
    consolePlacement(2, 2);
    printf("Product name");
    consolePlacement(20, 2);
    printf("Start amount");
    consolePlacement(45, 2);
    printf("Start price");
    consolePlacement(68, 2);
    printf("Amount decrement");
    consolePlacement(95, 2);
    printf("Price decrement");
}

void controls(int currentState){
    if(currentState == MENU){
        char* s = "|^ Move Up|   |v Move Down|   |ENTER select|";
        int i = (112 - (strlen(s)-1))/2;
        consolePlacement(i, 37);
        printf("%s", s);
    } else if(currentState == OVERVIEW){
        char* s = "|BACKSPACE Menu| |^v Change start time| |DEL Remove product| |HOME Reset|";
        int i = (112 - (strlen(s)-1))/2;
        consolePlacement(i, 37);
        printf("%s", s);
    } else if(currentState == EDIT){
        char* s = "|BACKSPACE Menu| |<> Swap editing mode| |ENTER create/edit/save|";
        int i = (112 - (strlen(s)-1))/2;
        consolePlacement(i, 37);
        printf("%s", s);
    }
}
