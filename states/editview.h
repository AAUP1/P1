#include "state.h"
#include "overview.h"


struct EditView {
    char searchText[MAX_TEXT_LENGTH];
    int searchTextLength;
    int editingIndex;
    Product *editingProduct;
    Product tempProduct;
    
    char popupText[512], *popupLeftText, *popupRightText;
    int popupIsActivated;
    int selectedPopupButton;
    void (*popupFunction)(struct EditView *, Overview *);
};
typedef struct EditView EditView;

void initEditView(EditView* edit_view);
void updateEditView(EditView* edit_view, Overview *overview, StateType *currentState, int input);
void drawEditView(EditView* edit_view, Overview *overview, Product *product);

void drawEditProducts(Overview *overview, EditView *editView);

Product *findProduct(char *name, Product *products, int productAmount);

void drawPopup(EditView *editView);
void updatePopup(EditView *editView, Overview *overview, int input);
void showPopup(EditView *editView, char *popupText, char *popupLeftText, char *popupRightText, void (*f)(EditView *, Overview *));
void hidePopup(EditView *editView, Overview *overview);

void initiateEditing(EditView *editView, Overview *overview);
void checkForAbnormalities(EditView *editView, Overview *overview);
void completeEditing(EditView *editView, Overview *overview);