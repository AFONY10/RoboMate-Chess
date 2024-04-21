/*******************************************************************************
* File Name: sensorSignal.h  
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

#if !defined(CY_PINS_sensorSignal_H) /* Pins sensorSignal_H */
#define CY_PINS_sensorSignal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sensorSignal_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sensorSignal__PORT == 15 && ((sensorSignal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sensorSignal_Write(uint8 value);
void    sensorSignal_SetDriveMode(uint8 mode);
uint8   sensorSignal_ReadDataReg(void);
uint8   sensorSignal_Read(void);
void    sensorSignal_SetInterruptMode(uint16 position, uint16 mode);
uint8   sensorSignal_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sensorSignal_SetDriveMode() function.
     *  @{
     */
        #define sensorSignal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sensorSignal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sensorSignal_DM_RES_UP          PIN_DM_RES_UP
        #define sensorSignal_DM_RES_DWN         PIN_DM_RES_DWN
        #define sensorSignal_DM_OD_LO           PIN_DM_OD_LO
        #define sensorSignal_DM_OD_HI           PIN_DM_OD_HI
        #define sensorSignal_DM_STRONG          PIN_DM_STRONG
        #define sensorSignal_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sensorSignal_MASK               sensorSignal__MASK
#define sensorSignal_SHIFT              sensorSignal__SHIFT
#define sensorSignal_WIDTH              1u

/* Interrupt constants */
#if defined(sensorSignal__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sensorSignal_SetInterruptMode() function.
     *  @{
     */
        #define sensorSignal_INTR_NONE      (uint16)(0x0000u)
        #define sensorSignal_INTR_RISING    (uint16)(0x0001u)
        #define sensorSignal_INTR_FALLING   (uint16)(0x0002u)
        #define sensorSignal_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sensorSignal_INTR_MASK      (0x01u) 
#endif /* (sensorSignal__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sensorSignal_PS                     (* (reg8 *) sensorSignal__PS)
/* Data Register */
#define sensorSignal_DR                     (* (reg8 *) sensorSignal__DR)
/* Port Number */
#define sensorSignal_PRT_NUM                (* (reg8 *) sensorSignal__PRT) 
/* Connect to Analog Globals */                                                  
#define sensorSignal_AG                     (* (reg8 *) sensorSignal__AG)                       
/* Analog MUX bux enable */
#define sensorSignal_AMUX                   (* (reg8 *) sensorSignal__AMUX) 
/* Bidirectional Enable */                                                        
#define sensorSignal_BIE                    (* (reg8 *) sensorSignal__BIE)
/* Bit-mask for Aliased Register Access */
#define sensorSignal_BIT_MASK               (* (reg8 *) sensorSignal__BIT_MASK)
/* Bypass Enable */
#define sensorSignal_BYP                    (* (reg8 *) sensorSignal__BYP)
/* Port wide control signals */                                                   
#define sensorSignal_CTL                    (* (reg8 *) sensorSignal__CTL)
/* Drive Modes */
#define sensorSignal_DM0                    (* (reg8 *) sensorSignal__DM0) 
#define sensorSignal_DM1                    (* (reg8 *) sensorSignal__DM1)
#define sensorSignal_DM2                    (* (reg8 *) sensorSignal__DM2) 
/* Input Buffer Disable Override */
#define sensorSignal_INP_DIS                (* (reg8 *) sensorSignal__INP_DIS)
/* LCD Common or Segment Drive */
#define sensorSignal_LCD_COM_SEG            (* (reg8 *) sensorSignal__LCD_COM_SEG)
/* Enable Segment LCD */
#define sensorSignal_LCD_EN                 (* (reg8 *) sensorSignal__LCD_EN)
/* Slew Rate Control */
#define sensorSignal_SLW                    (* (reg8 *) sensorSignal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sensorSignal_PRTDSI__CAPS_SEL       (* (reg8 *) sensorSignal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sensorSignal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sensorSignal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sensorSignal_PRTDSI__OE_SEL0        (* (reg8 *) sensorSignal__PRTDSI__OE_SEL0) 
#define sensorSignal_PRTDSI__OE_SEL1        (* (reg8 *) sensorSignal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sensorSignal_PRTDSI__OUT_SEL0       (* (reg8 *) sensorSignal__PRTDSI__OUT_SEL0) 
#define sensorSignal_PRTDSI__OUT_SEL1       (* (reg8 *) sensorSignal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sensorSignal_PRTDSI__SYNC_OUT       (* (reg8 *) sensorSignal__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sensorSignal__SIO_CFG)
    #define sensorSignal_SIO_HYST_EN        (* (reg8 *) sensorSignal__SIO_HYST_EN)
    #define sensorSignal_SIO_REG_HIFREQ     (* (reg8 *) sensorSignal__SIO_REG_HIFREQ)
    #define sensorSignal_SIO_CFG            (* (reg8 *) sensorSignal__SIO_CFG)
    #define sensorSignal_SIO_DIFF           (* (reg8 *) sensorSignal__SIO_DIFF)
#endif /* (sensorSignal__SIO_CFG) */

/* Interrupt Registers */
#if defined(sensorSignal__INTSTAT)
    #define sensorSignal_INTSTAT            (* (reg8 *) sensorSignal__INTSTAT)
    #define sensorSignal_SNAP               (* (reg8 *) sensorSignal__SNAP)
    
	#define sensorSignal_0_INTTYPE_REG 		(* (reg8 *) sensorSignal__0__INTTYPE)
#endif /* (sensorSignal__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sensorSignal_H */


/* [] END OF FILE */
