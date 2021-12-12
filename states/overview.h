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
    int lastHour, lastMinute;
    int minutesBetweenUpdates, timeSkipped;
    int year, month, day, hour, minute, second;
    OverviewState state;
};
typedef struct Overview Overview;
#endif

void initOverview(Overview* overview);
void updateOverview(Overview* overview, StateType *currentState, int input);
void drawOverview(Overview* overview);

void drawProducts(Overview *overview);
int compareProducts(const void *p_product1, const void *p_product2);

void addProduct(Overview* overview);
void removeProduct(char *name, Overview *overview);
void resetProducts(Product *products, int productAmount);
void resetProduct(Product product);
void iterateProductPrices(Product *products, int productAmount);

void setNextTime(Overview *overview);
void updateTime(Overview *overview);
void resetTime(Overview *overview);

int lowercaseStrstr(char *str1, char *str2);
int lowercaseStrcmp(char *str1, char *str2);
int compareLetters(char letter, char otherLetter);
int compareStrings(char *str, char *otherStr);