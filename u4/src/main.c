#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/stdmain.h"

int main(int argc, char *argv[]) {
    
    /* User Input */
    int num;
    /* END of User Input */

    int i;

    List list = newList();

    srand(time(NULL));

    userInput:

        printf("How many elements should the list have? ");
        scanf("%d", &num);

    if(num < 1) {
        printf("Invalid size. Try again\n");
        goto userInput;
    }
        

    for(i = 0; i < num; ++i)
        addToList(&list, rand());

    printf("Which list item should be removed? ");
    scanf("%d", &num);

    if(removeFromList(&list, num-1) == NULL && list.size)
        printf("Sorry, but that item does not exist\n");

    else 
        printf("Succesfully deleted item No. %d\n", num);


    removeList(&list);

    return 0;
}

/* 
n1. Sudaryti vienpusį sąrašą. Parašyti procedūrą, kuri išmeta numeriu nurodytą elementą.
Jeigu tokio elemento nėra, turi būti išvestas atitinkamas pranešimas.
 */