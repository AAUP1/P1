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


void line(char c){
    for(int i = 0; i < 117; i++){
        wprintf(L"%c", c);
    }
    printf("\n");
}