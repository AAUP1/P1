#include "addview.h"
#include "state.h"
#include "../terminal.h"

void initAddView(AddView *addView) {
}
void updateAddView(AddView *addView, StateType *currentState, int input) {
    if(input == BACKSPACE) {
        *currentState = MENU;
    }
}
void drawAddView(AddView *addView) {
    drawBox("Now you are adding products", 0, 10, 10);
}