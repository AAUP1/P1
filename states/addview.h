#include "../UI.h"
#include "state.h"

struct AddView {
    
};
typedef struct AddView AddView;

void initAddView(AddView* AddView);
void updateAddView(AddView* AddView, StateType *currentState, int input);
void drawAddView(AddView* AddView);