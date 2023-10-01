/*
 * LCD_Driver.h
 *
 *  Created on: Dec 19, 2022
 *      Author: Lenovo
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_
#include "std_types.h"


#define RS 0x01 /* PORTB BIT0 mask */
#define EN 0x02 /* PORTB BIT1 mask */
#define HIGH 1
#define LOW 0

/*define useful symbolic names for LCD commands */
#define clear_display     0x01
#define returnHome        0x02
#define moveCursorRight   0x06
#define moveCursorLeft    0x08
#define shiftDisplayRight 0x1C
#define shiftDisplayLeft  0x18
#define cursorBlink       0x0F
#define cursorOff         0x0C
#define cursorOn          0x0E
#define Function_set_4bit 0x28
#define Function_set_8bit 0x38
#define Entry_mode        0x06
#define Function_8_bit    0x32
#define Set5x7FontSize    0x20
#define FirstRow          0x80

/* prototypes of LCD functions */
//void delay_ms(int n); /* mili second delay function */
//void delay_us(int n); /* micro second delay function */
void LCD_init(void);  /* LCD initialization function */
void LCD_Cmd(unsigned char command); /*Used to send commands to LCD */
void LCD_Write_Char(unsigned char data); /* Writes ASCII character */
void LCD_Write_Nibble(unsigned char data, unsigned char control); /* Writes 4-bits */
void LCD_printString(const char *str);	/* Send string to LCD function */
void LCD_printInteger(signed int result); /*Function to print integers*/
void LCD_printFloat(float result); /*Function to print decimal numbers*/
void LCD_Cursor(char x , char y); /*Function to move cursor*/

#endif /* LCD_DRIVER_H_ */
