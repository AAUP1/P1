#ifndef BOX_DEFINED
#define BOX_DEFINED
struct Box {
    int x, y;
    char* text;
    int active;
};
typedef struct Box Box;
#endif

void initBox(Box* box, int x, int y, char* text);
void drawBox(char*, int, int, int);
void drawStructBox(Box* box);