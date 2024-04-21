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
#include "UART.h"

#define sensor_Clk_delay_us 1
#define scan_validation_delay_us 2000
#define change_validation_delay_us 3000

uint8_t lastSquareReg[64];
uint8_t squareReg[64];
uint8_t pieceLifted;
uint8_t deadPieceLifted;
int8_t newPos;
int8_t liftPos;
int8_t deadLiftPos;


void initSensor();
uint8_t scan4PieceLift();
void scanNewPos();
uint8_t scan4DeadOpp();
int8_t newPosLegal();
void updateLastSquareReg();
void sensorScan();
void sensorReset();

void sensorPrintTest(); //Debugging



/* [] END OF FILE */
