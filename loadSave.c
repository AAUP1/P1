#include <stdlib.h>

#include "loadSave.h"

#define MAX_NAME_LENGTH 32

void loadProducts(Product *products, int productAmount, FILE *file) {
    int i;
    for(i = 0; i < productAmount; i++) {
        char* name = (char *) malloc(MAX_NAME_LENGTH * sizeof(char));
        int startAmount, currentAmount, amountDecrement, startPrice, currentPrice, priceDecrement;
        fscanf(file, " %s %d %d %d %d %d %d", name, &startAmount, &currentAmount, &amountDecrement, &startPrice, &currentPrice, &priceDecrement);
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
        fprintf(file, "%s %d %d %d %d %d %d \n", 
            products[i].name, 
            products[i].startAmount, products[i].currentAmount, products[i].amountDecrement, 
            products[i].startPrice, products[i].currentPrice, products[i].priceDecrement);
    }

}

void productToString(Product product) {
    printf("PRODUCT [Name: %s, StartAmount: %d, CurrentAmount: %d, AmountDecrement: %d, StartPrice: %d, CurrentPrice: %d, PriceDecrement: %d \n", 
            product.name, product.startAmount, product.currentAmount, product.amountDecrement,
            product.startPrice, product.currentAmount, product.priceDecrement);
}