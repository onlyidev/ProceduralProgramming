#pragma once

typedef struct ListItem ListItem;

struct ListItem {
    int data;
    ListItem *next;
};

typedef struct {
    struct ListItem *begin;
    int size;
} List;

List newList(void);
void addToList(List *, int);
char removeFromList(List *, int);

void printList(List *);
void removeList(List *);
ListItem *getListItem(List *, int);
