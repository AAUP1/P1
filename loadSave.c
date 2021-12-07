#include <stdlib.h>

#include "loadSave.h"

#define MAX_NAME_LENGTH 32

void loadProducts(Product *products, int *productAmount) {
    FILE *file = fopen("products.txt", "r");
    if(file != NULL) {
        int i;
        fscanf(file, " %d", productAmount);
        for(i = 0; i < *productAmount; i++) {
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
        fclose(file);
    } else {
        *productAmount = 0;
    }
}

void saveProducts(Product *products, int *productAmount) {
    FILE *file = fopen("products.txt", "w");
    int i;
    fprintf(file, "%d \n", *productAmount);
    for(i = 0; i < *productAmount; i++) {
        fprintf(file, "%s %d %d %d %d %d %d \n", 
            products[i].name, 
            products[i].startAmount, products[i].currentAmount, products[i].amountDecrement, 
            products[i].startPrice, products[i].currentPrice, products[i].priceDecrement);
    }
    fclose(file);
}

int countLinesInFile(FILE *f) {
    char currentChar = '\n';
    int lines = 0;
    while(!feof(f)) {
        currentChar = fgetc(f);
        if(currentChar == '\n') {
            lines++;
        }
    }
    return lines;
}

void productToString(Product product) {
    printf("PRODUCT [Name: %s, StartAmount: %d, CurrentAmount: %d, AmountDecrement: %d, StartPrice: %d, CurrentPrice: %d, PriceDecrement: %d \n", 
            product.name, product.startAmount, product.currentAmount, product.amountDecrement,
            product.startPrice, product.currentAmount, product.priceDecrement);
}