#ifndef PRODUCT
#define PRODUCT
#define MAX_NAME_LENGTH 32
struct Product {
    char* name;
    char tempName[MAX_NAME_LENGTH];
    char* test;
    int tempnum;
    int nameLength;
    int startAmount;
    int currentAmount;
    int amountDecrement;
    int startPrice;
    int currentPrice;
    int priceDecrement;
};
typedef struct Product Product;
#endif