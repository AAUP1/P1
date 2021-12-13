#include "state.h"
#include "overview.h"


struct EditView {
    char searchText[MAX_TEXT_LENGTH];
    int searchTextLength;
    int editingIndex;
    Product *editingProduct;
    Product tempProduct;
};
typedef struct EditView EditView;

void initEditView(EditView* edit_view);
void updateEditView(EditView* edit_view, Overview *overview, StateType *currentState, int input);
void drawEditView(EditView* edit_view, Overview *overview, Product *product);

void drawEditProducts(Overview *overview, EditView *editView);

Product *findProduct(char *name, Product *products, int productAmount);