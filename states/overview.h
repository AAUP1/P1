#include "../UI.h"
#include "state.h"
#include "../product.h"

#define MAX_PRODUCT_AMOUNT 128
#define MAX_TEXT_LENGTH 32

#ifndef OVERVIEW_DEFINED
#define OVERVIEW_DEFINED
enum OverviewState { Searching, ChangingTime };
typedef enum OverviewState OverviewState;
struct Overview {
    Product products[MAX_PRODUCT_AMOUNT];
    char searchText[MAX_TEXT_LENGTH];
    int searchTextLength;
    int productAmount;
    int startHour, startMinute;
    int nextHour, nextMinute;
    int minutesBetweenUpdates;
    int year, month, day, hour, minute, second;
    OverviewState state;
};
typedef struct Overview Overview;
#endif

void initOverview(Overview* overview);
void updateOverview(Overview* overview, StateType *currentState, int input, Product *product);
void drawOverview(Overview* overview);

void drawProducts(Overview *overview);

void addProduct(Overview* overview, char* newname, int startAmount, int currentAmount, int startPrice, int currentPrice, int amountDecrement);
void removeProduct(char *name, Overview *overview);

void updateTime(Overview *overview);

char *strToLower(char *str);