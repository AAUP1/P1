#include "addview.h"
#include "state.h"
#include "../terminal.h"

void initAddView(AddView *addView) {
    initBox(&(addView->testBox), 10, 10, "Now you are adding products");
}
void updateAddView(AddView *addView, StateType *currentState, int input) {
    if(input == BACKSPACE) {
        *currentState = MENU;
    }
}
void drawAddView(AddView *addView) {
    drawStructBox(&(addView->testBox));
}