#ifndef _MACROS__H_
#define _MACROS__H_

#define Set_Bit(Register,Bit) (Register|=(1u<<Bit))

#define Clear_Bit(Register,Bit) (Register&=(~(1u<<Bit)))

#define Get_Bit(Register,Bit) ((Register & (1u<<Bit)) >> Bit) 

#define Toggle_Bit(Regitser,Bit) (Register ^= (1u<<Bit))

#endif