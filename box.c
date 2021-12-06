#include "box.h"
#include "terminal.h"

#include <string.h>
#include <stdio.h>
#include <windows.h>

// Initializes a box object with the given values
void initBox(Box* box, int x, int y, char* text) {
    box->x = x;
    box->y = y;
    box->text = text;
    box->active = 0;
}
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
// Draws a box using the struct that represents a box
void drawStructBox(Box* box) {
    drawBox(box->text, box->active, box->x, box->y);
}