#include "LCD_Driver.h"
#include "common_macros.h"
#include "tm4c123gh6pm.h"
#include "delay.h"
#define LCD_DATA GPIO_PORTB
#define LCD_CTRL GPIO_PORTB

//*ADJUSTING POSITION OF LCD CURSOR FUNCTION*//
void LCD_Cursor(char x , char y)
{
  if (x==0)
  {  LCD_Cmd(0x80+(y%16));
  return;
  }
  LCD_Cmd(0xC0+(y%16));
}
//*SENDING COMMAND TO LCD FUNCTION*//
void LCD_Cmd(unsigned char command)
{
    LCD_Write_Nibble(command & 0xF0, 0);                      /* Write upper nibble to LCD */
    LCD_Write_Nibble(command << 4, 0);                        /* Write lower nibble to LCD */

    if (command < 4)
        delay_ms(2);                                          /* 2ms delay for commands 1 and 2 */
    else
        delay_us(40);                                         /* 40us delay for other commands */
}

void LCD_Write_Nibble(unsigned char data, unsigned char control)
{

    data &= 0xF0;                                            /* Extract upper nibble for data */
    control &= 0x0F;                                        /* Extract lower nibble for control */
    GPIO_PORTB_DATA_R = data | control;                   /* Set RS and R/W to zero for write operation */
    GPIO_PORTB_DATA_R  = data | control | EN;              /* Provide Pulse to Enable pin to perform wite operation */
    delay_us(0);
    GPIO_PORTB_DATA_R  = data;                            /*Send data */
    GPIO_PORTB_DATA_R  = 0;                             /* stop writing data to LCD */
}

void LCD_Write_Char(unsigned char data)
{
    LCD_Write_Nibble(data & 0xF0, RS);                     /* Write upper nibble to LCD and RS = 1 to write data */
    LCD_Write_Nibble(data << 4, RS);                       /* Write lower nibble to LCD and RS = 1 to write data */
    delay_us(40);
}



/* LCD and GPIOB initialization Function */
void LCD_init(void)
{
 SYSCTL_RCGCGPIO_R |=(1<<1);                                   /* Enable Clock to GPIOB */
 GPIO_PORTB_DIR_R |=0xFF;                                    /* Set GPIOB all pins a digital output pins */
 GPIO_PORTB_DEN_R|=0xFF;                                       /* Declare GPIOB pins as digital pins */

LCD_Cmd(Set5x7FontSize);                                      /* select 5x7 font size and 2 rows of LCD */
LCD_Cmd(Function_set_4bit);                                    /* Select 4-bit Mode of LCD */
LCD_Cmd(moveCursorRight);                                      /* shift cursor right */
LCD_Cmd(clear_display);                                        /* clear whatever is written on display */
LCD_Cmd(cursorBlink);                                          /* Enable Display and cursor blinking */

}
//**LCD PRINT STRING FUNCTION**//

void LCD_printString(const char *str)
{
	uint8 i = 0;
	while(str[i] != '\0')
	{
		LCD_Write_Char(str[i]);                             /* Call LCD data write */
		i++;
	}
}
//**LCD PRINT INTEGER FUNCTION**//

void LCD_printInteger(signed int result)
{
  if(result < 0) 
  {
    result = result * -1;
    LCD_Write_Char('-');
  }
  if(result == 0) 
  {
    LCD_Write_Char(0 + 48);                               //Converting from integer to char
    return;
  }
  uint8 num[10];
  signed int i = 0;
  signed int j;
  while(result != 0)
  {
    num[i] = result%10;
    result = result / 10;
    i++;
    
  }
  for(j = i-1;j >= 0;j--)
  {
        LCD_Write_Char(num[j]+48);
  }
  
}

void LCD_printFloat(float result)
{
  uint8 i = 0;
  unsigned long num = result;
  LCD_printInteger(num);
  LCD_Write_Char('.');
  result -= num;
  if(result < 0)
     {
       LCD_Write_Char('-');
       result *= -1;
     }
  num = result;
  for(i = 0; i < 2; i++)
  {
    result *= 10;
    num = result;
    result -= num;
    LCD_printInteger(num);
  }
}

