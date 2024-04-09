/*
04/05/23:
-Gives symbolic names to vals
--dont need to know which register or mem location
-Provides abstraction of hardware tht underlays
--operations dont depend on instructions
ex: "a=b*c" even tho hardware may not have multply instruction

-Provide expressiveness
-meaningful symbols w/ meaning
-simple expressions for ctrl (if/then/else)
-safeguard against bugs
-Enhance code readability

*/
// hello world

#include <stdio.h> //standard io
int main(void)     // entry
{
    printf("SEX!\n"); // using io library for print

    return 0;
}

// prints hello worl. shift+alt+f auto formats

// embedded code for microcontroller
#include <stdio.h>
int main(void)
{
        printf("Hello, world!\n");
        // loops forever, never return
        while (1);
}

//simple program for circle
#include <stdio.h>
#define PI 3.14159
int main(void)
{
    float radius, area;

    //area of circle

}

//notation for good comment practices
/**
 * @file
 * @author example
 * @sec desc
 * This code does blah
*/

// vars + datatypes

int myVariable;
myVariable =5;

