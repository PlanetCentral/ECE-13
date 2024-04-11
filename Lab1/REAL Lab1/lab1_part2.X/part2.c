/*
 * File: part2.c
 * Author: Rahil Prakash (rprakas2@ucsc.edu)
 * Created on April 08, 2023, 9:02 PM
 */
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

// Class specific libraries
#include "BOARD.h"

// User libraries
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    BOARD_Init();
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    // Declare variables
    float fahr, celsius;
    int lower, upper, step;

    // Initialize Variables
    lower = 0;   // lower limit of temperature
    upper = 300; // upper limit
    step = 20;   // step size
    fahr = lower;

    // Print column headers for F to C
    printf("%7s %4s\n", "F", "C");

    // Print the table
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%7.1f %04.0f\n", fahr, celsius);
        fahr = fahr + step;
    }

    puts(""); 
    printf("%-3s %-7s\n", "K", "F"); 

    // Print K to F table
    for (float kelvin = lower + 273.15; kelvin <= upper + 273.15; kelvin += step)
    {
        fahr = (kelvin - 273.15) * 9 / 5 + 32;
        printf("%03.0f %7.1f\n", kelvin, fahr);
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1)
        ;
}
