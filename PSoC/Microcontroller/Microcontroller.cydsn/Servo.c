/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "Servo.h"

void servoOn()
{
    ServoPWM_WriteCompare(on_position);
    CyDelay(500);
}

void servoOff()
{
    ServoPWM_WriteCompare(off_position);
    CyDelay(500);
}

void initServo()
{
    ServoPWM_Start();
    servoOff();
}

/* [] END OF FILE */
