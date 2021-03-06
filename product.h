#ifndef PRODUCT
#define PRODUCT
#define MAX_NAME_LENGTH 32
#define MAX_NUMBER_LENGTH 9
struct Product {
    char name[MAX_NAME_LENGTH];
    int nameLength;

    /*Constant values*/
        int startAmount;
        double expectedDelta;
        double startPrice;
        double priceDelta;

    /*Dynamic values*/
        int currentAmount;

    /* What percentage of the starting value is the current value */
        double expectedModifier;
        double priceModifier;
};
typedef struct Product Product;
#endif