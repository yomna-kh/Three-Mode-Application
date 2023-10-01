#include "std_types.h"
#include "macros.h"
#include "timer.h"

/*initializing the pointer 0 to NULL*/
static volatile void(*G_Call_Back_ptr_0)(void) = NULL_PTR;

/*initializing the pointer 1 to NULL*/
static volatile void(*G_Call_Back_ptr_1)(void) = NULL_PTR;

/*initializing the pointer 2 to NULL*/
static volatile void(*G_Call_Back_ptr_2)(void) = NULL_PTR;

/*initializing the pointer 3 to NULL*/
static volatile void(*G_Call_Back_ptr_3)(void) = NULL_PTR;

/*initializing the pointer 4 to NULL*/
static volatile void(*G_Call_Back_ptr_4)(void) = NULL_PTR;

/*initializing the pointer 5 to NULL*/
static volatile void(*G_Call_Back_ptr_5)(void) = NULL_PTR;

/*INTERRUPT SERVICE ROUTINE OF TIMER 0*/
void
Timer0AIntHandler(void)
{
	
  {
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;                  //Clear the interrupt flag in Raw Interrupt Status (RIS) after timer has elapsed
  }
  if(G_Call_Back_ptr_0 != NULL_PTR)                      //Check if the call back pointer is not pointing out to NULL 
  	{
  		(*G_Call_Back_ptr_0)();                  //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}

}

/*INTERRUPT SERVICE ROUTINE OF TIMER 1*/
void
Timer1AIntHandler(void)
{
  {
    TIMER1_ICR_R = TIMER_ICR_TATOCINT;                 //Clear the interrupt flag in Raw Interrupt Status (RIS) after timer has elapsed
  }
  if(G_Call_Back_ptr_1 != NULL_PTR)                     //Check if the call back pointer is not pointing out to NULL 
  	{
  		(*G_Call_Back_ptr_1)();                 //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}

}

/*INTERRUPT SERVICE ROUTINE OF TIMER 2*/
void
Timer2AIntHandler(void)
{
  {
    TIMER2_ICR_R = TIMER_ICR_TATOCINT;                       //Clear the interrupt flag in Raw Interrupt Status (RIS) after timer has elapsed
  }
  if(G_Call_Back_ptr_2 != NULL_PTR)                          //Check if the call back pointer is not pointing out to NULL 
  	{
  		(*G_Call_Back_ptr_2)();                    //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}

}
/*INTERRUPT SERVICE ROUTINE OF TIMER 3*/
void
Timer3AIntHandler(void)
{
  {
    TIMER3_ICR_R = TIMER_ICR_TATOCINT;                        //Clear the interrupt flag in Raw Interrupt Status (RIS) after timer has elapsed
  }
  if(G_Call_Back_ptr_3 != NULL_PTR)                            //Check if the call back pointer is not pointing out to NULL 
  	{
  		(*G_Call_Back_ptr_3)();                     //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}

}

/*INTERRUPT SERVICE ROUTINE OF TIMER 4*/
void
Timer4AIntHandler(void)
{
  {
    TIMER4_ICR_R = TIMER_ICR_TATOCINT;                           //Clear the interrupt flag in Raw Interrupt Status (RIS) after timer has elapsed
  }
  if(G_Call_Back_ptr_4 != NULL_PTR)                              //Check if the call back pointer is not pointing out to NULL 
  	{
  		(*G_Call_Back_ptr_4)();                         //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}

}

/*INTERRUPT SERVICE ROUTINE OF TIMER 5*/
void
Timer5AIntHandler(void)
{
  {
    TIMER5_ICR_R = TIMER_ICR_TATOCINT;                          //Clear the interrupt flag in Raw Interrupt Status (RIS) after timer has elapsed
  }
  if(G_Call_Back_ptr_5 != NULL_PTR)                             //Check if the call back pointer is not pointing out to NULL 
  	{
  		(*G_Call_Back_ptr_0)();                        //Utilizing ptr to point out to the function that will be executed later through the ISR
  	}

}

//******TIMER INITIALIZATION FUNCTION******//

void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	switch (Config_Ptr->timer){
	case TIMER_0:
		SYSCTL_RCGCTIMER_R |= (1<<TIMER_0);            //Enabling clock gating to timer 0 at bit 0
		TIMER0_CTL_R = 0;                               //Disabling timer before initialization
		TIMER0_CFG_R = 0x04;                            //Configuring timer to its half scale
		TIMER0_TAMR_R = Config_Ptr->mode;               //Configuring timer A as periodic and down counter timer 
		TIMER0_TAPR_R = Config_Ptr->prescaler;           //Configuring the prescaler value
		TIMER0_IMR_R |= (1<<0);                         //Enabling Interrupt mask to timer 0 at bit 0
		TIMER0_TAILR_R = Config_Ptr->load_value;        //Adjusting the Interrupt load register by a reload value
		TIMER0_ICR_R = 0X1;                              //Clearing the flag of Raw Interrupt Status by Interrupt Clear
		NVIC_EN0_R = (1<<19);                            //Enabling Interrupts by NVIC at interrupt entry number = 19 in IVT
		break;
	case TIMER_1:
		SYSCTL_RCGCTIMER_R |= (1<<TIMER_1);             //Enabling clock gating to timer 1 at bit 1
		TIMER1_CTL_R = 0;                                //Disabling timer before initialization
		TIMER1_CFG_R = 0x04;                             //Configuring timer to its half scale
		TIMER1_TAMR_R = Config_Ptr->mode;                 //Configuring timer A as periodic and down counter timer 
		TIMER1_TAPR_R = Config_Ptr->prescaler;            //Configuring the prescaler value
		TIMER1_IMR_R |= (1<<0);                           //Enabling Interrupt mask to timer 1 at bit 1       
		TIMER1_TAILR_R = Config_Ptr->load_value;          //Adjusting the Interrupt load register by a reload value 
		TIMER1_ICR_R = 0X1;                               //Clearing the flag of Raw Interrupt Status by Interrupt Clear
		NVIC_EN0_R = (1<<21);                             //Enabling Interrupts by NVIC at interrupt entry number = 21 in IVT
		break;
	case TIMER_2:
		SYSCTL_RCGCTIMER_R |= (1<<TIMER_2);               //Enabling clock gating to timer 2 at bit 2
		TIMER2_CTL_R = 0;                                  //Disabling timer before initialization
		TIMER2_CFG_R = 0x04;                               //Configuring timer to its half scale                  
		TIMER2_TAMR_R = Config_Ptr->mode;                  //Configuring timer A as periodic and down counter timer 
		TIMER2_TAPR_R = Config_Ptr->prescaler;             //Configuring the prescaler value
		TIMER2_IMR_R |= (1<<0);                             //Enabling Interrupt mask to timer 2 at bit 2  
		TIMER2_TAILR_R = Config_Ptr->load_value;            //Adjusting the Interrupt load register by a reload value 
		TIMER2_ICR_R = 0X1;                                  //Clearing the flag of Raw Interrupt Status by Interrupt Clear
		NVIC_EN0_R = (1<<23);                                //Enabling Interrupts by NVIC at interrupt entry number = 23 in IVT
		break;
	case TIMER_3:
		SYSCTL_RCGCTIMER_R |= (1<<TIMER_3);                //Enabling clock gating to timer 3 at bit 3
		TIMER3_CTL_R = 0;                                    //Disabling timer before initialization
		TIMER3_CFG_R = 0x04;                                //Configuring timer to its half scale 
		TIMER3_TAMR_R = Config_Ptr->mode;                   //Configuring timer A as periodic and down counter timer 
		TIMER3_TAPR_R = Config_Ptr->prescaler;               //Configuring the prescaler value
		TIMER3_IMR_R |= (1<<0);                              //Enabling Interrupt mask to timer 3 at bit 3  
		TIMER3_TAILR_R = Config_Ptr->load_value;              //Adjusting the Interrupt load register by a reload value 
		TIMER3_ICR_R = 0X1;                                  //Clearing the flag of Raw Interrupt Status by Interrupt Clear
		NVIC_EN1_R = (1<<5);                                  //Enabling Interrupts by NVIC at interrupt entry number = 5 in IVT
		break;
	case TIMER_4:
		SYSCTL_RCGCTIMER_R |= (1<<TIMER_4);                  //Enabling clock gating to timer 4 at bit 4
		TIMER4_CTL_R = 0;                                     //Disabling timer before initialization
		TIMER4_CFG_R = 0x04;                                  //Configuring timer to its half scale 
		TIMER4_TAMR_R = Config_Ptr->mode;                     //Configuring timer A as periodic and down counter timer 
		TIMER4_TAPR_R = Config_Ptr->prescaler;                //Configuring the prescaler value
		TIMER4_IMR_R |= (1<<0);                               //Enabling Interrupt mask to timer 4 at bit 4
		TIMER4_TAILR_R = Config_Ptr->load_value;              //Adjusting the Interrupt load register by a reload value 
		TIMER4_ICR_R = 0X1;                                    //Clearing the flag of Raw Interrupt Status by Interrupt Clear                 
		NVIC_EN2_R = (1<<6);                                    //Enabling Interrupts by NVIC at interrupt entry number = 6 in IVT
		break;
	case TIMER_5:
		SYSCTL_RCGCTIMER_R |= (1<<TIMER_5);                   //Enabling clock gating to timer 5 at bit 5
		TIMER5_CTL_R = 0;                                     //Disabling timer before initialization
		TIMER5_CFG_R = 0x04;                                   //Configuring timer to its half scale 
		TIMER5_TAMR_R = Config_Ptr->mode;                      //Configuring timer A as periodic and down counter timer 
		TIMER5_TAPR_R = Config_Ptr->prescaler;                  //Configuring the prescaler value
		TIMER5_IMR_R |= (1<<0);                                 //Enabling Interrupt mask to timer 5 at bit 5
		TIMER5_TAILR_R = Config_Ptr->load_value;                //Adjusting the Interrupt load register by a reload value
		TIMER5_ICR_R = 0X1;                                    //Clearing the flag of Raw Interrupt Status by Interrupt Clear    
		NVIC_EN2_R = (1<<28);                                   //Enabling Interrupts by NVIC at interrupt entry number = 28 in IVT
		break;
	}
}

//****TIMER SET CALL BACK FUNCTION TO SET EACH POINTER TO POINT OUT TO ITS SPECIFIED CALL BACK FUNCTION****//

void Timer_setCallBack(uint8 TIMER_NUMBER,void(*a_ptr)(void))
{
	switch (TIMER_NUMBER)
	{
	case 0:
		G_Call_Back_ptr_0 = a_ptr;                //Setting ptr to point out to call back function of timer 0
		break;
	case 1:
		G_Call_Back_ptr_1 = a_ptr;                 //Setting ptr to point out to call back function of timer 1
		break;
	case 2:
		G_Call_Back_ptr_2 = a_ptr;                 //Setting ptr to point out to call back function of timer 2
		break;
	case 3:
		G_Call_Back_ptr_3 = a_ptr;                  //Setting ptr to point out to call back function of timer 3
		break;
	case 4:
		G_Call_Back_ptr_4 = a_ptr;                  //Setting ptr to point out to call back function of timer 4
		break;
	case 5:
		G_Call_Back_ptr_5 = a_ptr;                   //Setting ptr to point out to call back function of timer 5
		break;
	}
}

//***TIMER RELOAD VALUE CHANGE FUNCTION***//

void Timer_ChangeValue(uint8 TIMER_NUMBER, uint16 Reload_value)
{
	switch (TIMER_NUMBER)
	{
	case 0:
		TIMER0_TAILR_R = Reload_value;                //Adjusting the interrupt load register by a reload value for timer 0
		break;
	case 1:
		TIMER1_TAILR_R = Reload_value;                 //Adjusting the interrupt load register by a reload value for timer 1
		break;
	case 2:
		TIMER2_TAILR_R = Reload_value;                 //Adjusting the interrupt load register by a reload value for timer 2
		break;
	case 3:
		TIMER3_TAILR_R = Reload_value;                 //Adjusting the interrupt load register by a reload value for timer 3
		break;
	case 4:
		TIMER4_TAILR_R = Reload_value;                  //Adjusting the interrupt load register by a reload value for timer 4
		break;
	case 5:
		TIMER5_TAILR_R = Reload_value;                  //Adjusting the interrupt load register by a reload value for timer 5
		break;
	}
}
//***TIMER ENABLE FUNCTION***//

void Timer_ENAB(uint8 TIMER_NUMBER)
{
  switch (TIMER_NUMBER)
	{
	case 0:
		TIMER0_CTL_R = 0x1;                             //Enabling timer 0 to start counting 
		break;
	case 1:
		TIMER1_CTL_R = 0x1;                            //Enabling timer 1 to start counting 
		break;
	case 2:
		TIMER2_CTL_R = 0x1;                            //Enabling timer 2 to start counting 
		break;
	case 3:
		TIMER3_CTL_R = 0x1;                            //Enabling timer 3 to start counting 
		break;
	case 4:
		TIMER4_CTL_R = 0x1;                             //Enabling timer 4 to start counting 
		break;
	case 5:
		TIMER5_CTL_R = 0x1;                              //Enabling timer 5 to start counting 
		break;
	}
}
//***TIMER DISABLE FUNCTION***//

void Timer_DENAB(uint8 TIMER_NUMBER)
{
  switch (TIMER_NUMBER)
	{
	case 0:
		TIMER0_CTL_R = 0;                               //Disabling timer 0 after elapse
		break;
	case 1:
		TIMER1_CTL_R = 0;                                //Disabling timer 1 after elapse
		break;
	case 2:
		TIMER2_CTL_R = 0;                                 //Disabling timer 2 after elapse
		break;
	case 3:
		TIMER3_CTL_R = 0;                                //Disabling timer 3 after elapse
		break;
	case 4:
		TIMER4_CTL_R = 0;                                 //Disabling timer 4 after elapse
		break;
	case 5:
		TIMER5_CTL_R = 0;                                 //Disabling timer 5 after elapse
		break;
	}
}