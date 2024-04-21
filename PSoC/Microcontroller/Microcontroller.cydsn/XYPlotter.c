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


// Funktion til at flytte brik fra fromSquare til toSquare
void moveChessPiece(uint8_t fromSquare, uint8_t toSquare) {
    // Udtryk for at rykke fra currentSquare til fromSquare
    struct stepDif moveToStart = calculateSquares(currentSquare, fromSquare);
    
    // Ryk magnet til startposition
    moveMotorX(moveToStart.x);
    moveMotorY(moveToStart.y);
    
    servoOn(); //Tænd magnet
    
    struct stepDif stepsToMove = calculateSquares(fromSquare, toSquare);
    
    if(stepsToMove.x>=0){     //Positv x 
    moveMotorX(0.5);
        if(stepsToMove.y>=0){ //Positv y
            moveMotorY(0.5);
            moveMotorY(stepsToMove.y-1);
            moveMotorX(stepsToMove.x-0.5);
            moveMotorY(0.5);
            CyDelay(1000);
            servoOff(); //sluk magnet
        }
        else{                 //Negativ y
            moveMotorY(-0.5);
            moveMotorY(stepsToMove.y+1);
            moveMotorX(stepsToMove.x-0.5);
            moveMotorY(-0.5);
            CyDelay(1000);
            servoOff(); //sluk magnet
        }
    }
    else{                     //Negativ x
    moveMotorX(-0.5);
        if(stepsToMove.y>=0){ //Positv y
            moveMotorY(0.5);
            moveMotorY(stepsToMove.y-1);
            moveMotorX(stepsToMove.x+0.5);
            moveMotorY(0.5);
            CyDelay(1000);
            servoOff(); //sluk magnet
        }
        else{                 //Negativ y
            moveMotorY(-0.5);
            moveMotorY(stepsToMove.y+1);
            moveMotorX(stepsToMove.x+0.5);
            moveMotorY(-0.5);
            CyDelay(1000);
            servoOff(); //sluk magnet
        }
    }
    
    
    
    //Opdater magnetens position
    currentSquare = toSquare;
    
    //CyDelay(1000); //Vent til magnet er færdig med at bevæge sig.
}

// Funktion til at beregne antal steps mellem to felter
struct stepDif calculateSquares(uint8_t fromSquare, uint8_t toSquare) {
    // Beregn x og y for både fromSquare og toSquare
    uint8_t fromX = fromSquare % SQUARES_PER_ROW;
    uint8_t toX = toSquare % SQUARES_PER_ROW;
    
    uint8_t fromY = fromSquare / SQUARES_PER_ROW;
    uint8_t toY = toSquare / SQUARES_PER_ROW;
    
    // Beregn række- og kolonneforskellen
    struct stepDif dif;
    dif.x = (toX - fromX);
    dif.y = (toY - fromY);
    return dif;
}


