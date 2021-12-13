#include <stdio.h>

/* Gets the definition of the product struct */
#include "product.h"

#define MAX_NAME_LENGTH 32

#ifndef PRODUCT_SAVELOAD
#define PRODUCT_SAVELOAD
void loadProducts(Product *products, int *productAmount);
void saveProducts(Product *products, int *productAmount);
#endif

void saveStartTime(long int startUpdatingTime);
void loadStartTime(long int *startUpdatingTime);