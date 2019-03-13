/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <stdlib.h>
#include <stdio.h>
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CyDelay(1000);
    WS2812_Controller_1_Start();
    uint32 color = 0x123456;
    WS2812_Controller_1_InsertPixel(color);
    CyDelay(1000);
    UART_Start();
    char strEx[7] = "Hello!";
    char msgStr[20];
    UART_UartPutString(strEx);
    UART_UartPutCRLF(' ');
    for(int i=0;;)
    {
        char c;
        if((c = UART_UartGetChar()))
        {
            strEx[i] = c;
            UART_UartPutChar(c);
            if(i++==6)
            {
                strEx[6] = '\0';
                uint32 number = strtol(strEx, NULL, 16);
                WS2812_Controller_1_InsertPixel(number );
                CyDelay(500);
                sprintf(msgStr, "%d", number);
                UART_UartPutCRLF('!');
                UART_UartPutString(msgStr);
                UART_UartPutCRLF('#');
                i=0;
            }
        }
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
