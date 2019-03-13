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
}

void `$INSTANCE_NAME`_InsertPixel(uint32 color)
{
    CY_SET_REG8(`$INSTANCE_NAME`_Datapath_F0_PTR, (uint8)(color & 0xff));
    color >>= 8;
    CY_SET_REG8(`$INSTANCE_NAME`_Datapath_F0_PTR, (uint8)(color & 0xff));
    color >>= 8;
    CY_SET_REG8(`$INSTANCE_NAME`_Datapath_F0_PTR, (uint8)(color & 0xff));
}
/* [] END OF FILE */
