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

// XY-Plotter.h
#include "project.h"
#include "Servo.h"
#include <stdio.h>
#include <stdlib.h>
   
#define SQUARES_PER_ROW 8 // Antal felter pr. række
#define stepperWait 1500 // mikrosekunder
#define STEPS_PER_SQUARE 223 // Antal steps pr. felt (40 mm). En runde = 200 steps. 
#define deadSquare 64 // Dødsgraven
void moveChessPiece(uint8_t fromSquare, uint8_t toSquare); // Funktion til at flytte brikken fra fromSquare til toSquare
struct stepDif calculateSquares(uint8_t fromSquare, uint8_t toSquare); // Funktion til at beregne antal trin mellem to kvadrater
void moveMotorX(float squares);// Funktion til at flytte steppermotor x
void moveMotorY(float squares); // Funktion til at flytte steppermotor y
void steppersOff(); // slukker stepper motor, for at undgå varme spoler.
void initXYPlotter(); 
void moveHome(); // kør hjem til felt 0

struct stepDif {
    int x;
    int y; };
uint8_t currentSquare;
uint8_t stepCase;


void motorTest(uint8_t P1_1, uint8_t P2_1, uint8_t P1_2, uint8_t P2_2); // Debugging af stepper motor
void XYPlotterTest(); //Debugging

/* [] END OF FILE */
