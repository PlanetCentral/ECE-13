#include "stack.h"
#include "BOARD.h"
#include <stdio.h>

// Function prototypes for test cases
void testStackInit();
void testStackPush();
void testStackPop();
void testStackIsEmpty();
void testStackIsFull();
void testStackGetSize();

int main()
{
    BOARD_Init(); // Initialize the BOARD

    printf("\n###### Beginning Rahil's stack test harness: ####\n\n");

    // Test Stack Initialization
    testStackInit();

    // Test Stack Push functionality
    testStackPush();

    // Test Stack Pop functionality
    testStackPop();

    // Test if the stack correctly identifies when it is empty
    testStackIsEmpty();

    // Test if the stack correctly identifies when it is full
    testStackIsFull();

    // Test getting the size of the stack
    testStackGetSize();

    BOARD_End(); // Clean up and end testing
    while (1)
        ; // Keep the program alive
    return 0;
}

void testStackInit()
{
    printf("Testing Stack Initialization...\n");
    struct Stack s;
    StackInit(&s);
    if (s.initialized == TRUE && s.currentItemIndex == -1)
    {
        printf("PASS: Stack initialized correctly.\n");
    }
    else
    {
        printf("FAIL: Stack not initialized correctly.\n");
    }
}

void testStackPush()
{
    printf("Testing Stack Push...\n");
    struct Stack s;
    StackInit(&s);
    int result = StackPush(&s, 10.0);
    if (result == SUCCESS && s.stackItems[0] == 10.0 && s.currentItemIndex == 0)
    {
        printf("PASS: Push successful.\n");
    }
    else
    {
        printf("FAIL: Push unsuccessful.\n");
    }

    // Test pushing onto a full stack (edge case)
    for (int i = 1; i < STACK_SIZE; i++)
    {
        StackPush(&s, i);
    }
    result = StackPush(&s, 100.0);
    if (result == STANDARD_ERROR)
    {
        printf("PASS: Correctly identified full stack on push.\n");
    }
    else
    {
        printf("FAIL: Did not identify full stack on push.\n");
    }
}

void testStackPop()
{
    printf("Testing Stack Pop...\n");
    struct Stack s;
    StackInit(&s);
    StackPush(&s, 20.0);
    double poppedValue = 0;
    int result = StackPop(&s, &poppedValue);
    if (result == SUCCESS && poppedValue == 20.0 && s.currentItemIndex == -1)
    {
        printf("PASS: Pop successful.\n");
    }
    else
    {
        printf("FAIL: Pop unsuccessful.\n");
    }

    // Test popping from an empty stack
    result = StackPop(&s, &poppedValue);
    if (result == STANDARD_ERROR)
    {
        printf("PASS: Correctly identified empty stack on pop.\n");
    }
    else
    {
        printf("FAIL: Did not identify empty stack on pop.\n");
    }
}

void testStackIsEmpty()
{
    printf("Testing Stack IsEmpty...\n");
    struct Stack s;
    StackInit(&s);
    if (StackIsEmpty(&s) == TRUE)
    {
        printf("PASS: Stack is correctly identified as empty.\n");
    }
    else
    {
        printf("FAIL: Stack incorrectly identified as not empty.\n");
    }
}

void testStackIsFull()
{
    printf("Testing Stack IsFull...\n");
    struct Stack s;
    StackInit(&s);
    for (int i = 0; i < STACK_SIZE; i++)
    {
        StackPush(&s, i);
    }
    if (StackIsFull(&s) == TRUE)
    {
        printf("PASS: Stack is correctly identified as full.\n");
    }
    else
    {
        printf("FAIL: Stack incorrectly identified as not full.\n");
    }
}

void testStackGetSize()
{
    printf("Testing Stack GetSize...\n");
    struct Stack s;
    StackInit(&s);
    StackPush(&s, 10.0);
    StackPush(&s, 20.0);
    if (StackGetSize(&s) == 2)
    {
        printf("PASS: Stack size correctly reported as 2.\n");
    }
    else
    {
        printf("FAIL: Stack size incorrectly reported.\n");
    }
}
