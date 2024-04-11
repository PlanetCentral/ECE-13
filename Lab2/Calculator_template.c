// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
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

    void CalculatorRun(void)
{
    printf("\n\nWelcome to Rahil's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);

    char operation = '0';
    while (operation != 'q')
    {
        printf("\nSelect an operation (*, /, +, -, m, a, c, f, t, q, r): ");
        scanf(" %c", &operation);

        if (operation == 'q')
            break;

        double operand1 = 0, operand2 = 0, result = 0;
        if (operation == 'a' || operation == 'c' || operation == 'f' || operation == 't' || operation == 'r')
        {
            printf("Enter operand: ");
            scanf("%lf", &operand1);
        }
        else
        {
            printf("Enter first operand: ");
            scanf("%lf", &operand1);
            printf("Enter second operand: ");
            scanf("%lf", &operand2);
        }

        switch (operation)
        {
        case '*':
            result = Multiply(operand1, operand2);
            printf("Result: %.2lf\n", result);
            break;
        case '/':
            result = Divide(operand1, operand2);
            printf("Result: %.2lf\n", result);
            break;
        case '+':
            result = Add(operand1, operand2);
            printf("Result: %.2lf\n", result);
            break;
        case '-':
            result = Subtract(operand1, operand2);
            printf("Result: %.2lf\n", result);
            break;
        case 'm':
            result = Average(operand1, operand2);
            printf("Result: %.2lf\n", result);
            break;
        case 'a':
            result = AbsoluteValue(operand1);
            printf("Result: %.2lf\n", result);
            break;
        case 'c':
            result = FahrenheitToCelsius(operand1);
            printf("Result: %.2lf\n", result);
            break;
        case 'f':
            result = CelsiusToFahrenheit(operand1);
            printf("Result: %.2lf\n", result);
            break;
        case 't':
            result = Tangent(operand1);
            printf("Result: %.2lf\n", result);
            break;
        case 'r':
            result = Round(operand1);
            printf("Result: %.2lf\n", result);
            break;
        default:
            printf("Invalid operation.\n");
        }
    }

    BOARD_End();
    while (1)
        ;
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
        return 0;
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
    return tan(degrees * M_PI / 180);
}
/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{
    return (operand > 0.0) ? floor(operand + 0.5) : ceil(operand - 0.5);
}
