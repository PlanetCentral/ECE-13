/*
 * File:   stack.c
 * Author: Rahil Prakash
 *
 * Created on April 28, 2024, 2:08 PM
 *
 */
#include "stack.h" // Include the header file for definitions and prototypes

// Initializes the stack
void StackInit(struct Stack *stack)
{
    stack->currentItemIndex = -1; // Set the top index to -1 indicating an empty stack
    stack->initialized = TRUE;    // Set the initialized flag to TRUE
}

// Pushes a value onto the stack
int StackPush(struct Stack *stack, double value)
{
    if (!stack->initialized || StackIsFull(stack))
    {
        return STANDARD_ERROR; // Return error if stack is not initialized or full
    }
    stack->currentItemIndex++;                          // Increment the top index
    stack->stackItems[stack->currentItemIndex] = value; // Place the value at the new top of the stack
    return SUCCESS;                                     // Return success
}

// Pops a value from the stack
int StackPop(struct Stack *stack, double *value)
{
    if (!stack->initialized || StackIsEmpty(stack))
    {
        return STANDARD_ERROR; // Return error if stack is not initialized or empty
    }
    *value = stack->stackItems[stack->currentItemIndex]; // Retrieve the top value from the stack
    stack->currentItemIndex--;                           // Decrement the top index
    return SUCCESS;                                      // Return success
}

// Checks if the stack is empty
int StackIsEmpty(const struct Stack *stack)
{
    return (stack->initialized && stack->currentItemIndex == -1) ? TRUE : FALSE;
}

// Checks if the stack is full
int StackIsFull(const struct Stack *stack)
{
    return (stack->initialized && stack->currentItemIndex == STACK_SIZE - 1) ? TRUE : FALSE;
}

// Returns the current size of the stack
int StackGetSize(const struct Stack *stack)
{
    if (!stack->initialized)
    {
        return SIZE_ERROR; // Return error if the stack is not initialized
    }
    return stack->currentItemIndex + 1; // Return the number of elements in the stack
}
