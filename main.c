#include "GPIO.h"
#include "timer.h"
#include "keypad.h"
#include "LCD_Driver.h"
#include "calculator.h"
#include "Timer_project.h"
#include "stopwatch.h"

//**********ENUMERATION OF THE THREE PROJECT MODES*********//

typedef enum
{
  CALCULATOR, TIMER, STOPWATCH
}Project_Mode;

Project_Mode current = CALCULATOR;                            //Initial value of "current" is index 0
Project_Mode counter = CALCULATOR;                           //Initial value of "counter" is index 0       

Timer_ConfigType Timer_0 = {64000 ,255,PERIODIC_DOWN,TIMER_0};    
/*Configuring Timer 0 with the following parameters: Reload Value = 64000, Prescaler value = 255, Down, periodic counter*/
Timer_ConfigType Timer_1 = {64000 ,255,PERIODIC_DOWN,TIMER_1};
/*Configuring Timer 1 with the following parameters: Reload Value = 64000, Prescaler value = 255, Down, periodic counter*/
void switchmode (void);
void GPIO_portsSetup(void);

void (*fun_ptr[])(void)
= {Calculate, TimerMode, StopWatch};

 int main()
{
  LCD_init();                          //LCD Initialization
  KeyPad_Init();                       //Keypad Initialization
  Calc_init();                         //Calculator Initialization
  Buzzer_Init();                       //Buzzer Initialization
  LCD_Cmd(clear_display);               //Clearing all contents on LCD
  Timer_init(&Timer_0);                 //Timer 0 Initialization
  Timer_setCallBack(TIMER_0, call_back_Timer);  //Setting ptr to point out to the call back function of timer 0
  Timer_init(&Timer_1);                 //Timer 1 Initialization
  Timer_setCallBack(TIMER_1, call_back_stopwatch);   //Setting ptr to point out to the call back function of timer 1
  GPIO_portsSetup();

  while(1)
  {
   (*fun_ptr[counter])();             //Continue operation within the same mode 
  }
}


void GPIO_portsSetup(void)
{
 // PORTS interrupts initialization
   // System clock
    GPIO_portINIT(PORTF);
    GPIO_portINIT(PORTA);
    
    //Interrupt pins direction
    GPIO_setPinDirection(PORTF, PIN4, PIN_INPUT);
    
    //Stopwatch pins Directions
    GPIO_setPinDirection(PORTA ,PIN2,PIN_INPUT);
    GPIO_setPinDirection(PORTA, PIN3,PIN_INPUT);
    GPIO_setPinDirection(PORTA ,PIN4,PIN_INPUT);
    
    //Enable pullup resistors of PF4
    GPIO_portPUR(PORTF, 0x10);
    
    //Enable pullup resistors of pushbuttons of pins 2,3,4 of PORTA
    GPIO_portPUR(PORTA, 0x1C);
    
    //Enable pin interrupt as falling edge
    GPIO_InterruptEnable(PORTF, 0x10, FALLING_EDGE);
    
    //Set call back functions for interrupts
    GPIO_setCallBack(PORTF, switchmode);
}

void switchmode (void)
{
  if (counter == STOPWATCH)
  {
    counter = CALCULATOR;                   //Return to mode 0 when pressing the pushbutton during stopwatch mode
  }
  else
  {
    counter++;                             //Increment counter and switch to the next mode
  }
  delay_ms(500);
}



