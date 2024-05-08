/*
 * File:   LinkedList.c
 * Author: Rahil Prakash
 *
 * Created on May 5, 2024, 6:13 PM
 *
 */
#include "LinkedList.h"
#include <stdlib.h>
// Defining Std Error & Success for further use
#define STANDARD_ERROR -1
#define SUCCESS 0

ListItem *LinkedListNew(char *data)
{
    ListItem *newItem = malloc(sizeof(ListItem)); // allocate Memory
    if (newItem == NULL)
    {
        return NULL; // Memory allocation failed
    }
    newItem->data = data;         // set the data pointer of the new item to the passed in data paramater
    newItem->previousItem = NULL; // intialize the previousItem pointer to null (new item with no items linked)
    newItem->nextItem = NULL;     // return the pointer to the newly created ListItem (initalized and detached from other items)
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *newItem = malloc(sizeof(ListItem)); // allocate Memory
    if (newItem == NULL)
    {
        return NULL; // Memory allocation failed
    }
    newItem->data = data;
    newItem->nextItem = (item ? item->nextItem : NULL); // Set the 'nextItem' of the new item. If 'item' is not NULL, set it to item's nextItem, linking it to the rest of the list.
                                                        // If 'item' is NULL, set 'nextItem' to NULL, indicating that there are no subsequent items linked to this new item.
    newItem->previousItem = item;                       // set the preiviousItem POINTER of the newItem to point to the item that is passed in

    // logic for inserting a new item into a doubly linked list
    if (item) // if Item is null
    {
        if (item->nextItem) // check if there is a item next to this item
        {
            item->nextItem->previousItem = newItem; // if Item does have a nextItem insert the newItem in the middle of the linked items - maintain the doublely-linked list
        }
        item->nextItem = newItem; // sets the nextItem pointer of item to newItem. Linking newItem directly after item (forward linking)
    }
    return newItem;
}

char *LinkedListRemove(ListItem *item)
{
    if (item == NULL)
    {
        return NULL;
    }
    char *data = item->data; // getting the data of item
    if (item->nextItem)      // checks if there is a node after the item being removed
    {
        item->nextItem->previousItem = item->previousItem; // if so, sets the prevItem pointer to the next node (before item)
    }
    if (item->previousItem) // check if there is a node before the item being removed
    {
        item->previousItem->nextItem = item->nextItem; // if so, adjusts nextItem pointer to bypass the item and directly link to whatver comes after item (could be node or null if 'item' was last on the list)
    }
    free(item); // after unlinking process occurs frees the memory allocated for item
    return data;
}

int LinkedListSize(ListItem *list)
{
    if (list == NULL)
    {
        return 0;
    }
    int count = 0;
    ListItem *current = LinkedListGetFirst(list); // Ensure we start from the first item
    while (current != NULL)                       // while current is not equal to NULL count the node
    {
        count++;                     // count node
        current = current->nextItem; // go to next node
    }
    return count;
}

ListItem *LinkedListGetFirst(ListItem *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    while (list->previousItem != NULL) // loop until the previousItem is null (we are at the first node)
    {
        list = list->previousItem; // move back a node (if not at the start)
    }
    return list;
}

ListItem *LinkedListGetLast(ListItem *list) // same implementation as LinkedListGetFirst just using nextItem instead of previous
{
    if (list == NULL)
    {
        return NULL;
    }
    while (list->nextItem != NULL)
    {
        list = list->nextItem;
    }
    return list;
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem)
{
    if (firstItem == NULL || secondItem == NULL) // checks if either of the inputs are null
    {
        return STANDARD_ERROR;
    }
    char *tempData = firstItem->data;   // creates tempData to hold onto the data pointer of FirstItem while the swap occurs
    firstItem->data = secondItem->data; // the data previously held by secondItem is not pointed to by firstItem (does the swap)
    secondItem->data = tempData;        // assigns the data pointer of secondItem to the tempData (second data is now what first originally held)
    return SUCCESS;
}

#include <stdio.h>

int LinkedListPrint(ListItem *list)
{
    if (list == NULL)
    {
        return STANDARD_ERROR;
    }
    ListItem *start = LinkedListGetFirst(list); // intiazlise starter pointer to the first node in the list
    printf("[");                                // print beginning of list char
    while (start != NULL)                       // iterate through each node in the list starting with the first (until start becomes null)
    {
        printf("%s", start->data ? start->data : "NULL"); // check if start->data is not NULL. if data exists print data is data is null print null
        if (start->nextItem != NULL)                      // checks if the current node is not the last node in the list
        {
            printf(", "); // if it is not the last node print ,
        }
        start = start->nextItem; // move to the next node
    }
    printf("]\n"); // print closing bracket
    return SUCCESS;
}
