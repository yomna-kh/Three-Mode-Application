#include "calculator.h"
#include "LCD_Driver.h"

//**********ENUMERATION OF THE THREE PROJECT MODES*********//

typedef enum
{
  CALCULATOR, TIMER, STOPWATCH
}Project_Mode;

extern Project_Mode current;                         //Extending the visibility of "current" across all source files
extern Project_Mode counter;                         ////Extending the visibility of "counter" across all source files


int index = 0;
int arr2[10]  = {0};                                  
int arr[10]  = {0};

float result   = 0;
int num1 = 0;
int num2 = 0;
char op  = '0';
char addition  = '0';
char subtract  = '0';
char multiply  = '0';
char division  = '0';
volatile unsigned char key;
volatile int intkey;

//**********CALCULATOR INITIALIZATION FUNCTION***********//

void Calc_init (void)
{
 LCD_Cmd(cursorOn);                                        //Displaying Cursor on LCD
  delay_ms(250);
 LCD_Cmd(clear_display);                                   //Clearing all contents on LCD
  delay_ms(250);
 LCD_Cmd(FirstRow);                                       //Enabling Content Display on first row of LCD
 LCD_Cmd(cursorOn);                                       //Displaying Cursor on LCD
 LCD_Cmd(cursorBlink);                                    //Blinking Cursor on LCD to start typing
}

//*********CALCULATOR MODE FUNCTION**********//

void Calculate(void)
{ 
  LCD_Cmd(clear_display);                                 //Clearing all contents on LCD
  current = CALCULATOR;                                    //Current value is given index no.0 of Calculator mode
  LCD_Cmd(cursorOff);                                      //Setting OFF the cursor of the LCD
  LCD_printString("  CALCULATOR");
  delay_ms(2000);
  LCD_Cmd(clear_display);                                   //Clearing all contents on LCD
  LCD_Cmd(cursorBlink);                                      //Blinking Cursor on LCD to start typing

  while(1)
  { 
    if ( counter != current){return;}                        //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
 
    key = KeyPad_Read();                                      
    delay_ms(500);
         if ( counter != current){return;}                   //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
    if(key == '#')
    {
      clear_data();                                          //Clearing all data entered by user and enable typing new data
      LCD_Cmd(clear_display);                                //Clearing all contents on LCD
      continue;
    }
        if ( counter != current){return;}                    //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
    LCD_Write_Char(key);                                     //Display the character entered by user
    if(addition == '1')                                     
    {
      if(key == '=')
      {
        num2 = numfinalize(arr);                              //Multiplying by 10^n to create a number from input digits
        add(num1,num2);
        clear_data();                                        //Resetting all operation registers
      }
      //didn't write an operator yet
      else 
      {
        intkey = key - 48;                                  //Converting the input character into an integer number 
        store(intkey, arr);                                  //Storing the input integer into an array to be used in operation later
      }
    }
    else if (subtract == '1')
    {
      if(key=='=')
      {
        num2 = numfinalize(arr);
        sub(num1, num2);
        clear_data();                                         //Resetting all operation registers
      }
      else
      {
        intkey = key - 48;                                  //Converting the input character into an integer number 
        store(intkey, arr);                                 //Storing the input integer into an array to be used in operation later
      } 
    }
    else if (multiply == '1')
    {
      if(key == '=')
      {
        num2 = numfinalize(arr);                              //Multiplying by 10^n to create a number from input digits
        mult(num1,num2);
        clear_data();                                         //Resetting all operation registers

      }
       if ( counter != CALCULATOR){break;}
      else
      {
        intkey = key - 48;                                  //Converting the input character into an integer number 
        store(intkey, arr);                                 //Storing the input integer into an array to be used in operation later
      }
    }
    else if (division == '1')
    {
      if(key=='=')
      {
        num2 = numfinalize(arr);                              //Multiplying by 10^n to create a number from input digits
        if (num2 == 0)
        {
          LCD_printString("  Error");
        }
        else
        {
            divide(num1,num2);
        }
        clear_data();                                        //Resetting all operation registers
      }
      else
      {
        intkey = key - 48;                                   //Converting the input character into an integer number 
        store(intkey, arr);                                    //Storing the input integer into an array to be used in operation later
      }
    }
    else 
    {
      switch (key)
      {
    case '+':
          addition = '1';
          num1 = numfinalize(arr);                             //Multiplying by 10^n to create a number from input digits
          break;
    case '-':
          subtract = '1';
          num1 = numfinalize(arr);                              //Multiplying by 10^n to create a number from input digits
          break;
    case '*':
          multiply = '1';
          num1 = numfinalize(arr);                               //Multiplying by 10^n to create a number from input digits
          break;
    case '/':
          division = '1';
          num1 = numfinalize(arr);                                //Multiplying by 10^n to create a number from input digits
          break;
                                                            //Immediately goes to default to write digits of num1
    default:
        intkey = key - 48;                                  //Converting the input character into an integer number 
        store(intkey, arr);                                 //Storing the input integer into an array to be used in operation later
         if ( counter != CALCULATOR){break;}                //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
      }
       if ( counter != CALCULATOR){break;}                  //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
  }
   if ( counter != CALCULATOR){break;}                      //checking if any interrupt occured that will exit the current ISR and accordingly switch to the next program modes
  }
  
}

//*********CALCULATOR TERMINATION FUNCTION**********//

void end_calc(float result)
{
  
  LCD_Cursor(1,0);                                         //Setting cursor to the first screen row 
  if(result == (int)result)
  {
    LCD_printInteger((int)result);                         //Displaying the final result on LCD
  }
  else
  {
    LCD_printFloat(result);
  }
}


void add(int num1, int num2)                             //Addition function
{
  result = num1 + num2;
  end_calc(result);
}


void sub(int num1, int num2)                             //Subtraction function
{
  result = num1 - num2;
  end_calc(result);
}


void mult(int num1, int num2)                            //multiplication function
{
  result = num1 * num2;
  end_calc(result);
}

void divide(int num1, int num2)                          //Division function
{
  if(num2 == 0)
  {
   LCD_Cmd(cursorOff);
  }
  
  else if(num1 == 0)
  {
   LCD_Write_Char('0');
      LCD_Cmd(cursorOff);
  }
  
  else
  {
    result = (float)num1 / num2;
    end_calc(result);
  }
}

//*********CLEAR DATA ON LCD FUNCTION**********//

void clear_data()                                           //function used to reset all previously used registers
{
  uint8 i;
  for(i = 0; i<10; i++)
  {
    arr[i] = 0;
  }
  num1 = 0;
  num2 = 0;
  result    = 0;
  intkey  = 0;
  addition  = '0';
  subtract  = '0';
  multiply  = '0';
  division  = '0';
  
}

//*********DIGIT STORING FUNCTION**********//

void store(volatile int no, int* arr2)                  //Function that stores digits one by one respectively in an array with index increment after storing
{
  *(arr2 + index) = no;
  index++;
}

//*********CREATING NUMBER FUNCTION**********//

int numfinalize(int* arr2) 
{
  const int factor[6] = {1 , 10, 100, 1000, 10000, 100000};
  int numreturn = 0;
  for(int j = 0; j < 6; j++)
  {
    numreturn += ((arr2[j]) * factor[index-1]);           //Creating a number from input digits by user through 10^n multiplication in an array
    index--;
    if(index == 0) 
      break;
  }
  for(int k = 0; k < 6; k++)
    arr2[k] = 0;
  index = 0;
  return numreturn;
}
