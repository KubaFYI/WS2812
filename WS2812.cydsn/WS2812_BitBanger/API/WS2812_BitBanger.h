/* ========================================
 *
 * Copyright Kuba Sanak, 2019
 * 
 * Description:
 *  This file is a header for WS2812_Bitbanger component API to an UDB
 *  implementation of the WS2811/WS2812 RGB LED data protocol.
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
    
    #define STATUS_REG_MASK_FIFO_TURN 0x01
    #define STATUS_REG_MASK_RESETTING 0x02
    #define STATUS_REG_MASK_FIFO_EMPTY_0 0x04
    #define STATUS_REG_MASK_FIFO_EMPTY_1 0x08
    #define STATUS_REG_MASK_IDLE 0x10
    #define STATUS_REG_MASK_FIFO_EMPTY_CONCAT(idx) STATUS_REG_MASK_FIFO_EMPTY_ ## idx
//    #define STATUS_REG_MASK_FIFO_EMPTY_PRE STATUS_REG_MASK_FIFO_EMPTY_CONCAT(idx)
    #define STATUS_REG_MASK_FIFO_EMPTY(idx) STATUS_REG_MASK_FIFO_EMPTY_CONCAT(idx)

//    #define CTRL_REG_MASK_FIFO_TURN_NEW (uint8)0x01
    
    #define `$INSTANCE_NAME`_GetFifoTurn()          (`$INSTANCE_NAME`_StatusIntReg_Read() &   \
                                                     STATUS_REG_MASK_FIFO_TURN ? 1u : 0u)
    #define `$INSTANCE_NAME`_GetResettingStatus()   (`$INSTANCE_NAME`_StatusIntReg_Read() &   \
                                                     STATUS_REG_MASK_RESETTING ? 1u : 0u)
    #define `$INSTANCE_NAME`_FifoEmpty(idx)         (`$INSTANCE_NAME`_StatusIntReg_Read() &   \
                                                     STATUS_REG_MASK_FIFO_EMPTY(idx) ? 1u : 0u)
    #define `$INSTANCE_NAME`_Idle()                 (`$INSTANCE_NAME`_StatusIntReg_Read() &   \
                                                     STATUS_REG_MASK_IDLE ? 1u : 0u)
//    #define `$INSTANCE_NAME`_SetFifoTurn(x)         (`$INSTANCE_NAME`_CtrlReg_Write(x ?       \
//                                                    (`$INSTANCE_NAME`_CtrlReg_Read() |        \
//                                                        CTRL_REG_MASK_FIFO_TURN_NEW) :         \
//                                                    (`$INSTANCE_NAME`_CtrlReg_Read() &        \
//                                                        ~CTRL_REG_MASK_FIFO_TURN_NEW)))
    
    void `$INSTANCE_NAME`_Start(void);
    void `$INSTANCE_NAME`_PutPixel(uint32 color, uint32 fifoNum);
#endif
/* [] END OF FILE */
