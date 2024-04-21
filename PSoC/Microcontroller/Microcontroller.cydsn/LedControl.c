#include "LedControl.h"   


uint8_t whiteSquareArray[64] = {
        0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0};
 

/*
Gå under fanen "Clocks" <--. Dobbeltklik "PLL_Out"
Sæt "Desired" under PLL_OUT til 70 Mhz
Sæt Master clock til at modtage "PLL_OUT(70 mHz)"
Indstil Divider til 1
*/


    /*     Array:

                  Byte1 Byte2 Byte3               

        Led 1    [[Grøn][Rød][Blå]]
        Led 2    [[Grøn][Rød][Blå]]
        ...      [...             ]
        Led 64   [[Grøn][Rød][Blå]]
    */

CY_ISR(PWM_ISR_handler)
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

void setLEDs(uint8_t array[SIZE])
{
    end = 1;
    for(int i = 0; i < NUM_LEDS; i++)
    {
        ledArray[i] = array[i];
    }
    
    // Lav en forløkke der løber igennem. HUSK at det der modtages er fra RPI legalMoves.
    // i array[i]. Hvis gældene plads skal tændes(er et 1'tal), 
    // køres der nogle if-statement, der styrer hvilken farve led'erne har.
    
    sensorScan(); // Opdaterer squareReg[]
    
    for (uint8_t i = 0; i < 64; i++) // Opdaterer ledData[SIZE*3] med de rigtige farver på led'erne
    {   
        if(whiteSquareArray[i]==1) //Hvis hvidt felt
        {
            if(ledArray[i] == 1 && ledArray[i] == squareReg[i]) //
            {    
                //Vælg Farve//
                ledData[i * 3]     = 0;       //Grøn
                ledData[i * 3 + 1] = WHITE_LED_INTESITY;     //Rød
                ledData[i * 3 + 2] = 0;     //Blå
            }
            if(ledArray[i] == 1 && ledArray[i] != squareReg[i])
            {
                //Vælg Farve//
                ledData[i * 3]     = 0;       //Grøn
                ledData[i * 3 + 1] = 0;       //Rød
                ledData[i * 3 + 2] = WHITE_LED_INTESITY;     //Blå
            }
            if(ledArray[i] == 0)
            {
                //Vælg Farve//
                ledData[i * 3]     = 0;       //Grøn
                ledData[i * 3 + 1] = 0;       //Rød   // Sluk
                ledData[i * 3 + 2] = 0;       //Blå
            }
        }
        else // Hvis sort felt
        {
            if(ledArray[i] == 1 && ledArray[i] == squareReg[i]) //
            {    
                //Vælg Farve//
                ledData[i * 3]     = 0;       //Grøn
                ledData[i * 3 + 1] = BLACK_LED_INTESITY;     //Rød
                ledData[i * 3 + 2] = 0;     //Blå
            }
            if(ledArray[i] == 1 && ledArray[i] != squareReg[i])
            {
                //Vælg Farve//
                ledData[i * 3]     = 0;       //Grøn
                ledData[i * 3 + 1] = 0;       //Rød
                ledData[i * 3 + 2] = BLACK_LED_INTESITY;     //Blå
            }
            if(ledArray[i] == 0)
            {
                //Vælg Farve//
                ledData[i * 3]     = 0;       //Grøn
                ledData[i * 3 + 1] = 0;       //Rød   // Sluk
                ledData[i * 3 + 2] = 0;       //Blå
            }
        }
    }  

    pwmLedInterrupt();
}

void pwmLedInterrupt()
{
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

void onlyDeadPosLED(int ledNr)
{
    end = 1;
    for (uint8_t i = 0; i < 64; i++)
    {
        ledData[i * 3]     = 0;          //Grøn
        ledData[i * 3 + 1] = 0;          //Rød  
        ledData[i * 3 + 2] = 0;          //Blå
        if(i == ledNr)
        {
            ledData[ledNr * 3]     = 0;      //Grøn
            ledData[ledNr * 3 + 1] = WHITE_LED_INTESITY;                 //Rød  
            ledData[ledNr * 3 + 2] = 0;                 //Blå
        }
    }
    
    pwmLedInterrupt();
}

void moveAcceptedLED(int ledNr)
{   
    end = 1;
    for (uint8_t i = 0; i < 64; i++)
    {
        ledData[i * 3]     = 0;          //Grøn
        ledData[i * 3 + 1] = 0;          //Rød  
        ledData[i * 3 + 2] = 0;          //Blå
        if(i == ledNr)
        {
            ledData[ledNr * 3]     = WHITE_LED_INTESITY;      //Grøn
            ledData[ledNr * 3 + 1] = 0;                 //Rød  
            ledData[ledNr * 3 + 2] = 0;                 //Blå
        }
    }
    
    pwmLedInterrupt();
    
    CyDelay(2000);
    
    turnOffLEDs();
}

void initLED()
{
    isr_PWM_StartEx(PWM_ISR_handler);
    bitIndex = 7;
    byteIndex = 0;
    turnOffLEDs();
}

void turnOffLEDs()
{
    uint8_t offArray[64] = {0};
    
    setLEDs(offArray);
}