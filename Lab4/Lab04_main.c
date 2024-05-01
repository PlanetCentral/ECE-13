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

        // Various error cases (5/5)
        switch (returnVal) {
            case 1:
                sprintf(printString, "ERROR: There is no more room on the stack.\n");
                break;
            case 2:
                sprintf(printString, "ERROR: There aren't enough operands before the operator.\n");
                break;
            case 3:
                sprintf(printString, "ERROR: Invalid characters used in the RPN String.\n");
                break;
            case 4:
                sprintf(printString, "ERROR: Invalid RPN calculation; divided by 0.\n");
                break;
            case 5:
                sprintf(printString, "ERROR: Invalid RPN calculation; no items on the stack.\n");
                break;
            case 6:
                sprintf(printString, "ERROR: Invalid RPN calculation; too many items on the stack.\n");
                break;
            case ERROR_EXCEED_INPUT_LENGTH:
                sprintf(printString, "ERROR: Input string length exceeds 60 characters. At maximum please enter 60 characters.\n");
                break;
            default:
                sprintf(printString, "Result = %lf\n", result);
                break;
        }

        printf("%s", printString);
    }

    return 0;
}
