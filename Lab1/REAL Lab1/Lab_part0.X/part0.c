/* 
 * File:   part0.c
 * Author: Celest Romero
 *
 * Created on April 9, 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"


int main(void)
{
    BOARD_Init();
    
    printf("Hello World\n");
    
    BOARD_End();
    while(1);
}