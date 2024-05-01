// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Support Library
#include "BOARD.h"

// User libraries
#include "rpn.h"

int main()
{
    BOARD_Init();
    int error;
    double result;

    printf("\n###### Beginning Rahil's rpn test harness: ####\n\n");

    // Test basic addition
    char test0[] = "1 1 +";
    double expected0 = 2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result);
    if (error)
    {
        printf("   Failed, RPN_Evaluate produced an error\n");
    }
    else if (result != expected0)
    {
        printf("   Failed, expected = %f, result = %f\n", expected0, result);
    }
    else
    {
        printf("   Success!\n");
    }

    // Test subtraction that results in negative result
    char test1[] = "1 3 -";
    double expected1 = -2;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test1);
    error = RPN_Evaluate(test1, &result);
    if (error)
    {
        printf("   Failed, RPN_Evaluate produced an error\n");
    }
    else if (result != expected1)
    {
        printf("   Failed, expected = %f, result = %f\n", expected1, result);
    }
    else
    {
        printf("   Success!\n");
    }

    // Test multiplication
    char test2[] = "2 3 *";
    double expected2 = 6;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test2);
    error = RPN_Evaluate(test2, &result);
    if (error)
    {
        printf("   Failed, RPN_Evaluate produced an error\n");
    }
    else if (result != expected2)
    {
        printf("   Failed, expected = %f, result = %f\n", expected2, result);
    }
    else
    {
        printf("   Success!\n");
    }

    // Test division
    char test3[] = "10 5 /";
    double expected3 = 2;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test3);
    error = RPN_Evaluate(test3, &result);
    if (error)
    {
        printf("   Failed, RPN_Evaluate produced an error\n");
    }
    else if (result != expected3)
    {
        printf("   Failed, expected = %f, result = %f\n", expected3, result);
    }
    else
    {
        printf("   Success!\n");
    }

    // Test division by zero
    char test4[] = "10 0 /";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test4);
    error = RPN_Evaluate(test4, &result);
    if (error == RPN_ERROR_DIVIDE_BY_ZERO)
    {
        printf("   Success, caught divide by zero!\n");
    }
    else
    {
        printf("   Failed, did not catch divide by zero.\n");
    }

    // Test ProcessBackspaces
    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "123\b\b4";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 14\n");

    BOARD_End();
    while (1)
        ;
}
