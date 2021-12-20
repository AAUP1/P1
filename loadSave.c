#include "lib.h"

void loadProducts(Product *products, int *productAmount) {
    FILE *file = fopen("products.txt", "r");
    if(file != NULL) {
        int i, c, foundLetter;
        /* Scans the productAmount */
        fscanf(file, " %d", productAmount);
        /* Scans for all the variables in all the products and saves them to a product array */
        for(i = 0; i < *productAmount; i++) {
            /* Makes a temporary allocation for the name*/
            char* name = (char *) malloc(MAX_NAME_LENGTH * sizeof(char));
            int startAmount, currentAmount;
            double expectedDelta, startPrice, priceDelta, expectedModifier, priceModifier;
            /* Puts the cursor for fscanf after the name of the product */
            fscanf(file, " %-32s", name);
            /* Gets the name of the product - this does not move the file cursor */
            fgets(name, MAX_NAME_LENGTH, file);
            /* Scans the rest of the file */
            fscanf(file, " %d %lf %lf %lf %d %lf %lf", &startAmount, &expectedDelta, &startPrice, &priceDelta, &currentAmount, &expectedModifier, &priceModifier);
            /*Cuts all the trailing spaces off the name*/
            foundLetter = 0;
            for(c = strlen(name)-1; c >= 0 && !foundLetter; c--) {
                if(name[c] != ' ') {
                    foundLetter = 1;
                    name[c+1] = '\0';
                }
            }
            /* Copies each letter of the temporary name into the product name */
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
        fprintf(file, "%-32s %d %lf %lf %lf %d %lf %lf \n", 
            products[i].name, 
            products[i].startAmount, products[i].expectedDelta, products[i].startPrice, 
            products[i].priceDelta, products[i].currentAmount, products[i].expectedModifier, 
            products[i].priceModifier);
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