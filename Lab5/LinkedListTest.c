/*
 * File:   LinkedListTest.c
 * Author: Rahil Prakash
 *
 * Created on May 5, 2024, 6:14 PM
 *
 */
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

// Function prototypes for test functions
void testLinkedListNew();
void testLinkedListCreateAfter();
void testLinkedListRemove();
void testLinkedListSize();
void testLinkedListGetFirst();
void testLinkedListGetLast();
void testLinkedListPrint();

int main()
{
    printf("Testing LinkedList Functions\n");
    testLinkedListNew();
    testLinkedListCreateAfter();
    testLinkedListRemove();
    testLinkedListSize();
    testLinkedListGetFirst();
    testLinkedListGetLast();
    testLinkedListPrint();
    printf("All tests completed.\n");
    return 0;
}

void testLinkedListNew()
{
    printf("\nTesting LinkedListNew...\n");
    char *data = "Test data";
    ListItem *item = LinkedListNew(data); // setup
    if (item && item->data == data)       // validate
    {
        printf("PASS: LinkedListNew created a new item.\n");
    }
    else
    {
        printf("FAIL: LinkedListNew did not work as expected.\n");
    }
    free(item); // Cleanup
}

void testLinkedListCreateAfter()
{
    printf("\nTesting LinkedListCreateAfter...\n");
    ListItem *first = LinkedListNew("First"); // setup
    ListItem *second = LinkedListCreateAfter(first, "Second");
    if (second && second->previousItem == first && first->nextItem == second) // validate
    {
        printf("PASS: LinkedListCreateAfter linked items correctly.\n");
    }
    else
    {
        printf("FAIL: LinkedListCreateAfter failed to link items correctly.\n");
    }
    free(first);
    free(second);
}

void testLinkedListRemove()
{
    printf("\nTesting LinkedListRemove...\n");
    ListItem *item = LinkedListNew("To be removed"); // setup
    char *data = LinkedListRemove(item);
    if (data && !item->nextItem && !item->previousItem) // validate
    {
        printf("PASS: LinkedListRemove removed the item correctly.\n");
    }
    else
    {
        printf("FAIL: LinkedListRemove failed.\n");
    }
    free(item); // Cleanup
}

void testLinkedListSize()
{
    printf("\nTesting LinkedListSize...\n");
    ListItem *first = LinkedListNew("First"); // setup
    ListItem *second = LinkedListCreateAfter(first, "Second");
    if (LinkedListSize(first) == 2) // validate
    {
        printf("PASS: LinkedListSize reported correct size.\n");
    }
    else
    {
        printf("FAIL: LinkedListSize reported incorrect size.\n");
    }
    LinkedListRemove(second);
    LinkedListRemove(first);
}

void testLinkedListGetFirst()
{
    printf("\nTesting LinkedListGetFirst...\n");
    ListItem *first = LinkedListNew("First"); // setup
    ListItem *second = LinkedListCreateAfter(first, "Second");
    if (LinkedListGetFirst(second) == first) // validate
    {
        printf("PASS: LinkedListGetFirst found the first item correctly.\n");
    }
    else
    {
        printf("FAIL: LinkedListGetFirst did not find the first item.\n");
    }
    LinkedListRemove(second);
    LinkedListRemove(first);
}

void testLinkedListGetLast()
{
    printf("\nTesting LinkedListGetLast...\n");
    ListItem *first = LinkedListNew("First"); // setup
    ListItem *second = LinkedListCreateAfter(first, "Second");
    if (LinkedListGetLast(first) == second) // validate
    {
        printf("PASS: LinkedListGetLast found the last item correctly.\n");
    }
    else
    {
        printf("FAIL: LinkedListGetLast did not find the last item.\n");
    }
    LinkedListRemove(second);
    LinkedListRemove(first);
}

void testLinkedListPrint()
{
    printf("\nTesting LinkedListPrint...\n");
    ListItem *first = LinkedListNew("First");
    ListItem *second = LinkedListCreateAfter(first, "Second");
    printf("Expected output: [First, Second]\nActual output: ");
    LinkedListPrint(first);
    LinkedListRemove(second);
    LinkedListRemove(first);
}
