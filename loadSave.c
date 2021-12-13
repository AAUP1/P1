#include "lib.h"



void loadProducts(Product *products, int *productAmount) {
    FILE *file = fopen("products.txt", "r");
    if(file != NULL) {
        int i;
        /* Scans the productAmount */
        fscanf(file, " %d", productAmount);
        /* Scans for all the variables in all the products and saves them to a product array */
        for(i = 0; i < *productAmount; i++) {
            char* name = (char *) malloc(MAX_NAME_LENGTH * sizeof(char));
            int startAmount, expectedDelta, startPrice, priceDelta, currentAmount, expectedModifier, priceModifier;
            fscanf(file, " %s %d %d %d %d %d %d %d", name, &startAmount, &expectedDelta, &startPrice, &priceDelta, &currentAmount, &expectedModifier, &priceModifier);
            strcpy(products[i].name, name);
            products[i].startAmount = startAmount;
            products[i].expectedDelta = expectedDelta;
            products[i].startPrice = startPrice;
            products[i].priceDelta = priceDelta;
            products[i].currentAmount = currentAmount;
            products[i].expectedModifier = expectedModifier;
            products[i].priceModifier = priceModifier;
            free(name);
        }
        fclose(file);
    } else {
        *productAmount = 0;
    }
}

void saveProducts(Product *products, int *productAmount) {
    FILE *file = fopen("products.txt", "w");
    int i;
    /* Saves the new product amount to the file */
    fprintf(file, "%d \n", *productAmount);
    /* Saves the new product variables to the file */
    for(i = 0; i < *productAmount; i++) {
        fprintf(file, "%s %d %d %d %d %d %d %d \n", 
            products[i].name, 
            products[i].startAmount, products[i].expectedDelta, products[i].startPrice, 
            products[i].priceDelta, products[i].currentAmount, products[i].expectedModifier, products[i].priceModifier);
    }
    fclose(file);
}

void saveStartTime(long int startUpdatingTime) {
    FILE *file;
    file = fopen("startTime.txt", "w");
    fprintf(file, "%d", startUpdatingTime);
    fclose(file);
}
void loadStartTime(long int *startUpdatingTime) {
    FILE *file;
    file = fopen("startTime.txt", "r");
    fscanf(file, "%d", startUpdatingTime);
    fclose(file);
}