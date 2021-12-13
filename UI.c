#include "lib.h"

#define SCREENWIDTH 112

// makes a menu button: drawBox("text in center", 1/0);
void drawBox(char* str, int isactive, int x, int y){
    //takes the lengh of the input and uses it    
    int strL = strlen(str);
    //Box top
    ConsolePlacement(x, y);
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
        ConsolePlacement(x - 5, y + 1);
        printf("--->");
        ConsolePlacement(x + strL + 5, y + 1);
        printf("<---");
    }
    ConsolePlacement(x, y + 1);
    printf("| ");
    
    
    //prints the text in the box
    for(int i = 0; i < strL; i++){
        printf("%c", str[i]);
    }
    
    printf(" |\n");
    ConsolePlacement(x, y + 2);
    //box bottom
    printf("\\");
    for(int i = 0; i < strL + 2; i++){
        if(isactive){
            printf("=");
        } else{
            printf("-");
        }
    }
    printf("/\n");
}

//draws a line across the screen!
void line(char c){
    for(int i = 0; i < SCREENWIDTH; i++){
        wprintf(L"%c", c);
    }
    printf("\n");
}
void listItem(int y, int index, Product *product) {
    ConsolePlacement(0, y);
    line('-');
    //digit
    printf("%d.", index);
    // product name
    ConsolePlacement(4, y + 1);
    printf("%s", product->name);
    // Amount
    ConsolePlacement(20, y + 1);
    printf("%d [%d]", product->currentAmount, getExpectedProductAmount(product));
    // Start price
    ConsolePlacement(50, y + 1);
    printf("%d", product->startPrice);
    // Live price
    ConsolePlacement(75, y + 1);
    printf("%d", getCurrentProductPrice(product));
    // Decriment
    ConsolePlacement(103, y + 1);
    printf("%% %d", product->priceModifier);
    printf("\n");
    line('-');
}

void editListItem(int y, int index, Product *product) {
    ConsolePlacement(0, y);
    line('-');
    //digit
    printf("%d.", index);
    // product name
    ConsolePlacement(4, y + 1);
    printf("%s", product->name);
    // Amount
    ConsolePlacement(20, y + 1);
    printf("%d", product->startAmount);
    // Start price
    ConsolePlacement(50, y + 1);
    printf("%d", product->startPrice);
    // Live price
    ConsolePlacement(75, y + 1);
    printf("%% %d", product->expectedDelta);
    // Decriment
    ConsolePlacement(103, y + 1);
    printf("%% %d", product->priceDelta);
    printf("\n");
    line('-');
}
void drawtitle() {
    /* Draws an extremely cool title text */
    printf(" ________   ________   _______    ________   ________    \n");
    printf("|\\   __  \\ |\\   __  \\ |\\  ____\\  |\\   __  \\ |\\   ___ \\    \n");
    printf("\\ \\  \\|\\ /_\\ \\  \\|\\  \\\\ \\  \\__|  \\ \\  \\|\\  \\\\ \\  \\_|\\ \\   \n");
    printf(" \\ \\   __  \\\\ \\   _  _\\\\ \\   __\\  \\ \\   __  \\\\ \\  \\ \\\\ \\  \n");
    printf("  \\ \\  \\|\\  \\\\ \\  \\\\  \\|\\ \\  \\_|__ \\ \\  \\ \\  \\\\ \\  \\_\\\\ \\ \n");
    printf("   \\ \\_______\\\\ \\__\\\\ _\\ \\ \\_______\\\\ \\__\\ \\__\\\\ \\_______\\ \n");
    printf("    \\|_______| \\|__|\\|__| \\|_______| \\|__|\\|__| \\|_______|\n");
    /* Draws all the boxes */
}
void overviewUI(){
    ConsolePlacement(0,1);
    line('-');
    ConsolePlacement(2, 2);
    printf("Product name");
    ConsolePlacement(20, 2);
    printf("Product amount");
    ConsolePlacement(45, 2);
    printf("Start Price");
    ConsolePlacement(71, 2);
    printf("Live Price");
    ConsolePlacement(100, 2);
    printf("Decrement");
}

void editviewUI() {
    ConsolePlacement(0,1);
    line('-');
    ConsolePlacement(2, 2);
    printf("Product name");
    ConsolePlacement(20, 2);
    printf("Start amount");
    ConsolePlacement(45, 2);
    printf("Start price");
    ConsolePlacement(71, 2);
    printf("Amount decrement");
    ConsolePlacement(100, 2);
    printf("Price decrement");
}
