#include <stdio.h>

/* Gets the definition of the product struct */
#include "product.h"

void productToString(Product product);

#ifndef PRODUCT_SAVELOAD
#define PRODUCT_SAVELOAD
void loadProducts(Product *products, int *productAmount);
void saveProducts(Product *products, int *productAmount);
#endif

int countLinesInFile(FILE *f);

void saveStartTime(int startHour, int startMinute);
void loadStartTime(int *startHour, int *startMinute);