#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_cool(int number);

int main(void) {
    is_cool(21);
}

int is_cool(int number) {
    if(number == 69 || number == 420) {
        printf("nice");
        return 1;
    } else{
        printf("poo poo");
    }
    return 0;
}
