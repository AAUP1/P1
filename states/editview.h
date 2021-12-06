#include "../box.h"
#include "state.h"

struct EditView {
    Box testBox;
    Box box2;
};
typedef struct EditView EditView;

void initEditView(EditView* edit_view);
void updateEditView(EditView* edit_view, StateType *currentState, int input);
void drawEditView(EditView* edit_view);