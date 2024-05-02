// **** Include libraries here ****
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Support Library
#include "BOARD.h"

// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
#define MAX_INPUT_LENGTH 60
#define ERROR_EXCEED_INPUT_LENGTH 7

int main() {
    BOARD_Init();
    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    int returnVal;
    char printString[MAX_INPUT_LENGTH + 50];  // Increased buffer size for the error messages.

    printf("Welcome to Rahil's RPN calculator. Compiled on %s %s.\n", __DATE__, __TIME__);

    while (1) {
        printf("Enter floats and + - / * in RPN format, for example, '1 2 +':\n");

        if (fgets(rpn_sentence, sizeof(rpn_sentence), stdin) == NULL) {
            continue;  // Handles unexpected errors in the input.
        }

        // Finds and replace the newline chars with a null terminator.
        int iter = 0;
        while (rpn_sentence[iter] != '\n' && rpn_sentence[iter] != '\0') {
            iter++;
        }
        rpn_sentence[iter] = '\0';

        // Checks if the input length exceeds the max length.
        if (iter > MAX_INPUT_LENGTH) {
            returnVal = ERROR_EXCEED_INPUT_LENGTH;
        } else {
            ProcessBackspaces(rpn_sentence);
            returnVal = RPN_Evaluate(rpn_sentence, &result);
        }

        // Various error cases
        switch (returnVal)
        {
            // Stack overflow
        case 1:
            sprintf(printString, "Error: Stack overflow.\n");
            break;
            //Invalid char
        case 2:
            sprintf(printString, "Error: Invalid character in the RPN string.\n");
            break;
            // Divide by 0
        case 3:
            sprintf(printString, "Error: Division by 0 attempted.\n");
            break;
            // Stack underflow
        case 4:
            sprintf(printString, "Error: Stack underflow.\n");
            break;
            // >60 chars
        case 5:
            sprintf(printString, "Error: Input exceeds maximum length of 60 characters. Please at maximum, enter 60 characters.\n");
            break;
            // None
        default:
            sprintf(printString, "Result = %lf\n", result);
            break;
        }
        printf("%s", printString);
    }
    return 0;
}
