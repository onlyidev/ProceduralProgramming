#include "stdmain.h"
#include <stdlib.h>

List newList(void) {

    List list = {NULL, 0};

    return list;
}

ListItem *addToList(List *list, int data) {

    ListItem *item = malloc(sizeof(ListItem));
    item->data = data;
    item->next = NULL;

    if(!list->size)
        list->begin = item;
    else
        getListItem(list, list->size-1)->next = item;

    ++list->size;

    return item;
}

ListItem *removeFromList(List *list, int index) {
    if(index < 0 || index >= list->size) 
        return NULL;

    ListItem *prev = NULL;
    ListItem *curr = NULL;

    if(index) {
        prev = getListItem(list, index-1);
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
    
    return list->begin;
}

ListItem *getListItem(List *list, int index) {
    int i;
    ListItem *item = list->begin;
    for(i = 0; i < index; ++i) 
        item = item->next;
        
    return item;
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