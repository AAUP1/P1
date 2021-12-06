#include "UI.h"
#include "terminal.h"

#include <string.h>
#include <stdio.h>
#include <windows.h>

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
    for(int i = 0; i < 112; i++){
        wprintf(L"%c", c);
    }
    printf("\n");
}
void listItem(int y){
    ConsolePlacement(0, y);
    line('-');
    //digit
    printf("1.");
    // product name
    ConsolePlacement(4, y + 1);
    printf("DONUTS");
    // Amount
    ConsolePlacement(19, y + 1);
    printf("Product amount");
    // Start price
    ConsolePlacement(34, y + 1);
    printf("SP");
    // Live price
    ConsolePlacement(49, y + 1);
    printf("LP");
    // Decriment
    ConsolePlacement(64, y + 1);
    printf("Decriment");
    printf("\n");
    line('-');
}
