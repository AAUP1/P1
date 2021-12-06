#include "addview.h"
#include "state.h"
#include "../terminal.h"

void initEditView(AddView *addView) {

}
void updateEditView(AddView *addView, StateType *currentState, int input) {
    if(input == BACKSPACE) {
        *currentState = MENU;
    }
}
void drawEditView(AddView *addView) {
    drawStructBox(&(addView->testBox));
}