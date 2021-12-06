#include <stdio.h>

/* Gets the definition of the product struct */
#include "product.h"

void productToString(Product product);

void loadProducts(Product *products, int productAmount, FILE *file);
void saveProducts(Product *products, int productAmount, FILE *file);

/*void loadGlobals(int *globals, int globalAmount, FILE *file) {

}
void saveGlobals(int *globals, int globalAmount, FILE *file) {

}*/