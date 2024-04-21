/*******************************************************************************
* File Name: sensorClk.h  
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

#if !defined(CY_PINS_sensorClk_H) /* Pins sensorClk_H */
#define CY_PINS_sensorClk_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sensorClk_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sensorClk__PORT == 15 && ((sensorClk__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sensorClk_Write(uint8 value);
void    sensorClk_SetDriveMode(uint8 mode);
uint8   sensorClk_ReadDataReg(void);
uint8   sensorClk_Read(void);
void    sensorClk_SetInterruptMode(uint16 position, uint16 mode);
uint8   sensorClk_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sensorClk_SetDriveMode() function.
     *  @{
     */
        #define sensorClk_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sensorClk_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sensorClk_DM_RES_UP          PIN_DM_RES_UP
        #define sensorClk_DM_RES_DWN         PIN_DM_RES_DWN
        #define sensorClk_DM_OD_LO           PIN_DM_OD_LO
        #define sensorClk_DM_OD_HI           PIN_DM_OD_HI
        #define sensorClk_DM_STRONG          PIN_DM_STRONG
        #define sensorClk_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sensorClk_MASK               sensorClk__MASK
#define sensorClk_SHIFT              sensorClk__SHIFT
#define sensorClk_WIDTH              1u

/* Interrupt constants */
#if defined(sensorClk__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sensorClk_SetInterruptMode() function.
     *  @{
     */
        #define sensorClk_INTR_NONE      (uint16)(0x0000u)
        #define sensorClk_INTR_RISING    (uint16)(0x0001u)
        #define sensorClk_INTR_FALLING   (uint16)(0x0002u)
        #define sensorClk_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sensorClk_INTR_MASK      (0x01u) 
#endif /* (sensorClk__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sensorClk_PS                     (* (reg8 *) sensorClk__PS)
/* Data Register */
#define sensorClk_DR                     (* (reg8 *) sensorClk__DR)
/* Port Number */
#define sensorClk_PRT_NUM                (* (reg8 *) sensorClk__PRT) 
/* Connect to Analog Globals */                                                  
#define sensorClk_AG                     (* (reg8 *) sensorClk__AG)                       
/* Analog MUX bux enable */
#define sensorClk_AMUX                   (* (reg8 *) sensorClk__AMUX) 
/* Bidirectional Enable */                                                        
#define sensorClk_BIE                    (* (reg8 *) sensorClk__BIE)
/* Bit-mask for Aliased Register Access */
#define sensorClk_BIT_MASK               (* (reg8 *) sensorClk__BIT_MASK)
/* Bypass Enable */
#define sensorClk_BYP                    (* (reg8 *) sensorClk__BYP)
/* Port wide control signals */                                                   
#define sensorClk_CTL                    (* (reg8 *) sensorClk__CTL)
/* Drive Modes */
#define sensorClk_DM0                    (* (reg8 *) sensorClk__DM0) 
#define sensorClk_DM1                    (* (reg8 *) sensorClk__DM1)
#define sensorClk_DM2                    (* (reg8 *) sensorClk__DM2) 
/* Input Buffer Disable Override */
#define sensorClk_INP_DIS                (* (reg8 *) sensorClk__INP_DIS)
/* LCD Common or Segment Drive */
#define sensorClk_LCD_COM_SEG            (* (reg8 *) sensorClk__LCD_COM_SEG)
/* Enable Segment LCD */
#define sensorClk_LCD_EN                 (* (reg8 *) sensorClk__LCD_EN)
/* Slew Rate Control */
#define sensorClk_SLW                    (* (reg8 *) sensorClk__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sensorClk_PRTDSI__CAPS_SEL       (* (reg8 *) sensorClk__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sensorClk_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sensorClk__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sensorClk_PRTDSI__OE_SEL0        (* (reg8 *) sensorClk__PRTDSI__OE_SEL0) 
#define sensorClk_PRTDSI__OE_SEL1        (* (reg8 *) sensorClk__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sensorClk_PRTDSI__OUT_SEL0       (* (reg8 *) sensorClk__PRTDSI__OUT_SEL0) 
#define sensorClk_PRTDSI__OUT_SEL1       (* (reg8 *) sensorClk__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sensorClk_PRTDSI__SYNC_OUT       (* (reg8 *) sensorClk__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sensorClk__SIO_CFG)
    #define sensorClk_SIO_HYST_EN        (* (reg8 *) sensorClk__SIO_HYST_EN)
    #define sensorClk_SIO_REG_HIFREQ     (* (reg8 *) sensorClk__SIO_REG_HIFREQ)
    #define sensorClk_SIO_CFG            (* (reg8 *) sensorClk__SIO_CFG)
    #define sensorClk_SIO_DIFF           (* (reg8 *) sensorClk__SIO_DIFF)
#endif /* (sensorClk__SIO_CFG) */

/* Interrupt Registers */
#if defined(sensorClk__INTSTAT)
    #define sensorClk_INTSTAT            (* (reg8 *) sensorClk__INTSTAT)
    #define sensorClk_SNAP               (* (reg8 *) sensorClk__SNAP)
    
	#define sensorClk_0_INTTYPE_REG 		(* (reg8 *) sensorClk__0__INTTYPE)
#endif /* (sensorClk__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sensorClk_H */


/* [] END OF FILE */
