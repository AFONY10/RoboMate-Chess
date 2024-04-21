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

#include "UART.h"

CY_ISR(isr_uart_rx_handler)  // UART recieve interrupt
{
    isr_uart_rx_Disable();//Stopper uart interrupt, så handleren ikke bliver afbrudt.
    
    uint8_t buf = UART_1_GetRxBufferSize();   
    
    if(buf==9)
    {
        startChar = UART_1_GetChar();

        if(startChar == 'l' || startChar == 'm' || startChar == 'd')
        {
            UARTHandler(startChar);
        }
    }
    
    isr_uart_rx_Enable(); // Starter UART interrupt igen.
}

void UARTHandler(uint8_t startChar) //Switch med input fra UART interrupt.
{
    switch(startChar)
    {
    case 'l': //lille 'L' styrer LED'er
        {   
        // Opretter 8 variabler af typen uint8_t
            uint8_t rxByte1=0, rxByte2=0, rxByte3=0, rxByte4=0, 
                    rxByte5=0, rxByte6=0, rxByte7=0, rxByte8=0;
            
            //Kopiere modtagne bytes ind i variablerne
            rxByte1 = UART_1_ReadRxData();
            rxByte2 = UART_1_ReadRxData();
            rxByte3 = UART_1_ReadRxData();
            rxByte4 = UART_1_ReadRxData();
            rxByte5 = UART_1_ReadRxData();
            rxByte6 = UART_1_ReadRxData();
            rxByte7 = UART_1_ReadRxData();
            rxByte8 = UART_1_ReadRxData();

            // Loader de 8 variabler over i arrayet
            for (int i = 0; i < 8; i++) {
                    legalMoves[i]      = (rxByte8 >> i) & 1;
                    legalMoves[i + 8]  = (rxByte7 >> i) & 1;
                    legalMoves[i + 16] = (rxByte6 >> i) & 1;
                    legalMoves[i + 24] = (rxByte5 >> i) & 1;
                    legalMoves[i + 32] = (rxByte4 >> i) & 1;
                    legalMoves[i + 40] = (rxByte3 >> i) & 1;
                    legalMoves[i + 48] = (rxByte2 >> i) & 1;
                    legalMoves[i + 56] = (rxByte1 >> i) & 1;
            }
            
            //legalMovesRecieved = 1;
            setLEDs(legalMoves); // Kalder LED funktionen med arrayet.
        }
        break;

        case 'd': //Brik der rykkes til dødsgrav
        {
            uint8_t fromSquare = UART_1_ReadRxData();
            UART_1_ClearRxBuffer(); //Fjern de tomme bytes i RX-bufferen
            
            moveChessPiece(fromSquare, deadSquare); // Brik rykkes til dødsgraven
            UART_1_PutChar('s'); //Brik rykket med succes. RPI orienteres

        }
        break;

        case 'm': //Ryk brik og vent til brik 
        {
            uint8_t fromSquare = UART_1_ReadRxData();
            uint8_t toSquare = UART_1_ReadRxData();
            UART_1_ClearRxBuffer(); //Fjern de tomme bytes i RX-bufferen
            
            moveChessPiece(fromSquare, toSquare);
            
            while(1) //vent indtil feltet hvor RoboMate har rykket en brik til er 1
            {
                sensorScan();
                if(squareReg[toSquare] == 1)
                {
                    CyDelayUs(change_validation_delay_us);
                    sensorScan();
                    if(squareReg[toSquare] == 1)
                    {
                        break;
                    }
                }
            }
            moveAcceptedLED(toSquare);
            newPos = -1; liftPos = -1; //Nulstil new position
            sensorScan();
            UART_1_PutChar('s'); //Brik rykket med succes. RPI orienteres
            break;
        }
        break;
        
        case 'r': // Reset PSoC
            {
                moveHome(); // Kør tilbage til felt 0.
                CySoftwareReset();
            }
            break;
            
        default :
            {
            // nothing
            }
            break;
    }
}

void initUART()
{
    UART_1_Start(); //Start Uart
    isr_uart_rx_StartEx(isr_uart_rx_handler); // UART interrupt initialisering
}

void UARTArrayPrintTest()
{
    // Opretter 8 variabler af typen uint8_t
    uint8_t byte1 = 0b00000001;
    uint8_t byte2 = 0b00000011;
    uint8_t byte3 = 0b00000111;
    uint8_t byte4 = 0b00001111;
    uint8_t byte5 = 0b00011111;
    uint8_t byte6 = 0b00111111;
    uint8_t byte7 = 0b01111111;
    uint8_t byte8 = 0b11111111;
    

    // Loader de 8 variabler over i arrayet
    for(int i = 0; i < 8; i++) {
        legalMoves[i]      = (byte1 >> (7 - i)) & 1;
        legalMoves[i + 8]  = (byte2 >> (7 - i)) & 1;
        legalMoves[i + 16] = (byte3 >> (7 - i)) & 1;
        legalMoves[i + 24] = (byte4 >> (7 - i)) & 1;
        legalMoves[i + 32] = (byte5 >> (7 - i)) & 1;
        legalMoves[i + 40] = (byte6 >> (7 - i)) & 1;
        legalMoves[i + 48] = (byte7 >> (7 - i)) & 1;
        legalMoves[i + 56] = (byte8 >> (7 - i)) & 1;
    }
    
    uint8_t arrayByte1=0, arrayByte2=0, arrayByte3=0, arrayByte4=0, 
            arrayByte5=0, arrayByte6=0, arrayByte7=0, arrayByte8=0;
    
    for(int i = 0; i < 8; i++) {
        arrayByte1 |= legalMoves[i] << (7 - i);
        arrayByte2 |= legalMoves[i + 8] << (7 - i);
        arrayByte3 |= legalMoves[i + 16] << (7 - i);
        arrayByte4 |= legalMoves[i + 24] << (7 - i);
        arrayByte5 |= legalMoves[i + 32] << (7 - i);
        arrayByte6 |= legalMoves[i + 40] << (7 - i);
        arrayByte7 |= legalMoves[i + 48] << (7 - i);
        arrayByte8 |= legalMoves[i + 56] << (7 - i);
    }

    //Echo back modtagne bytes - uden lille L(startChar)
    UART_1_WriteTxData(arrayByte1);
    UART_1_WriteTxData(arrayByte2);
    UART_1_WriteTxData(arrayByte3);
    UART_1_WriteTxData(arrayByte4);
    UART_1_WriteTxData(arrayByte5);
    UART_1_WriteTxData(arrayByte6);
    UART_1_WriteTxData(arrayByte7);
    UART_1_WriteTxData(arrayByte8);
}

void UARTLedTest()
{
    
    // Opretter 8 variabler af typen uint8_t
    uint8_t byte1 = 0b00000000;
    uint8_t byte2 = 0b00000000;
    uint8_t byte3 = 0b00000000;
    uint8_t byte4 = 0b00000000;
    uint8_t byte5 = 0b00000010;
    uint8_t byte6 = 0b00000110;
    uint8_t byte7 = 0b00000000;
    uint8_t byte8 = 0b00000000;
    
    // TX og RX kortsluttes på PSoC
    
    // Arrayet sendes på UART TX
    UART_1_PutChar('l'); //lille L
    UART_1_WriteTxData(byte1);
    UART_1_WriteTxData(byte2);
    UART_1_WriteTxData(byte3);
    UART_1_WriteTxData(byte4);
    UART_1_WriteTxData(byte5);
    UART_1_WriteTxData(byte6);
    UART_1_WriteTxData(byte7);
    UART_1_WriteTxData(byte8);
}




/* [] END OF FILE */
