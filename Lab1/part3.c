/*
 * File: part3.c
 * Author: Rahil Prakash (rprakas2@ucsc.edu)
 * Created on April 08, 2023, 9:02 PM
 */
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <math.h>

// CMPE13 Support Library
#include "BOARD.h"

// User libraries

// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

int main()
{
    BOARD_Init();
    {
        // Add code here to print to OLED
        OledInit();

        OledDrawString("Hello, World!\n");

        OledUpdate();
        // You can never return from main() in an embedded system (one that lacks an operating system).
        // This will result in the processor restarting, which is almost certainly not what you want!
        while (1)
            ;
    }
}
