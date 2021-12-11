#include "stdmain.h"
#include <stdlib.h>
#include <stdio.h>

List newList(void) {

    List list = {NULL, 0, };

    return list;
}

ListItem *getListItem(List *list, int index) {
    int i;

    index = list->size - index - 1;

    ListItem *item = list->begin;

    for(i = 0; i < index; ++i) 
        item = item->next;
        
    return item;
}

void addToList(List *list, int data) {

    ListItem *item = malloc(sizeof(ListItem));
    item->data = data;
    item->next = list->begin;

    list->begin = item;

    ++list->size;

    return;
}

char removeFromList(List *list, int index) {
    if(index < 0 || index >= list->size) 
        return 0;

    ListItem *prev = NULL;
    ListItem *curr = NULL;

     if(index != list->size - 1) {
        prev = getListItem(list, index+1);
        curr = prev->next;
    }
    else 
        curr = list->begin;

    --list->size;

    if(curr == list->begin)
        list->begin = curr->next;
    else
        prev->next = curr->next;

    free(curr);
    
    return 1;
}

void removeList(List *list) {
    ListItem *curr = list->begin;
    ListItem *prev = NULL;

    while(list->size > 0) {
        prev = curr;
        curr = curr->next;
        free(prev);
        --list->size;
    }

    list->begin = NULL;

    return;
}

void printList(List *list) {
    int *arr = malloc(sizeof(int) * list->size);
    int i;

    ListItem *curr = list->begin;

    for(i = list->size-1; i >= 0; --i) {
        arr[i] = curr->data;
        curr = curr->next;
    }

    for(i = 0; i < list->size; ++i)
        printf("Number: %d; Element: %d\n", i+1, arr[i]);

    free(arr);

    return;
}