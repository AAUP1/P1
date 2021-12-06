#include "../UI.h"
#include "state.h"

struct Menu {
    int box_amount;
    int activeBoxIndex;
};
typedef struct Menu Menu;

void initMenu(Menu* menu);
void updateMenu(Menu* menu, StateType *currentState, int *programRunning, int input);
void drawMenu(Menu* menu);