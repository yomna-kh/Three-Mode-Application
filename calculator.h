#include "keypad.h"
#include "delay.h"
#include <stdio.h> 


void end_calc(float result);
void add(int num1, int num2);
void sub(int num1, int num2);
void mult(int num1, int num2);
void divide(int num1, int num2);
void clear_data(void);
void store(volatile int no, int* arr2);
int numfinalize(int* arr2);
void Calc_init (void);
void Calculate(void);
