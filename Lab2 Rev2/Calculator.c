// Standard libraries
#include <stdio.h>
#include <math.h>

// User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif

// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand, double operand2);
double AbsoluteValue(double operand1);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);
// add more prototypes here
double Subtract(double operand1, double operand2);
double Divide(double operand1, double operand2);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);
double Round(double operand);
//adding a def for Pi
#ifndef Pi
#define Pi 3.14159265358979323846
#endif

void CalculatorRun(void)
{
    printf("\n\nWelcome to Jonah and Rahil's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);
    // Your code here
    double a = -1, b = -1, result = -1;
    char operation = ' ';
    char validOperationsTwoArgs[] = {'*', '/', '+', '-', 'm'};
    char validOperationsOneArg[] = {'a', 'c', 'f', 't', 'r', 'q'};

    while (1)
    { // infinite loop for the operations
        printf("\nEnter a mathematical operation to perform (*, /, +, -, m, a, c, f, t, r, q to exit): ");
        scanf(" %c", &operation);

        if (operation == 'q')
        {
            printf("Quitting\n");
            break; // exit
        }

        size_t argsRequired = 0; // resetting the nums when a new operation
        for (size_t i = 0; i < sizeof(validOperationsTwoArgs); ++i)
        {
            if (validOperationsTwoArgs[i] == operation)
            {
                argsRequired = 2;
                break;
            }
        }

        for (size_t i = 0; i < sizeof(validOperationsOneArg); ++i)
        {
            if (validOperationsOneArg[i] == operation)
            {
                argsRequired = 1;
                break;
            }
        }

        if (argsRequired == 0)
        {
            printf("Error: Invalid\n");
            continue; // skip when invalid
        }

        if (argsRequired == 1)
        {
            printf("\tEnter the operand: ");
            scanf("%lf", &a);
        }
        else
        {
            printf("\tEnter the first operand: ");
            scanf("%lf", &a);
            printf("\tEnter the second operand: ");
            scanf("%lf", &b);
        }

        // doing actual operations
        switch (operation)
        {
        case '*':
            result = Multiply(a, b);
            break;
        case '/':
            result = Divide(a, b);
            break;
        case '+':
            result = Add(a, b);
            break;
        case '-':
            result = Subtract(a, b);
            break;
        case 'm':
            result = Average(a, b);
            break;
        case 'a':
            result = AbsoluteValue(a);
            break;
        case 'c':
            result = FahrenheitToCelsius(a);
            break;
        case 'f':
            result = CelsiusToFahrenheit(a);
            break;
        case 't':
            result = Tangent(a);
            break;
        case 'r':
            result = Round(a);
            break;
        default:
            printf("Not a valid choice\n");
            continue; // ignore undefined
        }

        // outputs results
        if (operation == 'f' || operation == 'c')
        {
            printf("\tResult of (%.0f deg->%c): %lf", a, (operation - 32), result);
        }

        else if (operation == 't')
        {
            printf("\tResult of tan(%lf): %lf", a, result);
        }

        else if (operation == 'r')
        {
            printf("\tResult of round(%lf): %lf", a, result);
        }

        else if (operation == 'm')
        {
            printf("\tResult of average(%lf, %lf): %lf", a, b, result);
        }

        else if (operation == 'a')
        {
            printf("\tResult of |%lf|: %lf", a, result);
        }

        else if (operation == 'r')
        {
            printf("\tResult of round(%lf): %lf", a, result);
        }

        else
        {
            if (operation == '/' && result == HUGE_VAL)
            {
                printf("\tDivde by zero error!");
            }
            else
            {
                printf("\tResult of (%lf %c %lf): %lf", a, operation, b, result);
            }
        }
        printf("\n");
    }

    BOARD_End();
    while (1);
}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{
    return operand1 + operand2;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
    return operand1 - operand2;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2)
{
    return operand1 * operand2;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
    if (operand2 == 0)
    {
        return HUGE_VAL;

        // FIXME: Should error if divide by zero
    }
    return operand1 / operand2;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand)
{
    if (operand >= 0)
    {
        return operand;
    }

    return operand * -1;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand)
{
    return ((operand - 32) * (5.0f / 9.0f));
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    return (operand * 1.8) + 32;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
    return (operand1 + operand2) / 2;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand)
{
    return tan(operand * (Pi / 180));
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{
    double round_direction = AbsoluteValue(operand);
    int negative;

    if (operand < 0)
    {
        negative = -1;
    }
    else
    {
        negative = 1;
    }

    while (round_direction > 1)
    {
        round_direction--;
    }
    if (round_direction < .5f)
    {
        return operand - (round_direction * negative);
    }

    return operand + negative * (1.0f - round_direction);
}
