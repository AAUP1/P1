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

    /*Constant values*/
        int startAmount;
        int expectedDelta;
        int startPrice;
        int priceDelta;

    /*Dynamic values*/
        int currentAmount;

        /* What percentage of the starting value is the current value */
        int expectedModifier;
        int priceModifier;
};
typedef struct Product Product;
#endif