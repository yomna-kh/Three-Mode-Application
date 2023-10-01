
#include "GPIO.h"
#include "timer.h"
#include "keypad.h"
#include "LCD_Driver.h"
#include "delay.h"
#include "calculator.h"
#include "stopwatch.h"

//**********ENUMERATION OF THE THREE PROJECT MODES*********//

typedef enum
{
  CALCULATOR, TIMER, STOPWATCH
}Project_Mode;

sint32 Stopwatch_Minutes = 0;                               //Initialization of total minutes displayed
sint32 Stopwatch_Seconds = 0;                                //Initialization of total seconds displayed
uint8 Stopwatch_ON = 0;                                      //Disabling Stop watch initially

extern Project_Mode current ;                                //Extending the visibility of "current" across all source files
extern Project_Mode counter ;                                 //Extending the visibility of "counter" across all source files

//**********STOPWATCH MODE FUNCTION***********//

void StopWatch(void)
{
      current = STOPWATCH;                                    //Current value is given index no.2 of Stopwatch mode
  if (Stopwatch_ON == 0)                                      
  {
    LCD_Cmd(cursorOff);                                        //Setting OFF the cursor of the LCD                       
    LCD_Cmd(clear_display);                                     //Clearing all contents on LCD
    LCD_printString("   STOPWATCH");
    delay_ms(2000);
    LCD_Cmd(clear_display);                                     //Clearing all contents on LCD
    LCD_printString("00:00");
    Stopwatch_Seconds = 0;
    Stopwatch_Minutes = 0;
  }
    LCD_Cmd(clear_display);                                     //Clearing all contents on LCD
    while(1)
    {
      if ( counter != current){return;}                         //Checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
      if(Stopwatch_Minutes<10)
      {
          LCD_Write_Char('0');                                   //Displaying '0' once the total minutes number have elapsed
      }
      LCD_printInteger(Stopwatch_Minutes);                        //Displaying the current number of minutes
      LCD_printString(":");
      if(Stopwatch_Seconds<10)
      {
         if ( counter != current){return;}                      //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
          LCD_Write_Char('0');                                   //Displaying '0' once the total seconds number have elapsed
      }
      LCD_printInteger(Stopwatch_Seconds);                       //Displaying the current number of seconds
      LCD_Cmd(returnHome);                                       ////Clearing display and returning cursor to home position
     if ( counter != current){return;}                          //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
    
     if (GPIO_readPort(PORTA) == 0X18)                          //Checking if PA2 is pressed
     {
       pause_pushbutton();                                     // pin 2 pressed
     }
     
     else if(GPIO_readPort(PORTA) == 0x14)                     //Checking if PA3 is pressed
       
     {
       start_pushbutton();                                     // pin 3 pressed
     }
     
     else if(GPIO_readPort(PORTA) == 0X0C)                    //Checking if PA4 is pressed
     {
       reset_pushbutton();                                    // pin 4 pressed
     }
  }
  }
  
//**********STOPWATCH CALL BACK FUNCTION**********//

void call_back_stopwatch (void)                               //Stopwatch call back function that sends the address of the function to ISR to start execution
{
  Stopwatch_Seconds++;
  if(Stopwatch_Seconds == 60)
  {
    Stopwatch_Seconds = 0;                                     //Resetting total seconds to zero after incrementing to max limit
    Stopwatch_Minutes++;
  }
  
}

//**********STOPWATCH PAUSE FUNCTION**********//

void pause_pushbutton (void)
{
  Timer_DENAB(TIMER_1);                                       //Disabling stopwatch on pressing pause PB
  delay_ms(500);
}

//**********STOPWATCH START/RESUME FUNCTION**********//

void start_pushbutton (void)
{
  Timer_ENAB(TIMER_1);                                       //Enabling/Re-Enabling stopwatch on pressing start PB
  Stopwatch_ON = 1;
  delay_ms(500);
}

//**********STOPWATCH RESET FUNCTION**********//

void reset_pushbutton (void)                                
{
  /*Reset the Timer to start from Zero*/
  Timer_DENAB(TIMER_1);                                    //Resetting stopwatch on pressing reset PB
  Stopwatch_ON = 0;
  Stopwatch_Seconds = 0;
  Stopwatch_Minutes = 0;
  delay_ms(500);
}
