/* ========================================
 *
 * Copyright Kuba Sanak, 2019
 * 
 * Description:
 *  This file is a header for WS2812_Controller component API serving
 *  as a driver and control function library for WS2811/WS2812 RGB LED strips.
 *
********************************************************************************
* Copyright 2019, Kuba Sanak.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined (`$INSTANCE_NAME`_H)
    #define `$INSTANCE_NAME`_H
    
    #include "cytypes.h"
    #include "cyfitter.h"
    
    void `$INSTANCE_NAME`_Start(void);
    void `$INSTANCE_NAME`_PutFirstPixel(uint32 color);
    void `$INSTANCE_NAME`_PutPixelArray(uint32* colors, uint32 num);
    uint32 `$INSTANCE_NAME`_Idle();
#endif
/* [] END OF FILE */
