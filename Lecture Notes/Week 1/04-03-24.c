/*ayman is cool
Adherence to style:
-Vars use camelCase (like in APCS)
-Function names MEANINGFUL
--Functions names with UpperCase 
#define (literal constants) in UPPERCASE
-Vars & Func names descriptive
example:
backingUpState=True;

Dev tools data flow: examine diagram

Example program:
*/
#include <stdio.h>
#define PI 3.14159
int main(void)
{   float radius, area;

//calc area of circle
radius =12;
area = PI* radius * radius;

area = PI*radius*radius;
printF("Area = %f", area);
}
//do NOT run code here

/*
C runtime is the backend of C
Runtime env code is setup to auto-link to XC32
Stack/Heap:
stack grows from btm "up"

heap grows from top "down"

Version Control:
-keep track of doc changes
-keep ability to "roll back" code that works
-coordinate w/ mltpl programmers
-allow for branches to try smth that can be merged back into development

*/