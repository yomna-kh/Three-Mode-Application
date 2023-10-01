/**********************************************************
*
* Module: GPIO driver
*
* File name: GPIO.c
*
* Description: Source file for Tiva GPIO driver
*
***********************************************************/

#include "GPIO.h"
#include "common_macros.h"
#include "tm4c123gh6pm.h"
#include "std_types.h"

/***********************************************************
*                     Callback Pointers                    *
************************************************************/
/*initializing the pointer to PORTA to NULL*/
static volatile void(*G_Call_Back_Ptr_PORTA)(void) = NULL_PTR;
/*initializing the pointer to PORTB to NULL*/
static volatile void(*G_Call_Back_Ptr_PORTB)(void) = NULL_PTR;
/*initializing the pointer to PORTC to NULL*/
static volatile void(*G_Call_Back_Ptr_PORTC)(void) = NULL_PTR;
/*initializing the pointer to PORTD to NULL*/
static volatile void(*G_Call_Back_Ptr_PORTD)(void) = NULL_PTR;
/*initializing the pointer to PORTE to NULL*/
static volatile void(*G_Call_Back_Ptr_PORTE)(void) = NULL_PTR;
/*initializing the pointer to PORTF to NULL*/
static volatile void(*G_Call_Back_Ptr_PORTF)(void) = NULL_PTR;


