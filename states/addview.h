#include "../box.h"
#include "state.h"

struct AddView {
    Box testBox;
};
typedef struct AddView AddView;

void initOverview(AddView* overview);
void updateOverview(AddView* overview, StateType *currentState, int input);
void drawOverview(AddView* overview);