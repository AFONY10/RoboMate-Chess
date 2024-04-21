#include "project.h"
#include "LEDRoboMate.h"

#define SIZE 64

    CY_ISR_PROTO(ISR_PWM_handler);

int main(void)
{
     CyGlobalIntEnable; // Enable global interrupts
    
    
    uint8_t array [SIZE * 3];
    
    //Sluk / Tænd alle Led'er
    for(int i = 0; i < SIZE ; i++)
    {
     array[i * 3] = 0;
     array[i * 3 + 1] = 0;
     array[i * 3 + 2] = 0;
    }
    
    /*     Array:

                  Byte1 Byte2 Byte3               

        Led 1    [[Grøn][Rød][Blå]]
        Led 2    [[Grøn][Rød][Blå]]
        ...      [...             ]
        Led 64   [[Grøn][Rød][Blå]]
    */
    
    //Tænd en LED//
    
    //Vælg LED nr//
    int ledNr = 10;  
    
    //Vælg Farve//
    array[ledNr * 3]     = 0;       //Grøn
    array[ledNr * 3 + 1] = 255;     //Rød
    array[ledNr * 3 + 2] = 255;     //Blå
    
    
    setLEDs(array);

    for (;;)
    {
        // Your main loop code here
    }
}