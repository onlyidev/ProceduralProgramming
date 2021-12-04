#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char arr[10];
} Static;

typedef struct {
    char *arr;
} Dynamic;

void changeStatic(Static *el) {
    const char *line = "labas";
    
    strcpy(el->arr, line);
}

void changeDynamic(Dynamic el) {
    const char *line = "labas";

    strcpy(el.arr, line);
}

int main(int argc, char *argv[]) {

    Static stat = {""};
    Dynamic dyn = {NULL};
    dyn.arr = malloc(10);

    changeStatic(&stat);
    changeDynamic(dyn);

    printf("Static: %s\n", stat.arr);
    printf("Dynamic: %s\n", dyn.arr);


    free(dyn.arr);

    return 0;
}

/* 2 fun, 2 struct. 1 struktura turi masyva 10 elementu. struktura funkcijai, iraso zodi labas. Kita turi dinamini is 10 el, funkcija pakeicia masyva, iraso "labas" */