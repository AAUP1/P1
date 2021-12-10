#ifndef PRODUCT
#define PRODUCT
#define MAX_NAME_LENGTH 32
struct Product {
    char* name;
    char tempName[MAX_NAME_LENGTH];
    int tempnum;
    int nameLength;
    int startAmount;
    int currentAmount;
    int amountDecrement;
    int currentAmountDecrement;
    int expectedAmount;
    int startPrice;
    int currentPrice;
    int priceDecrement;
    int currentPriceDecrement;
};
typedef struct Product Product;
#endif