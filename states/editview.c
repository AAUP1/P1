#include "editview.h"
#include "state.h"
#include "../terminal.h"

void initEditView(EditView *editView) {

}
void updateEditView(EditView *editView, StateType *currentState, int input) {
    if(input == BACKSPACE) {
        *currentState = MENU;
    }
}
void drawEditView(EditView *editView) {
    drawBox("Now you are editing products", 1, 10, 10);
    drawBox("This is a placement box", 1, 10, 20);
}