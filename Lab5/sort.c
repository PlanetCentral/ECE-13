// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

// CMPE13 Support Library
#include "BOARD.h"

// User libraries
#include "LinkedList.h"

// **** Declare any function prototypes here ***
ListItem *CreateUnsortedList(void); // this function has been written for you
ListItem *SelectionSort(ListItem *list);
ListItem *InsertionSort(ListItem *list);

/* Students should not need to modify main! */
int main(void)
{
    BOARD_Init();

    printf("\n\nWelcome to Rahil's sort.c, compiled on %s %s.\n", __DATE__, __TIME__);

    ListItem *listToSort;

    // Do a timing test
    printf("\nStarting stopwatch for selection sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); // put a breakpoint on this line
    listToSort = SelectionSort(listToSort);
    __asm("nop"); // put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);

    printf("\nStarting stopwatch for insertion sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); // put a breakpoint on this line
    listToSort = InsertionSort(listToSort);
    __asm("nop"); // put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);

    BOARD_End();
    while (1)
        ;
    return 0;
}

/**
 * SelectionSort() performs a selection sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().
 *
 * @param list Any element in a linked list to sort.
 * @return a pointer to the head of the sorted list.
 *
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 *
 * This function does not print.
 */

ListItem *SelectionSort(ListItem *list)
{
    if (!list)
        return NULL; // Return immediately if list is NULL

    ListItem *head = LinkedListGetFirst(list); // Ensure we start from the first node of the list (head)
    ListItem *current, *index, *min;           // create the variables we need

    for (current = head; current != NULL; current = current->nextItem) // Iterate over each item in the list
    {
        min = current;
        for (index = current->nextItem; index != NULL; index = index->nextItem) // for loop to find the smallest item in the list
                                                                                // index = firstItem       while index is not NULL    iterate to nextItem
        {
            if (strcmp(index->data, min->data) < 0)
            {
                min = index;
            }
        }
        if (min != current) // Swap the data of the current node with the min node
        {
            char *temp = current->data;
            current->data = min->data;
            min->data = temp;
        }
    }
    return head;
}

ListItem *InsertionSort(ListItem *list)
{
    if (!list)
        return NULL; // Return immediately if list is NULL

    ListItem *sorted = NULL;
    ListItem *current = list;
    ListItem *next;

    while (current != NULL)
    {
        next = current->nextItem; // Store next for the next iteration
        ListItem *loc = sorted;
        ListItem *prev = NULL;

        // Find the insertion location
        while (loc != NULL && strcmp(loc->data, current->data) < 0)
        // while loc is not null and the sort logic (loc comes b4 current in alphabet)
        {
            prev = loc;
            loc = loc->nextItem;
        }

        if (prev == NULL)
        { // Insert at the beginning
            current->nextItem = sorted;
            sorted = current;
        }
        else
        { // Insert between prev and loc
            current->nextItem = loc;
            prev->nextItem = current;
        }
        current = next;
    }
    return sorted;
}
ListItem *CreateUnsortedList(void)
/// <editor-fold defaultstate="collapsed" desc="CreateUnsortedList definition">
{
    char *wordList[] = {
        "decide", "toothpaste", "lowly", "robin", "reign", "crowd",
        "pies", "reduce", "tendency", "surround", "finger", "rake",
        "alleged", "hug", "nest", "punishment", "eggnog", "side",
        "beef", "exuberant", "sort", "scream", "zip", "hair",
        "ragged", "damage", "thought", "jump", "frequent", "substance",
        "head", "step", "faithful", "sidewalk", "pig", "raspy",
        "juggle", "shut", "maddening", "rock", "telephone", "selective",
        NULL};
    //  char* wordList[] = {"D", "A", "C", "E", "B", NULL};

    int i = 0;
    ListItem *head = LinkedListNew(wordList[i]);
    ListItem *tail = head;
    for (i = 1; wordList[i] != NULL; i++)
    {
        tail = LinkedListCreateAfter(tail, wordList[i]);
        if (tail == NULL)
        {
            printf("ERROR:  Heap full! Please increase heap size.\n");
            FATAL_ERROR();
        }
    }
    return head;
}
