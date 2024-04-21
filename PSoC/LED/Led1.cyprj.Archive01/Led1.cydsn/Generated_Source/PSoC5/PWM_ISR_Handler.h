/*******************************************************************************
* File Name: PWM_ISR_Handler.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_PWM_ISR_Handler_H)
#define CY_ISR_PWM_ISR_Handler_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PWM_ISR_Handler_Start(void);
void PWM_ISR_Handler_StartEx(cyisraddress address);
void PWM_ISR_Handler_Stop(void);

CY_ISR_PROTO(PWM_ISR_Handler_Interrupt);

void PWM_ISR_Handler_SetVector(cyisraddress address);
cyisraddress PWM_ISR_Handler_GetVector(void);

void PWM_ISR_Handler_SetPriority(uint8 priority);
uint8 PWM_ISR_Handler_GetPriority(void);

void PWM_ISR_Handler_Enable(void);
uint8 PWM_ISR_Handler_GetState(void);
void PWM_ISR_Handler_Disable(void);

void PWM_ISR_Handler_SetPending(void);
void PWM_ISR_Handler_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PWM_ISR_Handler ISR. */
#define PWM_ISR_Handler_INTC_VECTOR            ((reg32 *) PWM_ISR_Handler__INTC_VECT)

/* Address of the PWM_ISR_Handler ISR priority. */
#define PWM_ISR_Handler_INTC_PRIOR             ((reg8 *) PWM_ISR_Handler__INTC_PRIOR_REG)

/* Priority of the PWM_ISR_Handler interrupt. */
#define PWM_ISR_Handler_INTC_PRIOR_NUMBER      PWM_ISR_Handler__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PWM_ISR_Handler interrupt. */
#define PWM_ISR_Handler_INTC_SET_EN            ((reg32 *) PWM_ISR_Handler__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PWM_ISR_Handler interrupt. */
#define PWM_ISR_Handler_INTC_CLR_EN            ((reg32 *) PWM_ISR_Handler__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PWM_ISR_Handler interrupt state to pending. */
#define PWM_ISR_Handler_INTC_SET_PD            ((reg32 *) PWM_ISR_Handler__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PWM_ISR_Handler interrupt. */
#define PWM_ISR_Handler_INTC_CLR_PD            ((reg32 *) PWM_ISR_Handler__INTC_CLR_PD_REG)


#endif /* CY_ISR_PWM_ISR_Handler_H */


/* [] END OF FILE */