// Funktion til at styre steppermotor x
void moveMotorX(float squares) {
    int moveSteps = squares * STEPS_PER_SQUARE;
	for(int i = 0; i < abs(moveSteps); i++){
		if (moveSteps > 0){  //positiv retning?(med uret)
            switch(stepCase){
                case 1:
                P2_3_Write(1); //P1.1
                P2_4_Write(0); //P2.1
                P2_5_Write(0); //P1.2
                P2_6_Write(0); //P2.2
                stepCase++;
                CyDelayUs(stepperWait);
                break;
                case 2:
                P2_3_Write(0); 
                P2_4_Write(1);
                P2_5_Write(0);
                P2_6_Write(0);
                stepCase++;
                CyDelayUs(stepperWait);
                break;
                case 3:
                P2_3_Write(0);
                P2_4_Write(0);
                P2_5_Write(1);
                P2_6_Write(0);
                stepCase++;
                CyDelayUs(stepperWait);
                break;
                case 4:
                P2_3_Write(0);
                P2_4_Write(0);
                P2_5_Write(0);
                P2_6_Write(1);
                CyDelayUs(stepperWait);
                stepCase = 1; //reset stepCase
                break;
            }
		}
		else{               //negativ retning?(mod uret)
            switch(stepCase){
                case 4:
                P2_3_Write(0);
                P2_4_Write(0);
                P2_5_Write(0);
                P2_6_Write(1);
                stepCase--;
                CyDelayUs(stepperWait);
                break;
                case 3:
                P2_3_Write(0);
                P2_4_Write(0);
                P2_5_Write(1);
                P2_6_Write(0);
                stepCase--;
                CyDelayUs(stepperWait);
                break;
                case 2:
                P2_3_Write(0);
                P2_4_Write(1);
                P2_5_Write(0);
                P2_6_Write(0);
                stepCase--;
                CyDelayUs(stepperWait);
                break;
                case 1:
                P2_3_Write(1);
                P2_4_Write(0);
                P2_5_Write(0);
                P2_6_Write(0);
                stepCase = 4; //reset stepcase
                CyDelayUs(stepperWait);
                break;
            }
		}
	}
    steppersOff();
}
// Funktion til at styre steppermotor y
void moveMotorY(float squares) {
    int moveSteps = squares * STEPS_PER_SQUARE;
	for(int i = 0; i < abs(moveSteps); i++){
		if (moveSteps > 0){  //positiv retning?(med uret)
            switch(stepCase){
                case 1:
                P3_3_Write(1); //P1.1
                P3_4_Write(0); //P3.1
                P3_5_Write(0); //P1.2
                P3_6_Write(0); //P3.2
                stepCase++;
                CyDelayUs(stepperWait);
                break;
                case 2:
                P3_3_Write(0); 
                P3_4_Write(1);
                P3_5_Write(0);
                P3_6_Write(0);
                stepCase++;
                CyDelayUs(stepperWait);
                break;
                case 3:
                P3_3_Write(0);
                P3_4_Write(0);
                P3_5_Write(1);
                P3_6_Write(0);
                stepCase++;
                CyDelayUs(stepperWait);
                break;
                case 4:
                P3_3_Write(0);
                P3_4_Write(0);
                P3_5_Write(0);
                P3_6_Write(1);
                CyDelayUs(stepperWait);
                stepCase = 1; //reset stepCase
                break;
            }
		}
		else{               //negativ retning?(mod uret)
            switch(stepCase){
                case 4:
                P3_3_Write(0);
                P3_4_Write(0);
                P3_5_Write(0);
                P3_6_Write(1);
                stepCase--;
                CyDelayUs(stepperWait);
                break;
                case 3:
                P3_3_Write(0);
                P3_4_Write(0);
                P3_5_Write(1);
                P3_6_Write(0);
                stepCase--;
                CyDelayUs(stepperWait);
                break;
                case 2:
                P3_3_Write(0);
                P3_4_Write(1);
                P3_5_Write(0);
                P3_6_Write(0);
                stepCase--;
                CyDelayUs(stepperWait);
                break;
                case 1:
                P3_3_Write(1);
                P3_4_Write(0);
                P3_5_Write(0);
                P3_6_Write(0);
                stepCase = 4; //reset stepcase
                CyDelayUs(stepperWait);
                break;
            }
		}
	}
    steppersOff();
}

void initXYPlotter()
{
    stepCase = 1;
    currentSquare = 0;
}

void motorTest(uint8_t P1_1, uint8_t P2_1,uint8_t P1_2, uint8_t P2_2)
{
P2_3_Write(P1_1); //P1.1
P2_4_Write(P2_1); //P2.1
P2_5_Write(P1_2); //P1.2
P2_6_Write(P2_2); //P2.2
}

void steppersOff()
{
P2_3_Write(0); 
P2_4_Write(0); 
P2_5_Write(0); 
P2_6_Write(0); 
P3_3_Write(0); 
P3_4_Write(0); 
P3_5_Write(0);
P3_6_Write(0); 
}

void XYPlotterTest()
{
    //moveChessPiece(1,12);
    moveMotorY(-5);
    moveMotorY(5);
    

    //moveMotorX(1);
    //moveMotorX(-1);
    //motorTest(1,1,0,0);
    //motorTest(0,1,1,0);
    //motorTest(0,0,1,1);
    //motorTest(1,0,0,1);
}

void moveHome()
{
    servoOff();
        // Udtryk for at rykke fra currentSquare til fromSquare
    struct stepDif moveToStart = calculateSquares(currentSquare, 0);
    
    // Ryk magnet til startposition
    moveMotorX(moveToStart.x);
    moveMotorY(moveToStart.y);
    
    //Opdater magnetens position
    currentSquare = 0;
    CyDelay(500);
}
/* [] END OF FILE */