/***********************************************************
*                    Interrupt Functions                   *
************************************************************/
//***INTERRUPT SERVICE ROUTINE OF PORT A***//
void
PORTAIntHandler(void)
{
  if(G_Call_Back_Ptr_PORTA != NULL_PTR)                  //Check if the call back pointer is not pointing out to NULL
  	{
  		(*G_Call_Back_Ptr_PORTA)();               //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}
    GPIO_PORTA_ICR_R |= 0xFF;                             //Clear the interrupt flag in Raw Interrupt Status (RIS) 
}
//***INTERRUPT SERVICE ROUTINE OF PORT B***//
void
PORTBIntHandler(void)
{
  if(G_Call_Back_Ptr_PORTB != NULL_PTR)                    //Check if the call back pointer is not pointing out to NULL
  	{
  		(*G_Call_Back_Ptr_PORTB)();                //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}
    GPIO_PORTB_ICR_R |= 0xFF;                              //Clear the interrupt flag in Raw Interrupt Status (RIS) 
}
//***INTERRUPT SERVICE ROUTINE OF PORT C***//
void
PORTCIntHandler(void)
{
  if(G_Call_Back_Ptr_PORTC != NULL_PTR)                    //Check if the call back pointer is not pointing out to NULL
  	{
  		(*G_Call_Back_Ptr_PORTC)();                //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}
    GPIO_PORTC_ICR_R |= 0xFF;                              //Clear the interrupt flag in Raw Interrupt Status (RIS) 
}
//***INTERRUPT SERVICE ROUTINE OF PORT D***//
void
PORTDIntHandler(void)
{
  if(G_Call_Back_Ptr_PORTD != NULL_PTR)                      //Check if the call back pointer is not pointing out to NULL
  	{
  		(*G_Call_Back_Ptr_PORTD)();                   //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}
  GPIO_PORTD_ICR_R |= 0xFF;                                   //Clear the interrupt flag in Raw Interrupt Status (RIS) 
}
//***INTERRUPT SERVICE ROUTINE OF PORT E***//
void
PORTEIntHandler(void)
{
  if(G_Call_Back_Ptr_PORTE != NULL_PTR)                      //Check if the call back pointer is not pointing out to NULL
  	{
  		(*G_Call_Back_Ptr_PORTE)();                   //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}
    GPIO_PORTE_ICR_R |= 0x3F;                                  //Clear the interrupt flag in Raw Interrupt Status (RIS) 
}
//***INTERRUPT SERVICE ROUTINE OF PORT F***//
void
PORTFIntHandler(void)
{
  if(G_Call_Back_Ptr_PORTF != NULL_PTR)                       //Check if the call back pointer is not pointing out to NULL
  	{
  		(*G_Call_Back_Ptr_PORTF)();                   //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}
    GPIO_PORTF_ICR_R |= 0x1F;                                  //Clear the interrupt flag in Raw Interrupt Status (RIS) after timer has elapsed
}

/***********************************************************
*                         Functions                        *
************************************************************/
//***INITIALIZATION FUNCTION OF GPIO PORTS***//

void GPIO_portINIT(uint8 GPIO_portNum)
{
  SYSCTL_RCGCGPIO_R |= (1<<GPIO_portNum);                     //Enable Clock Gating to port
  while((SYSCTL_PRGPIO_R & (1<<GPIO_portNum)) == 0){};         //Using Peripheral Ready to check the presence of clock pulses
  
  switch(GPIO_portNum)
  {
  case PORTA:
    GPIO_PORTA_LOCK_R = 0x4C4F434B;                           //Unlocking Commit Register
    GPIO_PORTA_CR_R = 0xFF;                                    //Enabling Commit Register
    break;
    
  case PORTB:
    GPIO_PORTB_LOCK_R = 0x4C4F434B;                            //Unlocking Commit Register
    GPIO_PORTB_CR_R = 0xFF;                                    //Enabling Commit Register
    break;
    
  case PORTC:
    GPIO_PORTC_LOCK_R = 0x4C4F434B;                              //Unlocking Commit Register
    GPIO_PORTC_CR_R = 0xFF;                                    //Enabling Commit Register
    break;
    
  case PORTD:
    GPIO_PORTD_LOCK_R = 0x4C4F434B;                               //Unlocking Commit Register
    GPIO_PORTD_CR_R = 0xFF;                                       //Enabling Commit Register
    break;
    
  case PORTE:
    GPIO_PORTE_LOCK_R = 0x4C4F434B;                              //Unlocking Commit Register
    GPIO_PORTE_CR_R = 0x3F;                                        //Enabling Commit Register
    break;
    
  case PORTF:
    GPIO_PORTF_LOCK_R = 0x4C4F434B;                              //Unlocking Commit Register
    GPIO_PORTF_CR_R = 0x1F;                                       //Enabling Commit Register
    break;
  }
}
//***DIGITAL ENABLING OF GPIO PORTS FUNCTION***//

void GPIO_setPortDirection(uint8 GPIO_portNum, uint8 GPIO_portDirection)
{
  switch(GPIO_portNum)
  {
  case PORTA:
    GPIO_PORTA_DIR_R = GPIO_portDirection;                       //Setting the direction of PORT A pins
    GPIO_PORTA_DEN_R = 0xFF;                                      //Digital enabling of PORT A pins
    break;
    
  case PORTB:
    GPIO_PORTB_DIR_R = GPIO_portDirection;                        //Setting the direction of PORT B pins
    GPIO_PORTB_DEN_R = 0xFF;                                       //Digital enabling of PORT B pins
    break;
    
  case PORTC:
    GPIO_PORTC_DIR_R = GPIO_portDirection;                        //Setting the direction of PORT C pins
    GPIO_PORTC_DEN_R = 0xFF;                                       //Digital enabling of PORT C pins
    break;
    
  case PORTD:
    GPIO_PORTD_DIR_R = GPIO_portDirection;                        //Setting the direction of PORT D pins       
    GPIO_PORTD_DEN_R = 0xFF;                                      //Digital enabling of PORT D pins
    break;
    
  case PORTE:
    GPIO_PORTE_DIR_R = GPIO_portDirection;                         //Setting the direction of PORT E pins
    GPIO_PORTE_DEN_R = 0x3F;                                        //Digital enabling of PORT E pins
    break;
    
  case PORTF:
    GPIO_PORTF_DIR_R = GPIO_portDirection;                          //Setting the direction of PORT F pins 
    GPIO_PORTF_DEN_R = 0x1F;                                         //Digital enabling of PORT F pin
    break;
  }
}
//***PULLUP RESISTOR ENABLING FOR GPIO PORTS FUNCTION***//

void GPIO_portPUR(uint8 GPIO_portNum, uint8 GPIO_PUR_Pins)
{
  switch(GPIO_portNum)
  {
  case PORTA:
    GPIO_PORTA_PUR_R = GPIO_PUR_Pins;                                 //Enabling Pull up resistor to PORT A pins
    break;
    
  case PORTB:
    GPIO_PORTB_PUR_R = GPIO_PUR_Pins;                                  //Enabling Pull up resistor to PORT B pins
    break;
    
  case PORTC:
    GPIO_PORTC_PUR_R = GPIO_PUR_Pins;                                  //Enabling Pull up resistor to PORT C pins
    break;
    
  case PORTD:
    GPIO_PORTD_PUR_R = GPIO_PUR_Pins;                                  //Enabling Pull up resistor to PORT D pins
    break;
    
  case PORTE:
    GPIO_PORTE_PUR_R = GPIO_PUR_Pins;                                   //Enabling Pull up resistor to PORT E pins
    break;
    
  case PORTF:
    GPIO_PORTF_PUR_R = GPIO_PUR_Pins;                                   //Enabling Pull up resistor to PORT F pins
    break;
  }
}
//***BITWISE OPERATIONS FOR PINS FUNCTION***//

void GPIO_setPinDirection(uint8 GPIO_portNum, uint8 GPIO_pinNum, uint8 GPIO_pinDirection)
{
  switch(GPIO_portNum)
  {
  case PORTA:
    if(GPIO_pinDirection == PIN_INPUT)
    {
      CLEAR_BIT(GPIO_PORTA_DIR_R, GPIO_pinNum);
    }
    else
    {
      SET_BIT(GPIO_PORTA_DIR_R, GPIO_pinNum);
    }
    SET_BIT(GPIO_PORTA_DEN_R, GPIO_pinNum);
    break;
    
  case PORTB:
    if(GPIO_pinDirection == PIN_INPUT)
    {
      CLEAR_BIT(GPIO_PORTB_DIR_R, GPIO_pinNum);
    }
    else
    {
      SET_BIT(GPIO_PORTB_DIR_R, GPIO_pinNum);
    }
    SET_BIT(GPIO_PORTB_DEN_R, GPIO_pinNum);
    break;
    
  case PORTC:
    if(GPIO_pinDirection == PIN_INPUT)
    {
      CLEAR_BIT(GPIO_PORTC_DIR_R, GPIO_pinNum);
    }
    else
    {
      SET_BIT(GPIO_PORTC_DIR_R, GPIO_pinNum);
    }
    SET_BIT(GPIO_PORTC_DEN_R, GPIO_pinNum);
    break;
    
  case PORTD:
    if(GPIO_pinDirection == PIN_INPUT)
    {
      CLEAR_BIT(GPIO_PORTD_DIR_R, GPIO_pinNum);
    }
    else
    {
      SET_BIT(GPIO_PORTD_DIR_R, GPIO_pinNum);
    }
    SET_BIT(GPIO_PORTD_DEN_R, GPIO_pinNum);
    break;
    
  case PORTE:
    if(GPIO_pinDirection == PIN_INPUT)
    {
      CLEAR_BIT(GPIO_PORTE_DIR_R, GPIO_pinNum);
    }
    else
    {
      SET_BIT(GPIO_PORTE_DIR_R, GPIO_pinNum);
    }
    SET_BIT(GPIO_PORTE_DEN_R, GPIO_pinNum);
    break;
    
  case PORTF:
    if(GPIO_pinDirection == PIN_INPUT)
    {
      CLEAR_BIT(GPIO_PORTF_DIR_R, GPIO_pinNum);
    }
    else
    {
      SET_BIT(GPIO_PORTF_DIR_R, GPIO_pinNum);
    }
    SET_BIT(GPIO_PORTF_DEN_R, GPIO_pinNum);
    break;
  }
}
//***WRITING TO GPIO PORTS FUNCTION***//

void GPIO_writePort(uint8 GPIO_portNum, uint8 GPIO_portValue)
{
  switch(GPIO_portNum)
  {
  case PORTA:
    GPIO_PORTA_DATA_R = GPIO_portValue;
    break;
    
  case PORTB:
    GPIO_PORTB_DATA_R = GPIO_portValue;
    break;
    
  case PORTC:
    GPIO_PORTC_DATA_R = GPIO_portValue;
    break;
    
  case PORTD:
    GPIO_PORTD_DATA_R = GPIO_portValue;
    break;
    
  case PORTE:
    GPIO_PORTE_DATA_R = GPIO_portValue;
    break;
    
  case PORTF:
    GPIO_PORTF_DATA_R = GPIO_portValue;
    break;
  }
}
//***READING FROM GPIO PORTS FUNCTION***//

uint8 GPIO_readPort(uint8 GPIO_portNum)
{
  switch(GPIO_portNum)
  {
  case PORTA:
    return GPIO_PORTA_DATA_R;
    
  case PORTB:
    return GPIO_PORTB_DATA_R;
    
  case PORTC:
    return GPIO_PORTC_DATA_R;
    
  case PORTD:
    return GPIO_PORTD_DATA_R;
    
  case PORTE:
    return GPIO_PORTE_DATA_R;
    
  case PORTF:
    return GPIO_PORTF_DATA_R;
    
  default:
    return -1;
    
  }
}
//***WRITING TO GPIO PORTS PINS***//

void GPIO_writePin(uint8 GPIO_portNum, uint8 GPIO_pinNum, uint8 GPIO_pinValue)
{
  switch(GPIO_portNum)
  {
  case PORTA:
    if(GPIO_pinValue == LOGIC_HIGH)
    {
      SET_BIT(GPIO_PORTA_DATA_R, GPIO_pinNum);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTA_DATA_R, GPIO_pinNum);
    }
    break;
    
  case PORTB:
    if(GPIO_pinValue == LOGIC_HIGH)
    {
      SET_BIT(GPIO_PORTB_DATA_R, GPIO_pinNum);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTB_DATA_R, GPIO_pinNum);
    }
    break;
    
  case PORTC:
    if(GPIO_pinValue == LOGIC_HIGH)
    {
      SET_BIT(GPIO_PORTC_DATA_R, GPIO_pinNum);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTC_DATA_R, GPIO_pinNum);
    }
    break;
    
  case PORTD:
    if(GPIO_pinValue == LOGIC_HIGH)
    {
      SET_BIT(GPIO_PORTD_DATA_R, GPIO_pinNum);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTD_DATA_R, GPIO_pinNum);
    }
    break;
    
  case PORTE:
    if(GPIO_pinValue == LOGIC_HIGH)
    {
      SET_BIT(GPIO_PORTE_DATA_R, GPIO_pinNum);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTE_DATA_R, GPIO_pinNum);
    }
    break;
    
  case PORTF:
    if(GPIO_pinValue == LOGIC_HIGH)
    {
      SET_BIT(GPIO_PORTF_DATA_R, GPIO_pinNum);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTF_DATA_R, GPIO_pinNum);
    }
    break;
  }
}
//***READING FROM GPIO PORTS PINS***//
uint8 GPIO_readPin(uint8 GPIO_portNum, uint8 GPIO_pinNum)
{
  switch(GPIO_portNum)
  {
  case PORTA:
    return GET_BIT(GPIO_PORTA_DATA_R, GPIO_pinNum);
    
  case PORTB:
    return GET_BIT(GPIO_PORTB_DATA_R, GPIO_pinNum);
    
  case PORTC:
    return GET_BIT(GPIO_PORTC_DATA_R, GPIO_pinNum);
    
  case PORTD:
    return GET_BIT(GPIO_PORTD_DATA_R, GPIO_pinNum);
    
  case PORTE:
    return GET_BIT(GPIO_PORTE_DATA_R, GPIO_pinNum);
    
  case PORTF:
    return GET_BIT(GPIO_PORTF_DATA_R, GPIO_pinNum);
    
  default:
    return -1;
  }
}
//***GPIO PORTS INTERRUPT ENABLING FUNCTIONS***//

