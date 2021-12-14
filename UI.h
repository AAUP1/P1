#include "product.h"

#define SCREENWIDTH 112

void drawBox(char*, int, int, int);
void line(char);
void listItem(int, int, Product *);
void editListItem(int, int, int, Product *);
void overviewUI();
void editviewUI();
void drawtitle();
void controls(int currentState);