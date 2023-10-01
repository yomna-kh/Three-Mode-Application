/**********************************************************
*
* Module: GPIO driver
*
* File name: GPIO.h
*
* Description: Header file for Tiva GPIO driver
*
***********************************************************/

#ifndef GPIO_H__
#define GPIO_H__

#include "std_types.h"

/**********************************************************
*                       Definitions                       *
***********************************************************/

#define PORTA   0
#define PORTB   1
#define PORTC   2
#define PORTD   3
#define PORTE   4
#define PORTF   5

#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7

/***********************************************************
*                         Typedefs                         *
************************************************************/
/*
typedef enum
{
  LOGIC_LOW, LOGIC_HIGH
}GPIO_pinValue;*/

typedef enum
{
  PIN_INPUT, PIN_OUTPUT
}GPIO_pinDirection;

typedef enum
{
  FALLING_EDGE, RISING_EDGE, LOW_LEVEL, HIGH_LEVEL
}GPIO_interruptType;

/***********************************************************
*                     Function Prototypes                  *
************************************************************/

/*
*  Description:
*  Function responsible for initializing ports
*/
void GPIO_portINIT(uint8 GPIO_portNum);

/*
* Description:
* Function responsible for setting all port pins direction
*/
void GPIO_setPortDirection(uint8 GPIO_portNum, uint8 GPIO_portDirection);

/*
* Description:
* Function responsible for enabling Pullup resistors for required pins
*/
void GPIO_portPUR(uint8 GPIO_portNum, uint8 GPIO_PUR_Pins);

/*
* Description:
* Function responsible for setting individual pin direction
*/
void GPIO_setPinDirection(uint8 GPIO_portNum, uint8 GPIO_pinNum, uint8 GPIO_pinDirection);

/*
* Description:
* Function responsible for writing value on port
*/
void GPIO_writePort(uint8 GPIO_portNum, uint8 GPIO_portValue);

/*
* Description:
* Function responsible for reading port value
*/
uint8 GPIO_readPort(uint8 GPIO_portNum);

/*
* Description:
* function responsible for writing value on individual pin
*/
void GPIO_writePin(uint8 GPIO_portNum, uint8 GPIO_pinNum, uint8 GPIO_pinValue);

/*
* Description:
* Function responsible for reading pin value
*/
uint8 GPIO_readPin(uint8 GPIO_portNum, uint8 GPIO_pinNum);

/*
* Description:
* Function responsible for enabling interrupt for pins
*/
void GPIO_InterruptEnable(uint8 GPIO_portNum, uint8 GPIO_pinNum, uint8 GPIO_interruptType);

/*
* Description:
* Function responsible for setting callback function for GPIO interrupt handlers
*/
void GPIO_setCallBack(uint8 GPIO_portNum,void(*a_ptr)(void));

#endif /*GPIO_H__*/