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


#include "`$INSTANCE_NAME`_WS2812_Controller.h"
#include "project.h"


/******************************************************************************
 *
 *  Initialises and enables the component.
 *
 *  Has to be called before the component is used.
 *
 *****************************************************************************/
void `$INSTANCE_NAME`_Start(){
    `$INSTANCE_NAME`_WS2812_BitBanger_Start();
    }

/******************************************************************************
 *
 *  Sets the very first pixel to a given color.
 *
 *****************************************************************************/
void `$INSTANCE_NAME`_InsertPixel(uint32 color){
    `$INSTANCE_NAME`_WS2812_BitBanger_InsertPixel(color);
    }
/* [] END OF FILE */