void GPIO_InterruptEnable(uint8 GPIO_portNum, uint8 GPIO_interruptPins, uint8 GPIO_interruptType)
{
  switch(GPIO_portNum)
  {
  case PORTA:
    SET_BIT(NVIC_EN0_R, 0);                             //Enabling interrupt for Port A by NVIC
    switch(GPIO_interruptType)
    {
    case FALLING_EDGE:
      GPIO_PORTA_IS_R &= ~(GPIO_interruptPins);         //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTA_IEV_R &= ~(GPIO_interruptPins);        //Adjusting interrupt even value to be negative edge triggered
      break;
      
    case RISING_EDGE:
      GPIO_PORTA_IS_R &= ~(GPIO_interruptPins);        //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTA_IEV_R |= GPIO_interruptPins;          //Adjusting interrupt even value to be positive edge triggered
      break;
      
    case LOW_LEVEL:
      GPIO_PORTA_IS_R |= GPIO_interruptPins;           //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTA_IEV_R &= ~(GPIO_interruptPins);       //Adjusting interrupt even value to be negative level triggered
      break;
      
    case HIGH_LEVEL:
      GPIO_PORTA_IS_R |= GPIO_interruptPins;           //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTA_IEV_R |= GPIO_interruptPins;          //Adjusting interrupt even value to be positive level triggered
      break;
    }
    GPIO_PORTA_ICR_R |= GPIO_interruptPins;            //Clearing Interrupt Flag from Raw interrupt status
    GPIO_PORTA_IM_R |= GPIO_interruptPins;             //Enabling interrupts at pins through interrupt mask
    break;
    
  case PORTB:
    SET_BIT(NVIC_EN0_R, 1);                            //Enabling interrupt for Port B by NVIC
    switch(GPIO_interruptType)
    {
    case FALLING_EDGE:
      GPIO_PORTB_IS_R &= ~(GPIO_interruptPins);        //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTB_IEV_R &= ~(GPIO_interruptPins);        //Adjusting interrupt even value to be negative edge triggered
      break;
      
    case RISING_EDGE:
      GPIO_PORTB_IS_R &= ~(GPIO_interruptPins);        //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTB_IEV_R |= GPIO_interruptPins;          //Adjusting interrupt even value to be positive edge triggered
      break;
      
    case LOW_LEVEL:
      GPIO_PORTB_IS_R |= GPIO_interruptPins;            //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTB_IEV_R &= ~(GPIO_interruptPins);        //Adjusting interrupt even value to be negative level triggered
      break;
      
    case HIGH_LEVEL:
      GPIO_PORTB_IS_R |= GPIO_interruptPins;           //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTF_IEV_R |= GPIO_interruptPins;          //Adjusting interrupt even value to be positive level triggered
      break;
    }
    GPIO_PORTB_ICR_R |= GPIO_interruptPins;             //Clearing Interrupt Flag from Raw interrupt status
    GPIO_PORTB_IM_R |= GPIO_interruptPins;              //Enabling interrupts at pins through interrupt mask
    break;
    
  case PORTC:
    SET_BIT(NVIC_EN0_R, 2);                            //Enabling interrupt for Port C by NVIC
    switch(GPIO_interruptType)
    {
    case FALLING_EDGE:
      GPIO_PORTC_IS_R &= ~(GPIO_interruptPins);          //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTC_IEV_R &= ~(GPIO_interruptPins);         //Adjusting interrupt even value to be negative edge triggered
      break;
      
    case RISING_EDGE:
      GPIO_PORTC_IS_R &= ~(GPIO_interruptPins);          //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTC_IEV_R |= GPIO_interruptPins;            //Adjusting interrupt even value to be positive edge triggered
      break;
      
    case LOW_LEVEL:
      GPIO_PORTC_IS_R |= GPIO_interruptPins;             //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTC_IEV_R &= ~(GPIO_interruptPins);          //Adjusting interrupt even value to be negative level triggered
      break;
      
    case HIGH_LEVEL:
      GPIO_PORTC_IS_R |= GPIO_interruptPins;             //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTC_IEV_R |= GPIO_interruptPins;             //Adjusting interrupt even value to be positive level triggered
      break; 
    }
    GPIO_PORTC_ICR_R |= GPIO_interruptPins;              //Clearing Interrupt Flag from Raw interrupt status
    GPIO_PORTC_IM_R |= GPIO_interruptPins;               //Enabling interrupts at pins through interrupt mask      
    break;
    
  case PORTD:
    SET_BIT(NVIC_EN0_R, 3);                               //Enabling interrupt for Port D by NVIC
    switch(GPIO_interruptType)
    {
    case FALLING_EDGE:
      GPIO_PORTD_IS_R &= ~(GPIO_interruptPins);           //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTD_IEV_R &= ~(GPIO_interruptPins);          //Adjusting interrupt even value to be negative edge triggered
      break;
      
    case RISING_EDGE:
      GPIO_PORTD_IS_R &= ~(GPIO_interruptPins);           //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTD_IEV_R |= GPIO_interruptPins;             //Adjusting interrupt even value to be positive edge triggered
      break;
      
    case LOW_LEVEL:
      GPIO_PORTD_IS_R |= GPIO_interruptPins;              //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTD_IEV_R &= ~(GPIO_interruptPins);           //Adjusting interrupt even value to be negative level triggered
      break;
      
    case HIGH_LEVEL:
      GPIO_PORTD_IS_R |= GPIO_interruptPins;             //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTD_IEV_R |= GPIO_interruptPins;             //Adjusting interrupt even value to be positive level triggered
      break;
    }
    GPIO_PORTD_ICR_R |= GPIO_interruptPins;               //Clearing Interrupt Flag from Raw interrupt status
    GPIO_PORTD_IM_R |= GPIO_interruptPins;                //Enabling interrupts at pins through interrupt mask 
    break;
    
  case PORTE:
    SET_BIT(NVIC_EN0_R, 4);                               //Enabling interrupt for Port E by NVIC
    switch(GPIO_interruptType)
    {
    case FALLING_EDGE:
      GPIO_PORTE_IS_R &= ~(GPIO_interruptPins);             //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTE_IEV_R &= ~(GPIO_interruptPins);            //Adjusting interrupt even value to be negative edge triggered
      break;
      
    case RISING_EDGE:
      GPIO_PORTE_IS_R &= ~(GPIO_interruptPins);             //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTE_IEV_R |= GPIO_interruptPins;                //Adjusting interrupt even value to be positive edge triggered
      break;
      
    case LOW_LEVEL:
      GPIO_PORTE_IS_R |= GPIO_interruptPins;                //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTE_IEV_R &= ~(GPIO_interruptPins);              //Adjusting interrupt even value to be negative level triggered
      break;
      
    case HIGH_LEVEL:
      GPIO_PORTE_IS_R |= GPIO_interruptPins;                //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTE_IEV_R |= GPIO_interruptPins;                //Adjusting interrupt even value to be positive level triggered
      break;
    }
    GPIO_PORTE_ICR_R |= GPIO_interruptPins;                  //Clearing Interrupt Flag from Raw interrupt status
    GPIO_PORTE_IM_R |= GPIO_interruptPins;                   //Enabling interrupts at pins through interrupt mask 
    break;
    
  case PORTF:
    GPIO_PORTF_IBE_R &= ~(GPIO_interruptPins);                //Enabling interrupts to be fully controlled and triggered by IEV
    SET_BIT(NVIC_EN0_R, 30);                                  //Enabling interrupt for Port E by NVIC
    switch(GPIO_interruptType)
    {
    case FALLING_EDGE:
      GPIO_PORTF_IS_R &= ~(GPIO_interruptPins);               //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTF_IEV_R &= ~(GPIO_interruptPins);              //Adjusting interrupt even value to be negative edge triggered
      break;
      
    case RISING_EDGE:
      GPIO_PORTF_IS_R &= ~(GPIO_interruptPins);                //Adjusting Interrupt Sense to be edge triggered
      GPIO_PORTF_IEV_R |= GPIO_interruptPins;                  //Adjusting interrupt even value to be negative level triggered
      break;
      
    case LOW_LEVEL:
      GPIO_PORTF_IS_R |= GPIO_interruptPins;                   //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTF_IEV_R &= ~(GPIO_interruptPins);               //Adjusting interrupt even value to be negative level triggered
      break;
      
    case HIGH_LEVEL:
      GPIO_PORTF_IS_R |= GPIO_interruptPins;                  //Adjusting Interrupt Sense to be level triggered
      GPIO_PORTF_IEV_R |= GPIO_interruptPins;                  //Adjusting interrupt even value to be positive level triggered
      break;
    }
    GPIO_PORTF_ICR_R |= GPIO_interruptPins;                   //Clearing Interrupt Flag from Raw interrupt status
    GPIO_PORTF_IM_R |= GPIO_interruptPins;                     //Enabling interrupts at pins through interrupt mask 
  }
}
//****GPIO SET CALL BACK FUNCTION TO SET EACH POINTER TO POINT OUT TO ITS SPECIFIED CALL BACK FUNCTION****//

void GPIO_setCallBack(uint8 GPIO_portNum,void(*Callback_Ptr)(void))
{
  switch(GPIO_portNum)
  {
  case PORTA:
    G_Call_Back_Ptr_PORTA = Callback_Ptr;                     //Setting ptr to point out to call back function of PORT A
    break;
    
  case PORTB:
    G_Call_Back_Ptr_PORTB = Callback_Ptr;                     //Setting ptr to point out to call back function of PORT B
    break;
    
  case PORTC:
    G_Call_Back_Ptr_PORTC = Callback_Ptr;                     //Setting ptr to point out to call back function of PORT C
    break;
    
  case PORTD:
    G_Call_Back_Ptr_PORTD = Callback_Ptr;                     //Setting ptr to point out to call back function of PORT D
    break;
    
  case PORTE:
    G_Call_Back_Ptr_PORTE = Callback_Ptr;                      //Setting ptr to point out to call back function of PORT E
    break;
    
  case PORTF:
    G_Call_Back_Ptr_PORTF = Callback_Ptr;                      //Setting ptr to point out to call back function of PORT F
    break;

  }
}
