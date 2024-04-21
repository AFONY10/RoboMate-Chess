#include "LEDRoboMate.h"
#define NUM_LEDS 64

#define T_HIGH 0   
#define T_LOW 27   

volatile int8_t bitIndex = 7;
volatile uint16_t byteIndex = 0;

volatile uint8_t ledData[NUM_LEDS * 3];
int end = 1;

/*
Gå under fanen "Clocks" <--. Dobbeltklik "PLL_Out"
Sæt "Desired" under PLL_OUT til 70 Mhz
Sæt Master clock til at modtage "PLL_OUT(70 mHz)"
Indstil Divider til 1
*/



CY_ISR(PWM_ISR_Handler)
{
    if (ledData[byteIndex] & (1 << bitIndex) && bitIndex >= 0)
    {
        PWM_WriteCompare(T_HIGH);
        Control_Reg_1_Write(1);
    }
    else
    {
        PWM_WriteCompare(T_LOW);
        Control_Reg_1_Write(1);
    }

    bitIndex--;

    PWM_ReadStatusRegister();
}

    /*     Array:

                  Byte1 Byte2 Byte3               

        Led 1    [[Grøn][Rød][Blå]]
        Led 2    [[Grøn][Rød][Blå]]
        ...      [...             ]
        Led 64   [[Grøn][Rød][Blå]]
    */



void setLEDs(uint8_t array[])
{
    isr_PWM_StartEx(PWM_ISR_Handler);
    
    
    // Initialize data for the LEDs and start PWM
    
    for (int i = 0; i < NUM_LEDS; i++)
    {
        ledData[i * 3] = array[i * 3];     // Grøn
        ledData[i * 3 + 1] = array[i * 3 + 1]; // Rød
        ledData[i * 3 + 2] = array[i * 3 + 2];   // Blå
    }

    
    PWM_Start();
    Control_Reg_1_Write(1);

    // Vent indtil alle bits er sendt
    while(end)
    { 
        
            // Tjek om vi har sendt alle 24 bits
    if (bitIndex < 0)
    {
        bitIndex = 7;
        byteIndex++;
        if(byteIndex >= (NUM_LEDS * 3))
        {
        // Alle bits er blevet sendt, stop PWM
        PWM_Stop();
        byteIndex = 0;
        end = 0;
        }
    }
    }
}

