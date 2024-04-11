/* 
 * File:   part0.c
 * Author: finn seidel
 *
 * Created on April 8, 2024, 11:38 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"

/*
 * 
 */
int main(void)
{
    BOARD_Init();
    printf("Hello World\n");
    
    
    
    BOARD_End(); 
    while(1);
}

