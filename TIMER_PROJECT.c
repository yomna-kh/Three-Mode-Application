#include "GPIO.h"
#include "timer.h"
#include "keypad.h"
#include "LCD_Driver.h"
#include "delay.h"
#include "calculator.h"
#include "Timer_project.h"

sint32 minutes_total;                                                   //Declaring a variable for displaying the total minutes on LCD 
sint32 seconds_total;                                                 //Declaring a variable for displaying the total seconds on LCD
uint8 Timer_ON = 0;                                                  //Disbaling Timer initially

//**********ENUMERATION OF THE THREE PROJECT MODES*********//

typedef enum
{
  CALCULATOR, TIMER, STOPWATCH
}Project_Mode;                                                    //Enumeration of the three Project modes

extern Project_Mode current;                                    //Extending the visibility of "current" across all source files
extern Project_Mode counter;                                  //Extending the visibility of "counter" across all source files

//**********TIMER MODE FUNCTION***********//

void TimerMode(void)
{
  LCD_Cmd(clear_display);                                    //Clearing all contents on LCD
  current = TIMER;                                          //Current value is given index no.1 of Timer mode
  if(Timer_ON == 0)
  {
  uint8 key;
  uint8 minutes1;                                      //Declaring the first digit of minutes number entered by user
  uint8 seconds1;                                      //Declaring the first digit of seconds number entered by user
  uint8 minutes2;                                      //Declaring the second digit of minutes number entered by user
  uint8 seconds2;                                      //Declaring the second digit of seconds number entered by user
  
  LCD_Cursor(0 ,3);                                  //Setting the position at which the subsequent text written to the lCD will begin
  LCD_Cmd(cursorOff);                                //Setting OFF the cursor of the LCD
  LCD_printString("TIMER MODE");
  delay_ms(2000);
  LCD_Cmd(clear_display);                         //Clearing all contents on LCD
  LCD_printString("00:00");
  LCD_Cursor(0,0);                                //Setting the position of text at the top left of the LCD screen
  LCD_Cmd(cursorBlink);                           //Blinking the LCD cursor to wait for an input from user
  minutes1 = KeyPad_Read();                       //stores the first key pressed by the user 
  if ( counter != current){return;}               //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
  delay_ms(500);
  LCD_Cmd(clear_display);                        //Clearing all previously written contents on LCD
  LCD_Write_Char(minutes1);                      //Displaying first digit of minutes entered by user on LCD
  minutes2 = KeyPad_Read();                      //stores the second key pressed by the user 
  if ( counter != current){return;}              //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
  delay_ms(500);
  LCD_Write_Char(minutes2);                     //Displaying second digit of minutes entered by user on LCD
  LCD_printString(":");
  seconds1 = KeyPad_Read();                     //stores the third key pressed by the user 
  if ( counter != current){return;}             //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
  delay_ms(500);
  LCD_Write_Char(seconds1);                     //Displaying first digit of seconds entered by user on LCD
  seconds2 = KeyPad_Read();                      //stores the fourth key pressed by the user 
  if ( counter != current){return;}             //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
  delay_ms(500);
  LCD_Write_Char(seconds2);                      //Displaying second digit of seconds entered by user on LCD
  minutes_total=((minutes1-48)*10)+((minutes2-48)*1);                                  //Converting the total minutes from char to int
  seconds_total=((seconds1-48)*10)+((seconds2-48)*1);                                 //Converting the total seconds from char to int
  do
  {
    key = KeyPad_Read();                         //CONTINUE TAKING USER INPUT FOR MINUTES AND SECONDS UNTIL "=" IS PRESSED
    if ( counter != current){return;}             //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
    
  }while(key != '=');
  Timer_ENAB(TIMER_0);                            //Enable timer 0 to start counting down once the user has pressed "=" 
  Timer_ON = 1;                                   //Timer 0 is enabled
    if ( counter != current){return;}             //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes

  }
  LCD_Cmd(returnHome);                            //Clearing display and returning cursor to home position
  LCD_Cmd(cursorOff);                             //Setting OFF the cursor of the LCD
  while(Timer_ON == 1)
  {
    LCD_Cmd(returnHome);                          //Clearing display and returning cursor to home position

    if(minutes_total<10)
    {
          
      LCD_Write_Char('0');                        //Displaying '0' once the total minutes number have elapsed
      if ( counter != current){return;}           //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
    }
    
    LCD_printInteger(minutes_total);              //Displaying the current number of minutes
    LCD_printString(":");
    if(seconds_total<10)
    {
         
      LCD_Write_Char('0');                      //Displaying '0' once the total seconds number have elapsed
      if ( counter != current){return;}         //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes

    }
        
    LCD_printInteger(seconds_total);            //Displaying the current number of seconds
    if ( counter != current){return;}           //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes

  }
}

//**********BUZZER INITIALIZATION***********//

void Buzzer_Init(void)
{
  GPIO_portINIT(PORTF);                             //Initializing PORT F
  GPIO_setPinDirection(PORTF, PIN1, PIN_OUTPUT);    //Setting PF1 as digital output
}
  
//**********BUZZER ENABLE FUNCTION***********//

void Buzzer_ON(void)
{
  GPIO_writePin(PORTF,PIN1,LOGIC_HIGH);
}

//**********BUZZER DISABLE FUNCTION***********//

void Buzzer_OFF(void)
{
  GPIO_writePin(PORTF,PIN1,LOGIC_LOW); 
}

//**********TIMER CALL BACK FUNCTION**********//

void call_back_Timer(void)                          //Timer call back function that sends the address of the function to ISR to start execution
{
seconds_total--;
if ((seconds_total == -1)&&(minutes_total == 0))
        {
          Timer_ON = 0;                             //Disabling Timer after elapsing
          Timer_DENAB(TIMER_0);
          Buzzer_ON();                              //Enabling buzzer after Timer elapse
          delay_ms(1000);
          Buzzer_OFF();                             //Disabling buzzer after delay
          seconds_total = 0;
        }
	if (seconds_total == -1)
	{
		seconds_total = 59;                 
		minutes_total --;                    //Decrementing minutes after elapsing seconds
	}    
}




