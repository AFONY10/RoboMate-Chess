/*******************************************************************************
* File Name: Servo.h  
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

#if !defined(CY_PINS_Servo_H) /* Pins Servo_H */
#define CY_PINS_Servo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Servo_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Servo__PORT == 15 && ((Servo__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Servo_Write(uint8 value);
void    Servo_SetDriveMode(uint8 mode);
uint8   Servo_ReadDataReg(void);
uint8   Servo_Read(void);
void    Servo_SetInterruptMode(uint16 position, uint16 mode);
uint8   Servo_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Servo_SetDriveMode() function.
     *  @{
     */
        #define Servo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Servo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Servo_DM_RES_UP          PIN_DM_RES_UP
        #define Servo_DM_RES_DWN         PIN_DM_RES_DWN
        #define Servo_DM_OD_LO           PIN_DM_OD_LO
        #define Servo_DM_OD_HI           PIN_DM_OD_HI
        #define Servo_DM_STRONG          PIN_DM_STRONG
        #define Servo_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Servo_MASK               Servo__MASK
#define Servo_SHIFT              Servo__SHIFT
#define Servo_WIDTH              1u

/* Interrupt constants */
#if defined(Servo__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Servo_SetInterruptMode() function.
     *  @{
     */
        #define Servo_INTR_NONE      (uint16)(0x0000u)
        #define Servo_INTR_RISING    (uint16)(0x0001u)
        #define Servo_INTR_FALLING   (uint16)(0x0002u)
        #define Servo_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Servo_INTR_MASK      (0x01u) 
#endif /* (Servo__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Servo_PS                     (* (reg8 *) Servo__PS)
/* Data Register */
#define Servo_DR                     (* (reg8 *) Servo__DR)
/* Port Number */
#define Servo_PRT_NUM                (* (reg8 *) Servo__PRT) 
/* Connect to Analog Globals */                                                  
#define Servo_AG                     (* (reg8 *) Servo__AG)                       
/* Analog MUX bux enable */
#define Servo_AMUX                   (* (reg8 *) Servo__AMUX) 
/* Bidirectional Enable */                                                        
#define Servo_BIE                    (* (reg8 *) Servo__BIE)
/* Bit-mask for Aliased Register Access */
#define Servo_BIT_MASK               (* (reg8 *) Servo__BIT_MASK)
/* Bypass Enable */
#define Servo_BYP                    (* (reg8 *) Servo__BYP)
/* Port wide control signals */                                                   
#define Servo_CTL                    (* (reg8 *) Servo__CTL)
/* Drive Modes */
#define Servo_DM0                    (* (reg8 *) Servo__DM0) 
#define Servo_DM1                    (* (reg8 *) Servo__DM1)
#define Servo_DM2                    (* (reg8 *) Servo__DM2) 
/* Input Buffer Disable Override */
#define Servo_INP_DIS                (* (reg8 *) Servo__INP_DIS)
/* LCD Common or Segment Drive */
#define Servo_LCD_COM_SEG            (* (reg8 *) Servo__LCD_COM_SEG)
/* Enable Segment LCD */
#define Servo_LCD_EN                 (* (reg8 *) Servo__LCD_EN)
/* Slew Rate Control */
#define Servo_SLW                    (* (reg8 *) Servo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Servo_PRTDSI__CAPS_SEL       (* (reg8 *) Servo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Servo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Servo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Servo_PRTDSI__OE_SEL0        (* (reg8 *) Servo__PRTDSI__OE_SEL0) 
#define Servo_PRTDSI__OE_SEL1        (* (reg8 *) Servo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Servo_PRTDSI__OUT_SEL0       (* (reg8 *) Servo__PRTDSI__OUT_SEL0) 
#define Servo_PRTDSI__OUT_SEL1       (* (reg8 *) Servo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Servo_PRTDSI__SYNC_OUT       (* (reg8 *) Servo__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Servo__SIO_CFG)
    #define Servo_SIO_HYST_EN        (* (reg8 *) Servo__SIO_HYST_EN)
    #define Servo_SIO_REG_HIFREQ     (* (reg8 *) Servo__SIO_REG_HIFREQ)
    #define Servo_SIO_CFG            (* (reg8 *) Servo__SIO_CFG)
    #define Servo_SIO_DIFF           (* (reg8 *) Servo__SIO_DIFF)
#endif /* (Servo__SIO_CFG) */

/* Interrupt Registers */
#if defined(Servo__INTSTAT)
    #define Servo_INTSTAT            (* (reg8 *) Servo__INTSTAT)
    #define Servo_SNAP               (* (reg8 *) Servo__SNAP)
    
	#define Servo_0_INTTYPE_REG 		(* (reg8 *) Servo__0__INTTYPE)
#endif /* (Servo__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Servo_H */


/* [] END OF FILE */
