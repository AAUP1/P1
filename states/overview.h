#include "../UI.h"
#include "state.h"
#include "../product.h"

#define MAX_PRODUCT_AMOUNT 128
#define MAX_TEXT_LENGTH 32

struct Overview {
    Product products[MAX_PRODUCT_AMOUNT];
    char searchText[MAX_TEXT_LENGTH];
    int searchTextLength;
    int productAmount;
};
typedef struct Overview Overview;

void initOverview(Overview* overview);
void updateOverview(Overview* overview, StateType *currentState, int input);
void drawOverview(Overview* overview);

void drawProducts(Overview *overview);

void addProduct(Overview* overview);
void removeProduct(char *name, Overview *overview);