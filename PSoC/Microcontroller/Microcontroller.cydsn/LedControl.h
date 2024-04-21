#pragma once

#include "project.h"
#include "Sensor.h"

#define WHITE_LED_INTESITY 20
#define BLACK_LED_INTESITY 255
#define SIZE 64
#define NUM_LEDS 64
//#define T_HIGH 0   
//#define T_LOW 27   
#define T_HIGH 40   
#define T_LOW 90


CY_ISR_PROTO(PWM_ISR_handler);

uint8_t ledArray[64];
uint8_t ledData[64 * 3];
int8_t bitIndex;
uint16_t byteIndex;
int end;


void setLEDs(uint8_t array[64]);
void pwmLedInterrupt();
void turnOffLEDs();
void onlyDeadPosLED(int ledNr);
void moveAcceptedLED(int ledNr);
void initLED();

