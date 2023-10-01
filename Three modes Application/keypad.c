#include "keypad.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include "std_types.h"
#include "calculator.h"

//**********ENUMERATION OF THE THREE PROJECT MODES*********//

typedef enum
{
  CALCULATOR, TIMER, STOPWATCH
}Project_Mode;

extern Project_Mode current;                                  //Extending the visibility of "current" across all source files
extern Project_Mode counter;                                  //Extending the visibility of "counter" across all source files


unsigned char keypad[4][4]= {{'1','2','3','+'},{'4','5','6','-'},{'7','8','9','/'},{'*','0','#','='}}; //Creating an array of keypad elements

//***DELAY FUNCTION***//

void delay(void){
for ( int i = 0 ; i <= 1000000 ; i++)
{
  i++;
}
}


void KeyPad_Init (void){

  GPIO_portINIT(PORTB);                                //PORT B initialization
  GPIO_portINIT(PORTC);                                //PORT C initialization
  GPIO_portINIT(PORTE);                                //PORT E initialization

  GPIO_setPortDirection(PORTB, 0xFF);                  //Setting pins 0->7 as digital outputs
  GPIO_setPortDirection(PORTC, 0xF0);                  //Setting pins 0->3 as digital inputs and pins 4->7 as digital outputs
  GPIO_setPortDirection(PORTE, 0x00);                  //Setting pins 0->7 as digital inputs 
  GPIO_PORTE_PDR_R = 0x0F;                             //Setting Pull Down Resistors for pins 0->3 for PORT E
}

//*******KEYPAD INPUT READ FUNCTION********//

unsigned char KeyPad_Read(void){
    while(1){
  if ( counter != current){break;}                     //Checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
  for(int i=4; i<8; i++)
  {
    GPIO_PORTC_DATA_R = (1<<i);
        switch(GPIO_readPort(PORTE)){
        case 0x00:
          break;
        case 0x01: 
          return keypad[0][i-4];                       //Returning all input contents of first row and the specified column
          break;
        case 0x02:
          return keypad[1][i-4];                        //Returning all input contents of second  row and the specified column
          break;
        case 0x04:
          return keypad[2][i-4];                        //Returning all input contents of third row and the specified column
          break;
        case 0x08:
          return keypad[3][i-4];                        //Returning all input contents of fourth row and the specified column
          break;
        }
    }
}
}

