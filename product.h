#ifndef PRODUCT
#define PRODUCT
#define MAX_NAME_LENGTH 32
struct Product {
    char* name;
    char tempName[MAX_NAME_LENGTH];
    char* test;
    char tempnum[MAX_NAME_LENGTH];
    int nameLength;
    int numLength;
    int startAmount;
    int currentAmount;
    int amountDecrement;
    int startPrice;
    int currentPrice;
    int priceDecrement;
};
typedef struct Product Product;
#endif