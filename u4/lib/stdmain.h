#pragma once

/* Documentation available at:  */

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
ListItem *addToList(List *, int);
ListItem *removeFromList(List *, int);
ListItem *getListItem(List *, int);
void removeList(List *);