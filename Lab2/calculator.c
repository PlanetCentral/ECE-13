/*
 * File: calculator.c
 * Author: Rahil Prakash (rprakas2@ucsc.edu), Jonah Guardino (jdguardi@ucsc.edu)
 * Created on April 08, 2023, 9:02 PM
 */
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
double Multiply(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);

//add more prototypes here
double CelsiusToFahrenheit(double celsius); 
double Tangent(double degrees);
double Average(double operand1, double operand2);
double Round(double operand);
double Subtract(double operand1, double operand2);
double Divide(double operand1, double operand2);
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to handle input errors and prompt user
void PromptForInput(const char *prompt, double *operand);

void CalculatorRun(void)
{
    printf("\n\nWelcome to Rahil and Jonah's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);

    // Main calculator loop
    char operation = '0';
    while (operation != 'q')
    {
        printf("\nSelect an operation (*, /, +, -, m, a, c, f, t, q, r): ");
        scanf(" %c", &operation); // Spaces before %c for any newline chars

        double op1, op2, result;
        if (operation == 'q')
        {
            break; // Quits calculator
        }

        // Checks ops that need 1 operand
        if (operation == 'a' || operation == 'c' || operation == 'f' || operation == 't' || operation == 'r')
        {
            PromptForInput("Enter the operand: ", &op1);
            // Unary ops
        }
        else
        {
            // Ops needing 2 operands
            PromptForInput("Enter first operand: ", &op1);
            PromptForInput("Enter second operand: ", &op2);
        }

        // Do ops
        switch (operation)
        {
        case '*':
            result = Multiply(op1, op2);
            printf("Result of (%f * %f): %f\n", op1, op2, result);
            break;
        case '/':
            result = Divide(op1, op2);
            printf("Result of (%f / %f): %f\n", op1, op2, result);
            break;
        case '+':
            result = Add(op1, op2);
            printf("Result of (%f + %f): %f\n", op1, op2, result);
            break;
        case '-':
            result = Subtract(op1, op2);
            printf("Result of (%f - %f): %f\n", op1, op2, result);
            break;
        case 'm':
            result = Average(op1, op2);
            printf("Result of the average of %f and %f: %f\n", op1, op2, result);
            break;
        case 'a':
            result = AbsoluteValue(op1);
            printf("Result of |%f|: %f\n", op1, result);
            break;
        case 'c':
            result = FahrenheitToCelsius(op1);
            printf("Result of (%f deg->C): %f\n", op1, result);
            break;
        case 'f':
            result = CelsiusToFahrenheit(op1);
            printf("Result of (%f deg->F): %f\n", op1, result);
            break;
        case 't':
            result = Tangent(op1);
            printf("Result of tan(%f): %f\n", op1, result);
            break;
        case 'r':
            result = Round(op1);
            printf("Result of round(%f): %f\n", op1, result);
            break;
        default:
            printf("Error: Invalid operation\n");
            break;
        }
    }

    BOARD_End();
    while (1)
        ; // To ensure the program doesn't end
}

// Function for handling input errors user prompts
void PromptForInput(const char *prompt, double *operand)
{
    int inputValid;
    do
    {
        printf("%s", prompt);
        inputValid = scanf(" %lf", operand);
        while (getchar() != '\n')
            ; // Clear the buffer
        if (inputValid != 1)
        {
            printf("Error: Invalid input\n");
        }
    } while (inputValid != 1);
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
        printf("Error: Division by zero.\n");
        return HUGE_VAL; // return a value to represent infinity
    }
    return operand1 / operand2;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand)
{
    return fabs(operand);
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32) * 5 / 9;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double celsius)
{
    return (celsius * 9 / 5) + 32;
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
double Tangent(double degrees)
{
    // Conversion from degrees to radians
    return tan(degrees * M_PI / 180);
}

/*********************************************************************************
 * Define the Round function here.
 ********************************************************************************/
double Round(double operand)
{
    return (operand > 0.0) ? floor(operand + 0.5) : ceil(operand - 0.5);
}
