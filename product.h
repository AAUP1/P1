#ifndef PRODUCT
#define PRODUCT
struct Product {
    char* name;
    int startAmount;
    int currentAmount;
    int amountDecrement;
    int startPrice;
    int currentPrice;
    int priceDecrement;
};
typedef struct Product Product;
#endif