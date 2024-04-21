/*******************************************************************************
* File Name: ServoPWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ServoPWM.h"

static ServoPWM_backupStruct ServoPWM_backup;


/*******************************************************************************
* Function Name: ServoPWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ServoPWM_SaveConfig(void) 
{

    #if(!ServoPWM_UsingFixedFunction)
        #if(!ServoPWM_PWMModeIsCenterAligned)
            ServoPWM_backup.PWMPeriod = ServoPWM_ReadPeriod();
        #endif /* (!ServoPWM_PWMModeIsCenterAligned) */
        ServoPWM_backup.PWMUdb = ServoPWM_ReadCounter();
        #if (ServoPWM_UseStatus)
            ServoPWM_backup.InterruptMaskValue = ServoPWM_STATUS_MASK;
        #endif /* (ServoPWM_UseStatus) */

        #if(ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_256_CLOCKS || \
            ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_2_4_CLOCKS)
            ServoPWM_backup.PWMdeadBandValue = ServoPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(ServoPWM_KillModeMinTime)
             ServoPWM_backup.PWMKillCounterPeriod = ServoPWM_ReadKillTime();
        #endif /* (ServoPWM_KillModeMinTime) */

        #if(ServoPWM_UseControl)
            ServoPWM_backup.PWMControlRegister = ServoPWM_ReadControlRegister();
        #endif /* (ServoPWM_UseControl) */
    #endif  /* (!ServoPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoPWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ServoPWM_RestoreConfig(void) 
{
        #if(!ServoPWM_UsingFixedFunction)
            #if(!ServoPWM_PWMModeIsCenterAligned)
                ServoPWM_WritePeriod(ServoPWM_backup.PWMPeriod);
            #endif /* (!ServoPWM_PWMModeIsCenterAligned) */

            ServoPWM_WriteCounter(ServoPWM_backup.PWMUdb);

            #if (ServoPWM_UseStatus)
                ServoPWM_STATUS_MASK = ServoPWM_backup.InterruptMaskValue;
            #endif /* (ServoPWM_UseStatus) */

            #if(ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_256_CLOCKS || \
                ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_2_4_CLOCKS)
                ServoPWM_WriteDeadTime(ServoPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(ServoPWM_KillModeMinTime)
                ServoPWM_WriteKillTime(ServoPWM_backup.PWMKillCounterPeriod);
            #endif /* (ServoPWM_KillModeMinTime) */

            #if(ServoPWM_UseControl)
                ServoPWM_WriteControlRegister(ServoPWM_backup.PWMControlRegister);
            #endif /* (ServoPWM_UseControl) */
        #endif  /* (!ServoPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: ServoPWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ServoPWM_Sleep(void) 
{
    #if(ServoPWM_UseControl)
        if(ServoPWM_CTRL_ENABLE == (ServoPWM_CONTROL & ServoPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            ServoPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            ServoPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (ServoPWM_UseControl) */

    /* Stop component */
    ServoPWM_Stop();

    /* Save registers configuration */
    ServoPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: ServoPWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ServoPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ServoPWM_Wakeup(void) 
{
     /* Restore registers values */
    ServoPWM_RestoreConfig();

    if(ServoPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        ServoPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
