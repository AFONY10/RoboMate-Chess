/*******************************************************************************
* File Name: ServoClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_ServoClk_H)
#define CY_CLOCK_ServoClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void ServoClk_Start(void) ;
void ServoClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void ServoClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void ServoClk_StandbyPower(uint8 state) ;
void ServoClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 ServoClk_GetDividerRegister(void) ;
void ServoClk_SetModeRegister(uint8 modeBitMask) ;
void ServoClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 ServoClk_GetModeRegister(void) ;
void ServoClk_SetSourceRegister(uint8 clkSource) ;
uint8 ServoClk_GetSourceRegister(void) ;
#if defined(ServoClk__CFG3)
void ServoClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 ServoClk_GetPhaseRegister(void) ;
#endif /* defined(ServoClk__CFG3) */

#define ServoClk_Enable()                       ServoClk_Start()
#define ServoClk_Disable()                      ServoClk_Stop()
#define ServoClk_SetDivider(clkDivider)         ServoClk_SetDividerRegister(clkDivider, 1u)
#define ServoClk_SetDividerValue(clkDivider)    ServoClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define ServoClk_SetMode(clkMode)               ServoClk_SetModeRegister(clkMode)
#define ServoClk_SetSource(clkSource)           ServoClk_SetSourceRegister(clkSource)
#if defined(ServoClk__CFG3)
#define ServoClk_SetPhase(clkPhase)             ServoClk_SetPhaseRegister(clkPhase)
#define ServoClk_SetPhaseValue(clkPhase)        ServoClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(ServoClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ServoClk_CLKEN              (* (reg8 *) ServoClk__PM_ACT_CFG)
#define ServoClk_CLKEN_PTR          ((reg8 *) ServoClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ServoClk_CLKSTBY            (* (reg8 *) ServoClk__PM_STBY_CFG)
#define ServoClk_CLKSTBY_PTR        ((reg8 *) ServoClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ServoClk_DIV_LSB            (* (reg8 *) ServoClk__CFG0)
#define ServoClk_DIV_LSB_PTR        ((reg8 *) ServoClk__CFG0)
#define ServoClk_DIV_PTR            ((reg16 *) ServoClk__CFG0)

/* Clock MSB divider configuration register. */
#define ServoClk_DIV_MSB            (* (reg8 *) ServoClk__CFG1)
#define ServoClk_DIV_MSB_PTR        ((reg8 *) ServoClk__CFG1)

/* Mode and source configuration register */
#define ServoClk_MOD_SRC            (* (reg8 *) ServoClk__CFG2)
#define ServoClk_MOD_SRC_PTR        ((reg8 *) ServoClk__CFG2)

#if defined(ServoClk__CFG3)
/* Analog clock phase configuration register */
#define ServoClk_PHASE              (* (reg8 *) ServoClk__CFG3)
#define ServoClk_PHASE_PTR          ((reg8 *) ServoClk__CFG3)
#endif /* defined(ServoClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ServoClk_CLKEN_MASK         ServoClk__PM_ACT_MSK
#define ServoClk_CLKSTBY_MASK       ServoClk__PM_STBY_MSK

/* CFG2 field masks */
#define ServoClk_SRC_SEL_MSK        ServoClk__CFG2_SRC_SEL_MASK
#define ServoClk_MODE_MASK          (~(ServoClk_SRC_SEL_MSK))

#if defined(ServoClk__CFG3)
/* CFG3 phase mask */
#define ServoClk_PHASE_MASK         ServoClk__CFG3_PHASE_DLY_MASK
#endif /* defined(ServoClk__CFG3) */

#endif /* CY_CLOCK_ServoClk_H */


/* [] END OF FILE */
