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
#pragma once


#include "project.h"
#include "XYPlotter.h"
#include "LedControl.h"
#include "Servo.h"
#include "Sensor.h"

CY_ISR_PROTO(isr_uart_rx_handler);
uint8_t startChar;
uint8_t legalMoves[64];

void UARTHandler(uint8_t byteRecieved);
void UARTSendArray();
void initUART();

void UARTArrayPrintTest(); //Debugging
void UARTLedTest(); //Debugging

/* [] END OF FILE */
