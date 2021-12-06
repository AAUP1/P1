struct Product {
    char* name;
    int startAmount;
    int currentAmount;
    int amountDecrement;
    int startPrice;
    int currentPrice;
    int priceDecrement;
};

void loadProducts(Product *products, int productAmount, FILE *file);
void saveProducts(Product *products, int productAmount, FILE *file);

/*void loadGlobals(int *globals, int globalAmount, FILE *file) {

}
void saveGlobals(int *globals, int globalAmount, FILE *file) {

}*/