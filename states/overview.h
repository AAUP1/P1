#include "../UI.h"
#include "state.h"

struct Overview {
    
};
typedef struct Overview Overview;

void initOverview(Overview* overview);
void updateOverview(Overview* overview, StateType *currentState, int input);
void drawOverview(Overview* overview);