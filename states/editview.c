#include "editview.h"
#include "state.h"
#include "../terminal.h"

void initEditView(EditView *editView) {
    initBox(&(editView->testBox), 10, 10, "Now you are editing products");
    initBox(&(editView->box2), 10, 20, "This is a placement box");
}
void updateEditView(EditView *editView, StateType *currentState, int input) {
    if(input == BACKSPACE) {
        *currentState = MENU;
    }
}
void drawEditView(EditView *editView) {
    drawStructBox(&(editView->testBox));
    drawStructBox(&(editView->box2));
}