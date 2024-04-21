/*******************************************************************************
* File Name: magnetControl.h  
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

#if !defined(CY_PINS_magnetControl_H) /* Pins magnetControl_H */
#define CY_PINS_magnetControl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "magnetControl_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 magnetControl__PORT == 15 && ((magnetControl__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    magnetControl_Write(uint8 value);
void    magnetControl_SetDriveMode(uint8 mode);
uint8   magnetControl_ReadDataReg(void);
uint8   magnetControl_Read(void);
void    magnetControl_SetInterruptMode(uint16 position, uint16 mode);
uint8   magnetControl_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the magnetControl_SetDriveMode() function.
     *  @{
     */
        #define magnetControl_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define magnetControl_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define magnetControl_DM_RES_UP          PIN_DM_RES_UP
        #define magnetControl_DM_RES_DWN         PIN_DM_RES_DWN
        #define magnetControl_DM_OD_LO           PIN_DM_OD_LO
        #define magnetControl_DM_OD_HI           PIN_DM_OD_HI
        #define magnetControl_DM_STRONG          PIN_DM_STRONG
        #define magnetControl_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define magnetControl_MASK               magnetControl__MASK
#define magnetControl_SHIFT              magnetControl__SHIFT
#define magnetControl_WIDTH              1u

/* Interrupt constants */
#if defined(magnetControl__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in magnetControl_SetInterruptMode() function.
     *  @{
     */
        #define magnetControl_INTR_NONE      (uint16)(0x0000u)
        #define magnetControl_INTR_RISING    (uint16)(0x0001u)
        #define magnetControl_INTR_FALLING   (uint16)(0x0002u)
        #define magnetControl_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define magnetControl_INTR_MASK      (0x01u) 
#endif /* (magnetControl__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define magnetControl_PS                     (* (reg8 *) magnetControl__PS)
/* Data Register */
#define magnetControl_DR                     (* (reg8 *) magnetControl__DR)
/* Port Number */
#define magnetControl_PRT_NUM                (* (reg8 *) magnetControl__PRT) 
/* Connect to Analog Globals */                                                  
#define magnetControl_AG                     (* (reg8 *) magnetControl__AG)                       
/* Analog MUX bux enable */
#define magnetControl_AMUX                   (* (reg8 *) magnetControl__AMUX) 
/* Bidirectional Enable */                                                        
#define magnetControl_BIE                    (* (reg8 *) magnetControl__BIE)
/* Bit-mask for Aliased Register Access */
#define magnetControl_BIT_MASK               (* (reg8 *) magnetControl__BIT_MASK)
/* Bypass Enable */
#define magnetControl_BYP                    (* (reg8 *) magnetControl__BYP)
/* Port wide control signals */                                                   
#define magnetControl_CTL                    (* (reg8 *) magnetControl__CTL)
/* Drive Modes */
#define magnetControl_DM0                    (* (reg8 *) magnetControl__DM0) 
#define magnetControl_DM1                    (* (reg8 *) magnetControl__DM1)
#define magnetControl_DM2                    (* (reg8 *) magnetControl__DM2) 
/* Input Buffer Disable Override */
#define magnetControl_INP_DIS                (* (reg8 *) magnetControl__INP_DIS)
/* LCD Common or Segment Drive */
#define magnetControl_LCD_COM_SEG            (* (reg8 *) magnetControl__LCD_COM_SEG)
/* Enable Segment LCD */
#define magnetControl_LCD_EN                 (* (reg8 *) magnetControl__LCD_EN)
/* Slew Rate Control */
#define magnetControl_SLW                    (* (reg8 *) magnetControl__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define magnetControl_PRTDSI__CAPS_SEL       (* (reg8 *) magnetControl__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define magnetControl_PRTDSI__DBL_SYNC_IN    (* (reg8 *) magnetControl__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define magnetControl_PRTDSI__OE_SEL0        (* (reg8 *) magnetControl__PRTDSI__OE_SEL0) 
#define magnetControl_PRTDSI__OE_SEL1        (* (reg8 *) magnetControl__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define magnetControl_PRTDSI__OUT_SEL0       (* (reg8 *) magnetControl__PRTDSI__OUT_SEL0) 
#define magnetControl_PRTDSI__OUT_SEL1       (* (reg8 *) magnetControl__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define magnetControl_PRTDSI__SYNC_OUT       (* (reg8 *) magnetControl__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(magnetControl__SIO_CFG)
    #define magnetControl_SIO_HYST_EN        (* (reg8 *) magnetControl__SIO_HYST_EN)
    #define magnetControl_SIO_REG_HIFREQ     (* (reg8 *) magnetControl__SIO_REG_HIFREQ)
    #define magnetControl_SIO_CFG            (* (reg8 *) magnetControl__SIO_CFG)
    #define magnetControl_SIO_DIFF           (* (reg8 *) magnetControl__SIO_DIFF)
#endif /* (magnetControl__SIO_CFG) */

/* Interrupt Registers */
#if defined(magnetControl__INTSTAT)
    #define magnetControl_INTSTAT            (* (reg8 *) magnetControl__INTSTAT)
    #define magnetControl_SNAP               (* (reg8 *) magnetControl__SNAP)
    
	#define magnetControl_0_INTTYPE_REG 		(* (reg8 *) magnetControl__0__INTTYPE)
#endif /* (magnetControl__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_magnetControl_H */


/* [] END OF FILE */
