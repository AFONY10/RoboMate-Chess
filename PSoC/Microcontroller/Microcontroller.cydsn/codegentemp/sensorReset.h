/*******************************************************************************
* File Name: sensorReset.h  
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

#if !defined(CY_PINS_sensorReset_H) /* Pins sensorReset_H */
#define CY_PINS_sensorReset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sensorReset_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sensorReset__PORT == 15 && ((sensorReset__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sensorReset_Write(uint8 value);
void    sensorReset_SetDriveMode(uint8 mode);
uint8   sensorReset_ReadDataReg(void);
uint8   sensorReset_Read(void);
void    sensorReset_SetInterruptMode(uint16 position, uint16 mode);
uint8   sensorReset_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sensorReset_SetDriveMode() function.
     *  @{
     */
        #define sensorReset_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sensorReset_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sensorReset_DM_RES_UP          PIN_DM_RES_UP
        #define sensorReset_DM_RES_DWN         PIN_DM_RES_DWN
        #define sensorReset_DM_OD_LO           PIN_DM_OD_LO
        #define sensorReset_DM_OD_HI           PIN_DM_OD_HI
        #define sensorReset_DM_STRONG          PIN_DM_STRONG
        #define sensorReset_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sensorReset_MASK               sensorReset__MASK
#define sensorReset_SHIFT              sensorReset__SHIFT
#define sensorReset_WIDTH              1u

/* Interrupt constants */
#if defined(sensorReset__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sensorReset_SetInterruptMode() function.
     *  @{
     */
        #define sensorReset_INTR_NONE      (uint16)(0x0000u)
        #define sensorReset_INTR_RISING    (uint16)(0x0001u)
        #define sensorReset_INTR_FALLING   (uint16)(0x0002u)
        #define sensorReset_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sensorReset_INTR_MASK      (0x01u) 
#endif /* (sensorReset__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sensorReset_PS                     (* (reg8 *) sensorReset__PS)
/* Data Register */
#define sensorReset_DR                     (* (reg8 *) sensorReset__DR)
/* Port Number */
#define sensorReset_PRT_NUM                (* (reg8 *) sensorReset__PRT) 
/* Connect to Analog Globals */                                                  
#define sensorReset_AG                     (* (reg8 *) sensorReset__AG)                       
/* Analog MUX bux enable */
#define sensorReset_AMUX                   (* (reg8 *) sensorReset__AMUX) 
/* Bidirectional Enable */                                                        
#define sensorReset_BIE                    (* (reg8 *) sensorReset__BIE)
/* Bit-mask for Aliased Register Access */
#define sensorReset_BIT_MASK               (* (reg8 *) sensorReset__BIT_MASK)
/* Bypass Enable */
#define sensorReset_BYP                    (* (reg8 *) sensorReset__BYP)
/* Port wide control signals */                                                   
#define sensorReset_CTL                    (* (reg8 *) sensorReset__CTL)
/* Drive Modes */
#define sensorReset_DM0                    (* (reg8 *) sensorReset__DM0) 
#define sensorReset_DM1                    (* (reg8 *) sensorReset__DM1)
#define sensorReset_DM2                    (* (reg8 *) sensorReset__DM2) 
/* Input Buffer Disable Override */
#define sensorReset_INP_DIS                (* (reg8 *) sensorReset__INP_DIS)
/* LCD Common or Segment Drive */
#define sensorReset_LCD_COM_SEG            (* (reg8 *) sensorReset__LCD_COM_SEG)
/* Enable Segment LCD */
#define sensorReset_LCD_EN                 (* (reg8 *) sensorReset__LCD_EN)
/* Slew Rate Control */
#define sensorReset_SLW                    (* (reg8 *) sensorReset__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sensorReset_PRTDSI__CAPS_SEL       (* (reg8 *) sensorReset__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sensorReset_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sensorReset__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sensorReset_PRTDSI__OE_SEL0        (* (reg8 *) sensorReset__PRTDSI__OE_SEL0) 
#define sensorReset_PRTDSI__OE_SEL1        (* (reg8 *) sensorReset__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sensorReset_PRTDSI__OUT_SEL0       (* (reg8 *) sensorReset__PRTDSI__OUT_SEL0) 
#define sensorReset_PRTDSI__OUT_SEL1       (* (reg8 *) sensorReset__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sensorReset_PRTDSI__SYNC_OUT       (* (reg8 *) sensorReset__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sensorReset__SIO_CFG)
    #define sensorReset_SIO_HYST_EN        (* (reg8 *) sensorReset__SIO_HYST_EN)
    #define sensorReset_SIO_REG_HIFREQ     (* (reg8 *) sensorReset__SIO_REG_HIFREQ)
    #define sensorReset_SIO_CFG            (* (reg8 *) sensorReset__SIO_CFG)
    #define sensorReset_SIO_DIFF           (* (reg8 *) sensorReset__SIO_DIFF)
#endif /* (sensorReset__SIO_CFG) */

/* Interrupt Registers */
#if defined(sensorReset__INTSTAT)
    #define sensorReset_INTSTAT            (* (reg8 *) sensorReset__INTSTAT)
    #define sensorReset_SNAP               (* (reg8 *) sensorReset__SNAP)
    
	#define sensorReset_0_INTTYPE_REG 		(* (reg8 *) sensorReset__0__INTTYPE)
#endif /* (sensorReset__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sensorReset_H */


/* [] END OF FILE */
