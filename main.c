#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int i = 0;
int is_cool(int number);

int main(void) {
    printf("Yo, throw me a swag number!\n");
    scanf("%d", &i);
    is_cool(i);
}

int is_cool(int number) {
    if(number == 69 || number == 420 || number == 21) {
        printf("nice");
        return 1;
    } else{
        printf("poo poo");
    }
    return 0;
}
