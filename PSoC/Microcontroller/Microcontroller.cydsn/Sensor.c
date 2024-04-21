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

#include "Sensor.h"


void sensorScan()
{
    sensorReset();
    for (int i = 0; i < 64; i++) 
    {
        if(sensorSignal_Read()==1)
        {
            CyDelayUs(scan_validation_delay_us);
            if(sensorSignal_Read()==1)
            {
                squareReg[i] = sensorSignal_Read(); //Læs sensorSignal for plads i på skakbrættet
            }
        }
        else if(sensorSignal_Read()==0 )
        {
            CyDelayUs(scan_validation_delay_us);
            if(sensorSignal_Read()==0)
            {
                squareReg[i] = sensorSignal_Read(); //Læs sensorSignal for plads i på skakbrættet
            }
        }   
        
        if(i<63)
        {
            sensorClk_Write(1); //Clock høj
            CyDelayUs(sensor_Clk_delay_us); //Clock Delay
            sensorClk_Write(0); //Clock lav
            CyDelayUs(sensor_Clk_delay_us);
        }
    }
}


void sensorPrintTest()
{
    //Her bruges fremgangsmåden fra UARTArrayPrintTest() til at udskrive arrayet på UART
    uint8_t row1=0, row2=0, row3=0, row4=0, 
            row5=0, row6=0, row7=0, row8=0;
    
    for(int i = 0; i < 8; i++) {
        row1 |= squareReg[i] << (7 - i);
        row2 |= squareReg[i + 8] << (7 - i);
        row3 |= squareReg[i + 16] << (7 - i);
        row4 |= squareReg[i + 24] << (7 - i);
        row5 |= squareReg[i + 32] << (7 - i);
        row6 |= squareReg[i + 40] << (7 - i);
        row7 |= squareReg[i + 48] << (7 - i);
        row8 |= squareReg[i + 56] << (7 - i);
    }
    
    for(int i = 0; i < 64; i++)
    {
        // Print Arrayet som ascii art på UART
    }

    //Echo back modtagne bytes - uden lille L(startChar)
    UART_1_WriteTxData(row1);
    UART_1_WriteTxData(row2);
    UART_1_WriteTxData(row3);
    UART_1_WriteTxData(row4);
    UART_1_WriteTxData(row5);
    UART_1_WriteTxData(row6);
    UART_1_WriteTxData(row7);
    UART_1_WriteTxData(row8);
}


void initSensor()
{
    sensorReset();
    sensorScan();
    updateLastSquareReg();
    newPos = -1; liftPos = -1; deadLiftPos = -1; //Nulstil positioner
}

void updateLastSquareReg()
{
    for(int i = 0; i < 64; i++)
    {
        lastSquareReg[i] = squareReg[i]; // loader seneste squareReg over i lastSquareReg
    }
}

uint8_t scan4PieceLift()
{
    updateLastSquareReg();
    
    sensorScan(); // Opdaterer squareReg
    
    for(int i = 0; i < 64; i++)
    {
        if(lastSquareReg[i] == 1 && squareReg[i] == 0)
        {
            CyDelayUs(change_validation_delay_us);
            sensorScan();
            if(lastSquareReg[i] == 1 && squareReg[i] == 0)
            {
                updateLastSquareReg();
                liftPos = i; // liftPos sættes til felt nummer i
                return 1;
            }
        }
    }
    
    liftPos = -1;
    return 0;
}

void scanNewPos()
{    
    sensorScan(); // Opdaterer squareReg
    
    for(int i = 0; i < 64; i++)
    {   
        if(lastSquareReg[i] == 0 && squareReg[i] == 1)
        {
            CyDelayUs(change_validation_delay_us);
            sensorScan();
            if(lastSquareReg[i] == 0 && squareReg[i] == 1)
            {
                newPos = i;
            }
        }
    }
    
}

 uint8_t scan4DeadOpp()
{    
    sensorScan(); // Opdaterer squareReg
    
    for(int i = 0; i < 64; i++)
    {
        if(lastSquareReg[i] == 1 && squareReg[i] == 0 && legalMoves[i] == 1 && i != liftPos) // Hvis der sker ændringer og det sker på et legalmove felt 
        {
            CyDelayUs(change_validation_delay_us);
            sensorScan();
            if(lastSquareReg[i] == 1 && squareReg[i] == 0)
            {
                deadLiftPos = i;
                return 1;
            }
        }
    }
    return 0;
}

int8_t newPosLegal()
{
    sensorScan(); // Opdater squareReg
    for(int i = 0; i < 64; i++)
    {
        // Hvis legal              og   hvis der er en brik på feltet og hvis newPos ikke er -1
        if(legalMoves[newPos] == 1 && squareReg[i]==1) 
        {
            return 1;
        }
        if(legalMoves[newPos] == 0 && squareReg[i]==1) //Ulovligt træk
        {
            return -1;
        }
    }
    return 0;
}

void sensorReset()
{
    sensorReset_Write(1); //Reset on
    CyDelay(sensor_Clk_delay_us); //Clock Delay
    sensorReset_Write(0); //Reset off
}

/* [] END OF FILE */
