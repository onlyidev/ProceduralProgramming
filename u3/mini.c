#include <stdio.h>
#include <stdlib.h>

void insertNumbers(int **ptr) {
    *ptr = malloc(sizeof (int) * 3);

    for(int i = 0; i < 3; ++i) 
        (*ptr)[i] = i+1;
}

int main() {

    int *ptr = NULL;

    insertNumbers(&ptr);

    for(int i = 0; i < 3; ++i)
        printf("%d\n", ptr[i]);

    free(ptr);

    return 0;
}
