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
#include "XYPlotter.h"
#include "Sensor.h"
#include "UART.h"
#include "LedControl.h"
#include "Servo.h"

int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */
    initUART();
    initLED(); 
    initXYPlotter();
    initSensor();
    initServo();

    
    for (;;) 
    {
        start:
        pieceLifted = scan4PieceLift(); //opdaterer liftPos og returnerer 1 hvis en brik bliver løftet
        
        if(pieceLifted == 1)
        {
            pieceLifted = 0;            
            
//            UART_1_PutChar('o'); //startChar for løft
//            UART_1_WriteTxData(liftPos); //Sender hvilket felt der er løftet en brik fra.
            
            
            UARTLedTest(); //Fjernes når RPI kobles til.
            do
            {                
                tryAgain: // goto label ved ulovligt træk.
                scanNewPos(); //opdater newPos
                
                if(newPos == liftPos && newPos != -1) // Hvis en brik placeres på samme position som løfte position
                {
                    CyDelayUs(change_validation_delay_us*3);
                    scanNewPos();
                    if(newPos == liftPos)
                    {
                        newPos = -1; liftPos = -1; //Nulstil new position
                        turnOffLEDs(); // Sluk for led'er
                        UART_1_PutChar('e'); //Skriv til RPI at brik er på samme felt
                        goto start; //Springer resten af do-while over.
                    }
                }
                
                deadPieceLifted = scan4DeadOpp(); //Hvis en brik bliver dræbt
                if(deadPieceLifted == 1) //Hvis ny brik bliver løftet på et legalmove er en død brik løftet. 
                {
                    deadPieceLifted = 0;
                    onlyDeadPosLED(deadLiftPos); //Slukker alle andre LED'er end død briks position.
                    updateLastSquareReg();
                    do // Vent til brik er sat på død briks position.
                    {
                        sensorScan();
                    }while(squareReg[deadLiftPos] == 0);
                }

            }while(newPosLegal()==0 || newPosLegal() == -1); // indtil newPos har fået en ny og lovlig position //fjernet && newPos == liftPos
            
            if(newPosLegal()== -1) // Hvis brik sat ulovligt
            {
                UART_1_PutChar('i'); //Skriv til RPI af brik er placeret ulovligt.
                LED_1_Write(1); //Blå LED tændes som visuel indikator
                do
                {
                    sensorScan();     // Opdater squareReg indtil brik fra ulovlig position er fjernet
                }while(squareReg[newPos] == 1);
                LED_1_Write(0); //Blå LED slukkes igen
                newPos = -1; liftPos = -1; deadLiftPos = -1; //Nulstil positioner
                newPos = -1; liftPos = -1; // nulstil newPos og liftPos
                goto tryAgain; 
            }
            
            if(newPosLegal()==1)
            {
                UART_1_PutChar('n'); //startChar for ny placering af brik
                UART_1_WriteTxData(newPos); //send brikkens nye position
                moveAcceptedLED(newPos); //Grønt lys på den nye position, hvis brik er placeret lovligt.
                moveChessPiece(liftPos,newPos);
                newPos = -1; liftPos = -1; deadLiftPos = -1; //Nulstil positioner
            }
        }
    }
}

/* [] END OF FILE */