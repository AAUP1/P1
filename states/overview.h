#include "../UI.h"
#include "state.h"
#include "../product.h"

#define MAX_PRODUCT_AMOUNT 128
#define MAX_TEXT_LENGTH 32
#define LENGTH_OF_DAY (60*60*24)

#ifndef OVERVIEW_DEFINED
#define OVERVIEW_DEFINED
enum SortingState { Name, CurrentAmount, StartPrice, CurrentPrice, PriceDecrement, SORTING_AMOUNT };
typedef enum SortingState SortingState;
struct Overview {
    char searchText[MAX_TEXT_LENGTH];
    int searchTextLength;
    Product products[MAX_PRODUCT_AMOUNT];
    int productAmount;
    /* The time unit is in seconds. There are functions to convert this to hours, minutes and such */
    long int currentTime, timeOffset, startUpdatingTime, lastUpdateTime, nextUpdateTime, timeBetweenUpdates;
    SortingState sorting;
};
typedef struct Overview Overview;
#endif

void initOverview(Overview* overview);
void updateOverview(Overview* overview, StateType *currentState, int input, Product *product);
void drawOverview(Overview* overview);

void drawProducts(Overview *overview);
void addProduct(Overview* overview, char* newname, int startAmount, int startPrice, int expectedDelta, int priceDelta);
void removeProduct(char *name, Overview *overview);
void updateProducts(Overview *overview);

int compareProductsCurrentAmount(const void *p_product1,  const void *p_product2);
int compareProducts(const void *p_product1, const void *p_product2);
void sortProducts(Overview *overview);

void resetProducts(Product *products, int productAmount);
void iterateProductPrices(Product *products, int productAmount);
double getCurrentProductPrice(Product *product);
int getExpectedProductAmount(Product *product);

void setNextTime(Overview *overview);
void updateTime(Overview *overview);
void resetTime(Overview *overview);

int lowercaseStrstr(char *str1, char *str2);
int lowercaseStrcmp(char *str1, char *str2);
int compareLetters(char letter, char otherLetter);
int compareStrings(char *str, char *otherStr);