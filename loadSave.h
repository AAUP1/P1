#include <stdio.h>

/* Gets the definition of the product struct */
#include "product.h"

#ifndef PRODUCT_SAVELOAD
#define PRODUCT_SAVELOAD
void loadProducts(Product *products, int *productAmount);
void saveProducts(Product *products, int *productAmount);
#endif

int countLinesInFile(FILE *f);

void saveStartTime(long int startUpdatingTime);
void loadStartTime(long int *startUpdatingTime);