/*******************************************************************************
* File Name: servoControl.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_servoControl_H) /* Pins servoControl_H */
#define CY_PINS_servoControl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "servoControl_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 servoControl__PORT == 15 && ((servoControl__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    servoControl_Write(uint8 value);
void    servoControl_SetDriveMode(uint8 mode);
uint8   servoControl_ReadDataReg(void);
uint8   servoControl_Read(void);
void    servoControl_SetInterruptMode(uint16 position, uint16 mode);
uint8   servoControl_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the servoControl_SetDriveMode() function.
     *  @{
     */
        #define servoControl_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define servoControl_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define servoControl_DM_RES_UP          PIN_DM_RES_UP
        #define servoControl_DM_RES_DWN         PIN_DM_RES_DWN
        #define servoControl_DM_OD_LO           PIN_DM_OD_LO
        #define servoControl_DM_OD_HI           PIN_DM_OD_HI
        #define servoControl_DM_STRONG          PIN_DM_STRONG
        #define servoControl_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define servoControl_MASK               servoControl__MASK
#define servoControl_SHIFT              servoControl__SHIFT
#define servoControl_WIDTH              1u

/* Interrupt constants */
#if defined(servoControl__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in servoControl_SetInterruptMode() function.
     *  @{
     */
        #define servoControl_INTR_NONE      (uint16)(0x0000u)
        #define servoControl_INTR_RISING    (uint16)(0x0001u)
        #define servoControl_INTR_FALLING   (uint16)(0x0002u)
        #define servoControl_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define servoControl_INTR_MASK      (0x01u) 
#endif /* (servoControl__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define servoControl_PS                     (* (reg8 *) servoControl__PS)
/* Data Register */
#define servoControl_DR                     (* (reg8 *) servoControl__DR)
/* Port Number */
#define servoControl_PRT_NUM                (* (reg8 *) servoControl__PRT) 
/* Connect to Analog Globals */                                                  
#define servoControl_AG                     (* (reg8 *) servoControl__AG)                       
/* Analog MUX bux enable */
#define servoControl_AMUX                   (* (reg8 *) servoControl__AMUX) 
/* Bidirectional Enable */                                                        
#define servoControl_BIE                    (* (reg8 *) servoControl__BIE)
/* Bit-mask for Aliased Register Access */
#define servoControl_BIT_MASK               (* (reg8 *) servoControl__BIT_MASK)
/* Bypass Enable */
#define servoControl_BYP                    (* (reg8 *) servoControl__BYP)
/* Port wide control signals */                                                   
#define servoControl_CTL                    (* (reg8 *) servoControl__CTL)
/* Drive Modes */
#define servoControl_DM0                    (* (reg8 *) servoControl__DM0) 
#define servoControl_DM1                    (* (reg8 *) servoControl__DM1)
#define servoControl_DM2                    (* (reg8 *) servoControl__DM2) 
/* Input Buffer Disable Override */
#define servoControl_INP_DIS                (* (reg8 *) servoControl__INP_DIS)
/* LCD Common or Segment Drive */
#define servoControl_LCD_COM_SEG            (* (reg8 *) servoControl__LCD_COM_SEG)
/* Enable Segment LCD */
#define servoControl_LCD_EN                 (* (reg8 *) servoControl__LCD_EN)
/* Slew Rate Control */
#define servoControl_SLW                    (* (reg8 *) servoControl__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define servoControl_PRTDSI__CAPS_SEL       (* (reg8 *) servoControl__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define servoControl_PRTDSI__DBL_SYNC_IN    (* (reg8 *) servoControl__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define servoControl_PRTDSI__OE_SEL0        (* (reg8 *) servoControl__PRTDSI__OE_SEL0) 
#define servoControl_PRTDSI__OE_SEL1        (* (reg8 *) servoControl__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define servoControl_PRTDSI__OUT_SEL0       (* (reg8 *) servoControl__PRTDSI__OUT_SEL0) 
#define servoControl_PRTDSI__OUT_SEL1       (* (reg8 *) servoControl__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define servoControl_PRTDSI__SYNC_OUT       (* (reg8 *) servoControl__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(servoControl__SIO_CFG)
    #define servoControl_SIO_HYST_EN        (* (reg8 *) servoControl__SIO_HYST_EN)
    #define servoControl_SIO_REG_HIFREQ     (* (reg8 *) servoControl__SIO_REG_HIFREQ)
    #define servoControl_SIO_CFG            (* (reg8 *) servoControl__SIO_CFG)
    #define servoControl_SIO_DIFF           (* (reg8 *) servoControl__SIO_DIFF)
#endif /* (servoControl__SIO_CFG) */

/* Interrupt Registers */
#if defined(servoControl__INTSTAT)
    #define servoControl_INTSTAT            (* (reg8 *) servoControl__INTSTAT)
    #define servoControl_SNAP               (* (reg8 *) servoControl__SNAP)
    
	#define servoControl_0_INTTYPE_REG 		(* (reg8 *) servoControl__0__INTTYPE)
#endif /* (servoControl__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_servoControl_H */


/* [] END OF FILE */
