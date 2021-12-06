#include "../UI.h"
#include "state.h"

struct AddView {
    Box testBox;
};
typedef struct AddView AddView;

void initAddView(AddView* AddView);
void updateAddView(AddView* AddView, StateType *currentState, int input);
void drawOAddView(AddView* AddView);