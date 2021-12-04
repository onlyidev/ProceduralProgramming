#include <gtest/gtest.h>

extern "C" {
    #include "../lib/stdmain.h"
}

TEST(ListNew, nullInit) {
    List list = newList();
    EXPECT_EQ(NULL, list.begin);
    removeList(&list);
}

TEST(ListNew, zeroSize) {
    List list = newList();
    EXPECT_EQ(list.size, 0);
    removeList(&list);
}

TEST(ListNew, gtSizeOfInt) {
    List list = newList();
    EXPECT_GT(sizeof(list), sizeof(int));
    removeList(&list);
}

TEST(ListNew, nullLogic) {
    List list = newList();
    EXPECT_FALSE(list.begin);
    removeList(&list);
}

TEST(ListAdd, setListBeginOnFirst) {
    List list = newList();
    ListItem *begin = list.begin;
    addToList(&list, 5);
    EXPECT_NE(begin, list.begin);
    removeList(&list);
}

TEST(ListAdd, correctData) {
    List list = newList();

    int data = 5;
    addToList(&list, data);    

    EXPECT_EQ(data, list.begin->data);

    data = 6;
    addToList(&list, data);
    EXPECT_NE(data, list.begin->data);
    removeList(&list);

}

TEST(ListAdd, correctReturn) {
    List list = newList();
    ListItem *item = addToList(&list, 5);
    EXPECT_EQ(item, list.begin);
    
    item = addToList(&list, 5);
    EXPECT_EQ(item, list.begin->next);
    removeList(&list);
}

TEST(ListAdd, sizeIncrease) {
    List list = newList();
    ListItem *item = addToList(&list, 5);
    EXPECT_EQ(list.size, 1);
    removeList(&list);
}

TEST(ListRemove, changeListDescriptor) {
    List list = newList();
    for(int i = 0; i < 3; ++i)
        addToList(&list, i);
    
    ListItem *nth = list.begin;

    removeFromList(&list, 0);

    EXPECT_NE(nth, list.begin);
    removeList(&list);
}


TEST(ListRemove, changeListSize) {
    List list = newList();
    for(int i = 0; i < 3; ++i)
        addToList(&list, i);
    
    removeFromList(&list, 0);

    EXPECT_EQ(list.size, 2);
    removeList(&list);
}

TEST(ListRemove, edgeCase) {
    List list = newList();
    addToList(&list, 5);
    
    removeFromList(&list, 0);

    EXPECT_EQ(NULL, list.begin);
    removeList(&list);
}

TEST(ListFree, beginPointer) {
    List list = newList();

    addToList(&list, 1);

    ListItem *ptr = list.begin;

    removeList(&list);

    EXPECT_NE(list.begin, ptr);
    EXPECT_EQ(NULL, list.begin);
}

TEST(ListFree, sizeZero) {
    List list = newList();

    addToList(&list, 1);

    ListItem *ptr = list.begin;

    removeList(&list);

    EXPECT_EQ(list.size, 0);
}