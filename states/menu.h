#include "../box.h"
#include "state.h"

struct Menu {
    int box_amount;
    struct Box boxes[3];
    int activeBoxIndex;
};
typedef struct Menu Menu;

void initMenu(Menu* menu, int box_amount, int activeBoxIndex);
void updateMenu(Menu* menu, StateType *currentState, int *programRunning, int input);
void drawMenu(Menu* menu);