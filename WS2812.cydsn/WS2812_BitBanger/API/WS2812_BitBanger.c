/* ========================================
 *
 * Copyright Kuba Sanak, 2019
 * 
 * Description:
 *  This file is the source code for WS2812_Bitbanger component API to an UDB
 *  implementation of the WS2811/WS2812 RGB LED data protocol.
 *
********************************************************************************
* Copyright 2019, Kuba Sanak.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_WS2812_BitBanger.h"
#include "`$INSTANCE_NAME`_defs.h"


/******************************************************************************
 *
 *  Initialises and enables the component.
 *
 *  Has to be called before the component is used.
 *
 *****************************************************************************/
void `$INSTANCE_NAME`_Start()
{
    // Enter Critical Section
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    
    // Setup the FIFOs
    `$INSTANCE_NAME`_Datapath_F0_CLEAR;
    `$INSTANCE_NAME`_Datapath_F1_CLEAR;
    `$INSTANCE_NAME`_Datapath_F0_SET_LEVEL_NORMAL;
    `$INSTANCE_NAME`_Datapath_F1_SET_LEVEL_NORMAL;
    `$INSTANCE_NAME`_Datapath_F0_SINGLE_BUFFER_UNSET;
    `$INSTANCE_NAME`_Datapath_F1_SINGLE_BUFFER_UNSET;
    
    //Exit Critical Section
    CyExitCriticalSection(interruptState);
    
    `$INSTANCE_NAME`_Reset_Timer_Start();
    
    // Enable relevant interrupts
    `$INSTANCE_NAME`_StatusIntReg_InterruptEnable();
}

/******************************************************************************
 *
 *  Instructs the first connected pixel to assume a given color
 *
 *****************************************************************************/
void `$INSTANCE_NAME`_PutPixel(uint32 color, uint32 fifoNum)
{
    reg8* datapath_ptr;
    if (fifoNum) {
        datapath_ptr = `$INSTANCE_NAME`_Datapath_F1_PTR;
    } else {
        datapath_ptr = `$INSTANCE_NAME`_Datapath_F0_PTR;
    }
    
    CY_SET_REG8(datapath_ptr, (uint8)(color & 0xff));
    color >>= 8;
    CY_SET_REG8(datapath_ptr, (uint8)(color & 0xff));
    color >>= 8;
    CY_SET_REG8(datapath_ptr, (uint8)(color & 0xff));
}

/* [] END OF FILE */
