/* ========================================
 *
 * Copyright Kuba Sanak, 2019
 * 
 * Description:
 *  This file provides source code for the WS2812_Controller component serving
 *  as a driver and control function library for WS2811/WS2812 RGB LED strips.
 *
********************************************************************************
* Copyright 2019, Kuba Sanak.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


/******************************************************************************
 *
 *  Includes, defines and Cypress-specific prototypes.
 *
 *****************************************************************************/
#include "`$INSTANCE_NAME`_WS2812_Controller.h"
#include "project.h"

#define PIXEL_BUFFER_SIZE 100

CY_ISR_PROTO(`$INSTANCE_NAME`_PixelLoaderIsr);

/******************************************************************************
 *
 *  Global variables
 *
 *****************************************************************************/
uint32 pxl_buff[PIXEL_BUFFER_SIZE];
uint32 pxl_buff_ptr = 0;
uint32 buffer_end = 0;
uint32 fifo_turn = 0;

/******************************************************************************
 *
 *  Initialises and enables the component.
 *
 *  Has to be called before the component is used.
 *
 *****************************************************************************/
void `$INSTANCE_NAME`_Start(){
    `$INSTANCE_NAME`_WS2812_BitBanger_Start();
    `$INSTANCE_NAME`_Stat_Reg_Isr_StartEx(`$INSTANCE_NAME`_PixelLoaderIsr);
}

/******************************************************************************
 *
 *  Sets the very first pixel to a given color.
 *
 *****************************************************************************/
void `$INSTANCE_NAME`_PutFirstPixel(uint32 color){
    
    `$INSTANCE_NAME`_WS2812_BitBanger_PutPixel(color, 0);
}

/******************************************************************************
 *
 *  Instructs the first `num` pixels to assume colors in the provided array.
 *
 *****************************************************************************/
void `$INSTANCE_NAME`_PutPixelArray(uint32* colors, uint32 num)
{
    // Wait until the resource is available
    while (!`$INSTANCE_NAME`_WS2812_BitBanger_Idle()) ;
    
    memcpy(pxl_buff, colors, num * sizeof(uint32));
    buffer_end = num;
    pxl_buff_ptr = 1;

    // Initialise the process (only the first (or first two) pixels -> the
    // remainder will be loaded by with interrupts until pxl_buff_ptr matches
    // buffer_end.
    `$INSTANCE_NAME`_WS2812_BitBanger_PutPixel(pxl_buff[0], 0);
    if (num > 1) {
        `$INSTANCE_NAME`_WS2812_BitBanger_PutPixel(pxl_buff[1], 1);
        pxl_buff_ptr++;
    }
}

/******************************************************************************
 *
 *  Run by the ISR triggered whenever a FIFO gets empty.
 *
 *  Checks whether there is more pixels to load and puts them in an
 *  appropriate FIFO.
 *
 *****************************************************************************/
CY_ISR(`$INSTANCE_NAME`_PixelLoaderIsr){
    if (buffer_end < pxl_buff_ptr) {
        uint32 fifoTurn = !`$INSTANCE_NAME`_WS2812_BitBanger_GetFifoTurn();
        if (fifoTurn && `$INSTANCE_NAME`_WS2812_BitBanger_FifoEmpty(fifoTurn)) {
            `$INSTANCE_NAME`_WS2812_BitBanger_PutPixel(pxl_buff[pxl_buff_ptr++], fifoTurn);
        } else {
            // TODO timeout handling
        }
    }
}

/******************************************************************************
 *
 *  Returns True when the UDB Bitbanger is Idle and False otherwise.
 *
 *****************************************************************************/
uint32 `$INSTANCE_NAME`_Idle(){
    return `$INSTANCE_NAME`_WS2812_BitBanger_Idle();
}

/* [] END OF FILE */
