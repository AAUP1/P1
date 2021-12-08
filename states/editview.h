#include "state.h"
#include "overview.h"
struct EditView {
    
};
typedef struct EditView EditView;

void initEditView(EditView* edit_view);
void updateEditView(EditView* edit_view, StateType *currentState, Overview *overview, int input);
void drawEditView(EditView* edit_view, Overview *overview);