/*
 * File:   rpn.c
 * Author: Rahil Prakash
 *
 * Created on April 28, 2024, 2:09 PM
 *
 */
#include "rpn.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int RPN_Evaluate(char *rpn_string, double *result)
{
    struct Stack s;
    StackInit(&s);
    char *token = strtok(rpn_string, " "); // tokenizing the input by soaces
    double a, b;

    while (token != NULL) // while there is tokens to read
    {
        if (isdigit(token[0]) || ((token[0] == '-' || token[0] == '+') && isdigit(token[1])))
        {
            // It's a number
            double value = atof(token);
            if (StackIsFull(&s)) // Error Handling
            {
                return RPN_ERROR_STACK_OVERFLOW; // Error Handling overflow
            }
            StackPush(&s, value);
        }
        else
        {
            // It's an operator
            if (StackGetSize(&s) < 2) // Error Handling
            {
                return RPN_ERROR_TOO_FEW_ITEMS_REMAIN; // Error Handling underflow
            }
            StackPop(&s, &b); // pop the operands
            StackPop(&s, &a);
            switch (token[0])
            {
            case '+':
                *result = a + b;
                break;
            case '-':
                *result = a - b;
                break;
            case '*':
                *result = a * b;
                break;
            case '/':
                if (b == 0) // Error Handling
                {
                    return RPN_ERROR_DIVIDE_BY_ZERO; // Error Handling dividing by zero
                }
                *result = a / b;
                break;
            default:
                return RPN_ERROR_INVALID_TOKEN; // Error Handling if token is invalid
            }
            StackPush(&s, *result);
        }
        token = strtok(NULL, " "); // next token
    }

    if (StackGetSize(&s) == 1) // Error Handling if stackgetSize returns 1
    {
        StackPop(&s, result);
        return RPN_NO_ERROR;
    }
    else if (StackGetSize(&s) > 1) // Error Handling
    {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN; // Error Handling # of items on stack
    }
    else
    {
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN; // Error Handling
    }
}

int ProcessBackspaces(char *rpn_sentence)
{
    int write_index = 0;

    for (int read_index = 0; rpn_sentence[read_index] != '\0'; ++read_index)
    {
        if (rpn_sentence[read_index] == '\b')
        {
            if (write_index > 0)
            { // Make sure there's something to backspace
                write_index--;
            }
        }
        else
        {
            rpn_sentence[write_index++] = rpn_sentence[read_index];
        }
    }
    rpn_sentence[write_index] = '\0'; // Terminate the adjusted string
    return write_index;               // Return the new length of the string
}
