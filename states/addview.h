#include "../box.h"
#include "state.h"

struct AddView {
    Box testBox;
};
typedef struct AddView AddView;

void initAddView(AddView* overview);
void updateAddView(AddView* overview, StateType *currentState, int input);
void drawAddView(AddView* overview);