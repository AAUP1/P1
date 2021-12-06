#include "loadSave.h"

void loadProducts(Product *products, int productAmount, FILE *file) {
    int i;
    for(i = 0; i < productAmount; i++) {
        char* name;
        int startAmount, currentAmount, amountDecrement, startPrice, currentPrice, priceDecrement;
        fscanf(file, "%s %d %d %d %d %d %d", name, &startAmount, &currentAmount, &amountDecrement, &startPrice, &currentPrice, &priceDecrement);
        products[i].name = name;
        products[i].startAmount = startAmount;
        products[i].currentAmount = currentAmount;
        products[i].amountDecrement = amountDecrement;
        products[i].startPrice = startPrice;
        products[i].currentPrice = currentPrice;
        products[i].priceDecrement = priceDecrement;

    }
}

void saveProducts(Product *products, int productAmount, FILE *file) {
    int i;
    for(i = 0; i < productAmount; i++) {
        fprintf(file, " %s %d %d %d %d %d %d", 
            products[i].name, 
            products[i].startAmount, products[i].currentAmount, products[i].amountDecrement, 
            products[i].startPrice, products[i].currentPrice, products[i].priceDecrement);
    }
}